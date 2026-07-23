# Project-owned Material Graph DSL parser.

"""Strict, engine-independent parser for the Material Graph DSL."""

from __future__ import annotations

import json
import re


VERSION = 3
_ID_PATTERN = re.compile(r'^[A-Za-z_][A-Za-z0-9_]*$')
_GUID_PATTERN = re.compile(
    r'^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$')
_REPLACE_ROOT_KEYS = {'version', 'mode', 'nodes', 'connections', 'outputs', 'layout'}
_PATCH_ROOT_KEYS = {'version', 'mode', 'operations', 'layout'}
_NODE_KEYS = {
    'id', 'guid', 'interface_guid', 'parameter_guid', 'class', 'x', 'y',
    'properties', 'pins',
}
_UPDATE_KEYS = {'target', 'x', 'y', 'properties', 'pins'}
_PINS_KEYS = {'inputs', 'outputs'}
_PIN_OUTPUT_KEYS = {'name', 'type'}
_CONNECTION_KEYS = {'from', 'output', 'to', 'input'}
_DISCONNECT_KEYS = {'to', 'input'}
_OUTPUT_KEYS = {'from', 'output', 'property'}
_OPERATIONS_KEYS = {
    'add_nodes', 'update_nodes', 'delete_nodes', 'connect', 'disconnect',
    'set_outputs', 'clear_outputs',
}

USAGE = r'''
Material Graph DSL is a strict JSON document. Unknown fields are errors.

{
  "version": 3,
  "mode": "replace",
  "nodes": [
    {
      "id": "roughness",
      "guid": "0f93bb9c-9db4-4ce6-b03c-fd84eed95dc0",
      "class": "/Script/Engine.MaterialExpressionConstant",
      "x": 0,
      "y": 0,
      "properties": {"r": 0.2}
    }
  ],
  "connections": [],
  "outputs": [
    {"from": "roughness", "output": "", "property": "MP_ROUGHNESS"}
  ],
  "layout": false
}

Node rules:
* id is required and must be unique.
* guid is the stable machine identity used by patch mode.
* class accepts a MaterialExpression class path or short class name.
* properties is a JSON object consumed by ToolsetLibrary.set_object_properties.
* Custom node dynamic pins live only in pins.inputs and pins.outputs.

Connection rules:
* from/to refer to node ids in the same document.
* output/input use exact material pin names. Empty string selects the first pin.
* outputs are valid only for Materials and property must be an MP_* enum name.

Safety:
* The whole document is parsed before graph mutation.
* Runtime references, properties, pins, connections and shader compilation are checked.
* Validation runs on a transient sandbox graph and never mutates the target asset.
* replace apply performs sandbox preflight and snapshots the old graph before mutation.
* Unexpected replace failures automatically rebuild the previous graph from that snapshot.
* mode "replace" replaces the complete graph.
* mode "patch" supports add/update/delete/connect/disconnect/output operations.
* read_graph_dsl exports a version 3 document that can be round-tripped.
'''.strip()


class MaterialDSLValidationError(ValueError):
    """Raised when a DSL document is malformed before Unreal graph mutation."""

    def __init__(self, errors: list[str]) -> None:
        super().__init__('\n'.join(errors))
        self.errors = errors


