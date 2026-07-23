# Material Graph DSL

This feature is distributed by the UE 5.7 MCP PortKit. Its native bridge and
strict parser are project-owned files under `owned/MaterialGraphDSLBridge`.
Only the minimal integration changes to Epic's ported `EditorToolset` are
carried in the generated compatibility patch.

`editor_toolset.toolsets.material.MaterialTools` exposes four Material Graph DSL tools:

- `get_graph_dsl_docs`: Returns the current syntax and safety contract.
- `validate_graph_dsl`: Runs full graph and shader validation, then rolls back.
- `apply_graph_dsl`: Applies the document atomically and compiles the result.
- `read_graph_dsl`: Exports the complete graph in one call as round-trippable DSL.

The DSL is strict JSON. Unknown fields, duplicate ids, invalid classes, invalid properties,
invalid pins and failed connections are errors. Every validation/apply call returns a JSON
report. Shader compile diagnostics are returned in `compile_errors`; structural failures are
returned in `errors`.

Validation uses a transient Material or MaterialFunction sandbox. It does not edit the
target asset and therefore does not depend on UE 5.7 transaction rollback behavior.
Every apply performs this preflight and snapshots the old graph first. If an unexpected
target-side failure occurs, the old graph is rebuilt from the snapshot.

UE 5.7 compile diagnostics come from the project-owned
`UMaterialCompileDiagnosticsBridge`. It waits for shader compilation and reads the active
platform's `FMaterialResource` errors. For Material Functions it recompiles referencing
Materials and prefixes each error with the dependent asset path. No engine source is changed.

Version 3 is the only accepted format. It has two modes:

- `replace`: Rebuilds the complete graph.
- `patch`: Changes only named nodes, connections or Material outputs.

`read_graph_dsl` exports `replace` documents. Node `id` values are readable aliases derived
from parameter names, function input/output names and descriptions. Node `guid` is the stable
machine identity and should be used as a patch target. Custom HLSL pins are normalized under
`pins`; embedded Unreal object references are never exposed in `properties`.

Minimal replace:

```json
{
  "version": 3,
  "mode": "replace",
  "nodes": [
    {
      "id": "roughness",
      "guid": "0f93bb9c-9db4-4ce6-b03c-fd84eed95dc0",
      "class": "MaterialExpressionConstant",
      "properties": {"r": 0.2}
    }
  ],
  "outputs": [
    {"from": "roughness", "output": "", "property": "MP_ROUGHNESS"}
  ]
}
```

Minimal patch:

```json
{
  "version": 3,
  "mode": "patch",
  "operations": {
    "update_nodes": [
      {
        "target": "0f93bb9c-9db4-4ce6-b03c-fd84eed95dc0",
        "properties": {"r": 0.3}
      }
    ],
    "disconnect": [],
    "connect": [],
    "set_outputs": [],
    "clear_outputs": []
  }
}
```

Patch operations are `add_nodes`, `update_nodes`, `delete_nodes`, `connect`, `disconnect`,
`set_outputs` and `clear_outputs`. Omitted operation arrays default to empty. `apply_graph_dsl`
already runs sandbox validation; a separate validation call is useful only for dry runs.
Asset saving remains explicit through `AssetTools.save_assets`.
