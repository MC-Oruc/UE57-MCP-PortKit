# Project-owned tests for the Material Graph DSL parser.
"""Pure-Python tests for the strict Material Graph DSL parser."""

import json
import importlib.util
from pathlib import Path
import unittest


_MODULE_PATH = Path(__file__).parents[1] / 'material_dsl.py'
_SPEC = importlib.util.spec_from_file_location('material_dsl_under_test', _MODULE_PATH)
material_dsl = importlib.util.module_from_spec(_SPEC)
_SPEC.loader.exec_module(material_dsl)


class MaterialDSLParserTests(unittest.TestCase):

    def test_parses_valid_replace_document(self):
        document = material_dsl.parse(json.dumps({
            'version': 3,
            'mode': 'replace',
            'nodes': [{
                'id': 'constant',
                'guid': '0f93bb9c-9db4-4ce6-b03c-fd84eed95dc0',
                'class': 'MaterialExpressionConstant',
                'properties': {'r': 0.25},
            }],
            'outputs': [{
                'from': 'constant',
                'output': '',
                'property': 'MP_ROUGHNESS',
            }],
        }))
        self.assertEqual('constant', document['nodes'][0]['id'])
        self.assertFalse(document['layout'])
        self.assertEqual('replace', document['mode'])

    def test_parses_valid_patch_document(self):
        document = material_dsl.parse(json.dumps({
            'version': 3,
            'mode': 'patch',
            'operations': {
                'update_nodes': [{
                    'target': '0f93bb9c-9db4-4ce6-b03c-fd84eed95dc0',
                    'properties': {'r': 0.5},
                }],
                'disconnect': [{
                    'to': 'roughness',
                    'input': '',
                }],
            },
        }))
        self.assertEqual('patch', document['mode'])
        self.assertEqual(0.5, document['operations']['update_nodes'][0]['properties']['r'])
        self.assertEqual([], document['operations']['add_nodes'])

    def test_rejects_legacy_version(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 2,
                'mode': 'replace',
                'nodes': [],
            }))
        self.assertIn('root.version must be 3.', context.exception.errors)

    def test_rejects_empty_patch(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'patch',
                'operations': {},
            }))
        self.assertIn(
            'root.operations must contain at least one operation.',
            context.exception.errors)

    def test_reports_json_line_and_column(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse('{\n  "version": 3,\n  broken\n}')
        self.assertIn('line 3', context.exception.errors[0])
        self.assertIn('column', context.exception.errors[0])

    def test_rejects_unknown_fields(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'replace',
                'nodes': [{'id': 'a', 'class': 'MaterialExpressionConstant'}],
                'surprise': True,
            }))
        self.assertIn('root.surprise is not supported.', context.exception.errors)

    def test_rejects_duplicate_node_ids(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'replace',
                'nodes': [
                    {'id': 'same', 'class': 'MaterialExpressionConstant'},
                    {'id': 'same', 'class': 'MaterialExpressionConstant2Vector'},
                ],
            }))
        self.assertTrue(any('duplicates "same"' in error for error in context.exception.errors))

    def test_requires_node_class(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'replace',
                'nodes': [{'id': 'bad'}],
            }))
        self.assertTrue(any('.class must be a non-empty string' in error
                            for error in context.exception.errors))

    def test_rejects_unknown_connection_node(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'replace',
                'nodes': [{'id': 'a', 'class': 'MaterialExpressionConstant'}],
                'connections': [{
                    'from': 'missing', 'output': '', 'to': 'a', 'input': '',
                }],
            }))
        self.assertTrue(any('unknown node id "missing"' in error
                            for error in context.exception.errors))

    def test_rejects_non_integer_position(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'replace',
                'nodes': [{
                    'id': 'a', 'class': 'MaterialExpressionConstant', 'x': 1.5,
                }],
            }))
        self.assertIn('nodes[0].x must be an integer.', context.exception.errors)

    def test_rejects_noncanonical_guid(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'replace',
                'nodes': [{
                    'id': 'a',
                    'guid': 'not-a-guid',
                    'class': 'MaterialExpressionConstant',
                }],
            }))
        self.assertIn('nodes[0].guid must be a canonical GUID.', context.exception.errors)

    def test_validates_custom_pin_schema(self):
        document = material_dsl.parse(json.dumps({
            'version': 3,
            'mode': 'replace',
            'nodes': [{
                'id': 'custom',
                'class': 'MaterialExpressionCustom',
                'pins': {
                    'inputs': ['Time', 'Mask'],
                    'outputs': [{'name': 'Result', 'type': 'CMOT_FLOAT1'}],
                },
            }],
        }))
        self.assertEqual(['Time', 'Mask'], document['nodes'][0]['pins']['inputs'])

    def test_rejects_malformed_custom_pin_schema(self):
        with self.assertRaises(material_dsl.MaterialDSLValidationError) as context:
            material_dsl.parse(json.dumps({
                'version': 3,
                'mode': 'replace',
                'nodes': [{
                    'id': 'custom',
                    'class': 'MaterialExpressionCustom',
                    'pins': {
                        'inputs': [''],
                        'outputs': [{'name': 'Result'}],
                    },
                }],
            }))
        self.assertTrue(any('.pins.inputs must be an array' in error
                            for error in context.exception.errors))
        self.assertTrue(any('.type must be a non-empty string' in error
                            for error in context.exception.errors))


if __name__ == '__main__':
    unittest.main()