def parse(code: str) -> dict:
    """Parse and structurally validate a Material Graph DSL document."""
    errors: list[str] = []
    try:
        document = json.loads(code)
    except json.JSONDecodeError as exc:
        raise MaterialDSLValidationError([
            f'JSON syntax error at line {exc.lineno}, column {exc.colno}: {exc.msg}'
        ]) from exc

    if not isinstance(document, dict):
        raise MaterialDSLValidationError(['Root value must be a JSON object.'])

    version = document.get('version')
    if version != VERSION:
        errors.append(f'root.version must be {VERSION}.')

    mode = document.get('mode')
    if mode not in ('replace', 'patch'):
        errors.append('root.mode must be "replace" or "patch".')

    if mode == 'patch':
        return _parse_patch(document, errors)

    _reject_unknown(document, _REPLACE_ROOT_KEYS, 'root', errors)

    nodes = document.get('nodes')
    connections = document.get('connections', [])
    outputs = document.get('outputs', [])
    layout = document.get('layout', False)

    if not isinstance(nodes, list):
        errors.append('root.nodes must be an array.')
        nodes = []
    if not isinstance(connections, list):
        errors.append('root.connections must be an array.')
        connections = []
    if not isinstance(outputs, list):
        errors.append('root.outputs must be an array.')
        outputs = []
    if not isinstance(layout, bool):
        errors.append('root.layout must be a boolean.')

    node_ids: set[str] = set()
    for index, node in enumerate(nodes):
        path = f'nodes[{index}]'
        if not isinstance(node, dict):
            errors.append(f'{path} must be an object.')
            continue
        _validate_node(node, path, errors)
        node_id = node.get('id')
        if isinstance(node_id, str):
            if node_id in node_ids:
                errors.append(f'{path}.id duplicates "{node_id}".')
            node_ids.add(node_id)

    for index, connection in enumerate(connections):
        path = f'connections[{index}]'
        _validate_edge(connection, _CONNECTION_KEYS, path, errors)
        if isinstance(connection, dict):
            _validate_node_reference(connection.get('from'), node_ids, f'{path}.from', errors)
            _validate_node_reference(connection.get('to'), node_ids, f'{path}.to', errors)

    for index, output in enumerate(outputs):
        path = f'outputs[{index}]'
        _validate_edge(output, _OUTPUT_KEYS, path, errors)
        if isinstance(output, dict):
            _validate_node_reference(output.get('from'), node_ids, f'{path}.from', errors)
            prop = output.get('property')
            if not isinstance(prop, str) or not prop.startswith('MP_'):
                errors.append(f'{path}.property must be an MP_* enum name.')

    if errors:
        raise MaterialDSLValidationError(errors)

    return {
        'version': version,
        'mode': mode,
        'nodes': nodes,
        'connections': connections,
        'outputs': outputs,
        'layout': layout,
    }


def _parse_patch(document: dict, errors: list[str]) -> dict:
    _reject_unknown(document, _PATCH_ROOT_KEYS, 'root', errors)
    layout = document.get('layout', False)
    if not isinstance(layout, bool):
        errors.append('root.layout must be a boolean.')

    operations = document.get('operations')
    if not isinstance(operations, dict):
        errors.append('root.operations must be an object.')
        operations = {}
    _reject_unknown(operations, _OPERATIONS_KEYS, 'operations', errors)

    normalized = {}
    for key in _OPERATIONS_KEYS:
        value = operations.get(key, [])
        if not isinstance(value, list):
            errors.append(f'operations.{key} must be an array.')
            value = []
        normalized[key] = value

    added_ids: set[str] = set()
    for index, node in enumerate(normalized['add_nodes']):
        path = f'operations.add_nodes[{index}]'
        _validate_node(node, path, errors)
        if isinstance(node, dict) and isinstance(node.get('id'), str):
            if node['id'] in added_ids:
                errors.append(f'{path}.id duplicates "{node["id"]}".')
            added_ids.add(node['id'])

    for index, update in enumerate(normalized['update_nodes']):
        path = f'operations.update_nodes[{index}]'
        if not isinstance(update, dict):
            errors.append(f'{path} must be an object.')
            continue
        _reject_unknown(update, _UPDATE_KEYS, path, errors)
        _validate_target(update.get('target'), f'{path}.target', errors)
        _validate_edit_fields(update, path, errors)

    for index, target in enumerate(normalized['delete_nodes']):
        _validate_target(target, f'operations.delete_nodes[{index}]', errors)

    for key in ('connect',):
        for index, edge in enumerate(normalized[key]):
            _validate_edge(edge, _CONNECTION_KEYS, f'operations.{key}[{index}]', errors)
    for index, edge in enumerate(normalized['disconnect']):
        _validate_edge(edge, _DISCONNECT_KEYS, f'operations.disconnect[{index}]', errors)
    for index, output in enumerate(normalized['set_outputs']):
        path = f'operations.set_outputs[{index}]'
        _validate_edge(output, _OUTPUT_KEYS, path, errors)
        if isinstance(output, dict):
            prop = output.get('property')
            if not isinstance(prop, str) or not prop.startswith('MP_'):
                errors.append(f'{path}.property must be an MP_* enum name.')
    for index, prop in enumerate(normalized['clear_outputs']):
        if not isinstance(prop, str) or not prop.startswith('MP_'):
            errors.append(
                f'operations.clear_outputs[{index}] must be an MP_* enum name.')

    if not any(normalized.values()):
        errors.append('root.operations must contain at least one operation.')
    if errors:
        raise MaterialDSLValidationError(errors)
    return {
        'version': VERSION,
        'mode': 'patch',
        'operations': normalized,
        'layout': layout,
    }


def _validate_node(node: object, path: str, errors: list[str]) -> None:
    if not isinstance(node, dict):
        errors.append(f'{path} must be an object.')
        return
    _reject_unknown(node, _NODE_KEYS, path, errors)
    node_id = node.get('id')
    if not isinstance(node_id, str) or not _ID_PATTERN.fullmatch(node_id):
        errors.append(f'{path}.id must match {_ID_PATTERN.pattern}.')
    if not isinstance(node.get('class'), str) or not node['class']:
        errors.append(f'{path}.class must be a non-empty string.')
    for guid_key in ('guid', 'interface_guid', 'parameter_guid'):
        if guid_key in node and node[guid_key] != '' and (
                not isinstance(node[guid_key], str)
                or not _GUID_PATTERN.fullmatch(node[guid_key])):
            errors.append(f'{path}.{guid_key} must be a canonical GUID.')
    _validate_edit_fields(node, path, errors)


def _validate_edit_fields(value: dict, path: str, errors: list[str]) -> None:
    for coordinate in ('x', 'y'):
        if coordinate in value and (not isinstance(value[coordinate], int)
                                    or isinstance(value[coordinate], bool)):
            errors.append(f'{path}.{coordinate} must be an integer.')
    if 'properties' in value and not isinstance(value['properties'], dict):
        errors.append(f'{path}.properties must be an object.')
    if 'pins' in value:
        _validate_pins(value['pins'], f'{path}.pins', errors)


def _validate_pins(pins: object, path: str, errors: list[str]) -> None:
    if not isinstance(pins, dict):
        errors.append(f'{path} must be an object.')
        return
    _reject_unknown(pins, _PINS_KEYS, path, errors)
    inputs = pins.get('inputs', [])
    outputs = pins.get('outputs', [])
    if not isinstance(inputs, list) or not all(
            isinstance(name, str) and name for name in inputs):
        errors.append(f'{path}.inputs must be an array of non-empty strings.')
    if not isinstance(outputs, list):
        errors.append(f'{path}.outputs must be an array.')
        return
    for index, output in enumerate(outputs):
        output_path = f'{path}.outputs[{index}]'
        if not isinstance(output, dict):
            errors.append(f'{output_path} must be an object.')
            continue
        _reject_unknown(output, _PIN_OUTPUT_KEYS, output_path, errors)
        for key in _PIN_OUTPUT_KEYS:
            if not isinstance(output.get(key), str) or not output[key]:
                errors.append(f'{output_path}.{key} must be a non-empty string.')


def _validate_target(value: object, path: str, errors: list[str]) -> None:
    if not isinstance(value, str) or not value:
        errors.append(f'{path} must be a non-empty node id or GUID.')


def _reject_unknown(value: dict, allowed: set[str], path: str, errors: list[str]) -> None:
    for key in sorted(set(value) - allowed):
        errors.append(f'{path}.{key} is not supported.')


def _validate_edge(value: object, allowed: set[str], path: str, errors: list[str]) -> None:
    if not isinstance(value, dict):
        errors.append(f'{path} must be an object.')
        return
    _reject_unknown(value, allowed, path, errors)
    for key in allowed:
        if not isinstance(value.get(key), str):
            errors.append(f'{path}.{key} must be a string.')


def _validate_node_reference(value: object, ids: set[str], path: str,
                             errors: list[str]) -> None:
    if isinstance(value, str) and value not in ids:
        errors.append(f'{path} references unknown node id "{value}".')
