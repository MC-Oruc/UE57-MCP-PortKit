# MCP Validation Report

This report compares the UE 5.8 Experimental Toolsets source surface against the validated UE 5.7.4 PortKit MCP health schema.

Sources:
- UE 5.8 tool sources: pinned EpicGames/UnrealEngine `5.8.0-release` source tree
- Validated health schema: PortKit install probe report
- Health status: `pass`

Rule: `Available` means the tool is advertised by the validated MCP health schema. Runtime smoke coverage is limited to the PortKit health/probe workflow.

## Project Extensions

The UE 5.8 parity totals below do not count these project-specific additions:

- `EditorToolset.EditorAppToolset.ExecuteConsoleCommand`: runs editor console commands such as `viewmode unlit`.
- `editor_toolset.toolsets.asset.AssetTools.find_assets`: enhanced `name` filtering. The same `name` argument now matches case-insensitive substring text and wildcard patterns with `*` / `?`.

## Summary

- UE 5.8 total sub-tools: **853**
- Available sub-tools: **414**
- Missing sub-tools: **439**
- Registered toolset count: **40**

## Group Summary

Group names are shown as sections instead of repeated table cells.

### `AIModuleToolset` - 🟢 COMPLETE (7/7)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `BehaviorTreeTools` | 7 | 7 | 0 | 🟢 COMPLETE |

### `AnimationAssistantToolset` - 🔴 MISSING (0/319)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `ControlRigTools` | 44 | 0 | 44 | 🔴 MISSING |
| `SequencerConditionTools` | 9 | 0 | 9 | 🔴 MISSING |
| `SequencerControlRigTools` | 72 | 0 | 72 | 🔴 MISSING |
| `SequencerCustomBindingTools` | 8 | 0 | 8 | 🔴 MISSING |
| `SequencerImportExportTools` | 6 | 0 | 6 | 🔴 MISSING |
| `SequencerKeyframingTools` | 22 | 0 | 22 | 🔴 MISSING |
| `SequencerOutlinerTools` | 18 | 0 | 18 | 🔴 MISSING |
| `SequencerTools` | 140 | 0 | 140 | 🔴 MISSING |

### `AutomationTestToolset` - 🟢 COMPLETE (7/7)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `AutomationTestToolset` | 7 | 7 | 0 | 🟢 COMPLETE |

### `ChaosClothAssetToolset` - 🔴 MISSING (0/6)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `ChaosClothAssetToolset` | 6 | 0 | 6 | 🔴 MISSING |

### `ConfigSettingsToolset` - 🟢 COMPLETE (8/8)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `ConfigSettingsToolset` | 8 | 8 | 0 | 🟢 COMPLETE |

### `ConversationToolset` - 🟢 COMPLETE (7/7)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `ConversationTools` | 7 | 7 | 0 | 🟢 COMPLETE |

### `DataflowAgent` - 🔴 MISSING (0/22)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `DataflowAgentToolset` | 22 | 0 | 22 | 🔴 MISSING |

### `DataRegistryToolset` - 🟢 COMPLETE (7/7)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `DataRegistryTools` | 7 | 7 | 0 | 🟢 COMPLETE |

### `EditorToolset` - 🟢 COMPLETE (251/251)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `ActorTools` | 17 | 17 | 0 | 🟢 COMPLETE |
| `AssetTools` | 21 | 21 | 0 | 🟢 COMPLETE |
| `BlueprintTools` | 53 | 53 | 0 | 🟢 COMPLETE |
| `CurveTableTools` | 9 | 9 | 0 | 🟢 COMPLETE |
| `DataAssetTools` | 1 | 1 | 0 | 🟢 COMPLETE |
| `DataTableTools` | 10 | 10 | 0 | 🟢 COMPLETE |
| `EditorAppToolset` | 21 | 21 | 0 | 🟢 COMPLETE |
| `LogsToolset` | 4 | 4 | 0 | 🟢 COMPLETE |
| `MaterialInstanceTools` | 13 | 13 | 0 | 🟢 COMPLETE |
| `MaterialTools` | 22 | 22 | 0 | 🟢 COMPLETE |
| `ObjectTools` | 6 | 6 | 0 | 🟢 COMPLETE |
| `PrimitiveTools` | 4 | 4 | 0 | 🟢 COMPLETE |
| `ProgrammaticToolset` | 2 | 2 | 0 | 🟢 COMPLETE |
| `SceneTools` | 20 | 20 | 0 | 🟢 COMPLETE |
| `SkeletalMeshTools` | 22 | 22 | 0 | 🟢 COMPLETE |
| `StaticMeshTools` | 16 | 16 | 0 | 🟢 COMPLETE |
| `StringTableTools` | 8 | 8 | 0 | 🟢 COMPLETE |
| `TextureTools` | 2 | 2 | 0 | 🟢 COMPLETE |

### `GameFeaturesToolset` - 🟢 COMPLETE (7/7)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `GameFeaturesToolset` | 7 | 7 | 0 | 🟢 COMPLETE |

### `GameplayTagsToolset` - 🟢 COMPLETE (6/6)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `GameplayTagsToolset` | 6 | 6 | 0 | 🟢 COMPLETE |

### `GASToolsets` - 🟢 COMPLETE (14/14)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `AbilitySystemInspectorToolset` | 4 | 4 | 0 | 🟢 COMPLETE |
| `AttributeSetToolset` | 2 | 2 | 0 | 🟢 COMPLETE |
| `GameplayCueToolset` | 8 | 8 | 0 | 🟢 COMPLETE |

### `LiveCodingToolset` - 🟢 COMPLETE (1/1)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `LiveCodingToolset` | 1 | 1 | 0 | 🟢 COMPLETE |

### `MetaHumanGenerator` - 🔴 MISSING (0/9)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `MetaHumanToolset` | 9 | 0 | 9 | 🔴 MISSING - UE 5.7 does not expose `unreal.MetaHumanGeneratorSubsystemWrapper`; a native bridge is required. |

### `MVVMToolset` - 🔴 MISSING (0/9)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `MVVMToolset` | 9 | 0 | 9 | 🔴 MISSING |

### `NiagaraToolsets` - 🟡 PARTIAL (7/56)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `NiagaraToolset_Assets` | 3 | 3 | 0 | 🟢 COMPLETE |
| `NiagaraToolset_Blueprint` | 2 | 2 | 0 | 🟢 COMPLETE |
| `NiagaraToolset_Component` | 4 | 1 | 3 | 🟡 PARTIAL |
| `NiagaraToolset_Info` | 1 | 1 | 0 | 🟢 COMPLETE |
| `NiagaraToolset_System` | 46 | 0 | 46 | 🔴 MISSING |

### `PCGToolset` - 🟢 COMPLETE (31/31)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `PCGSpatialToolset` | 1 | 1 | 0 | 🟢 COMPLETE |
| `PCGToolset` | 30 | 30 | 0 | 🟢 COMPLETE |

### `PhysicsToolsets` - 🟢 COMPLETE (17/17)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `PhysicsAssetToolset` | 17 | 17 | 0 | 🟢 COMPLETE |

### `PluginToolset` - 🟢 COMPLETE (17/17)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `PluginToolset` | 17 | 17 | 0 | 🟢 COMPLETE |

### `SemanticSearchToolset` - 🔴 MISSING (0/2)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `SemanticSearchToolset` | 2 | 0 | 2 | 🔴 MISSING |

### `SequencerAnimMixerToolset` - 🔴 MISSING (0/21)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `SequencerAnimMixerTools` | 21 | 0 | 21 | 🔴 MISSING |

### `SlateInspectorToolset` - 🟢 COMPLETE (14/14)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `SlateInspectorToolset` | 14 | 14 | 0 | 🟢 COMPLETE |

### `StateTreeToolset` - 🟢 COMPLETE (9/9)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `StateTreeTools` | 9 | 9 | 0 | 🟢 COMPLETE |

### `ToolsetRegistry` - 🟢 COMPLETE (4/4)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `AgentSkillToolset` | 4 | 4 | 0 | 🟢 COMPLETE |

### `WorldConditionsToolset` - 🟢 COMPLETE (2/2)

| Toolset | UE 5.8 sub-tools | Available | Missing | Status |
| :--- | ---: | ---: | ---: | :--- |
| `WorldConditionTools` | 2 | 2 | 0 | 🟢 COMPLETE |
## Detaylı Karşılaştırma

### ToolsetRegistry

#### `AgentSkillToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `CreateSkill` | 🟢 Available | `ToolsetRegistry.AgentSkillToolset.CreateSkill` |
| `GetSkills` | 🟢 Available | `ToolsetRegistry.AgentSkillToolset.GetSkills` |
| `ListSkills` | 🟢 Available | `ToolsetRegistry.AgentSkillToolset.ListSkills` |
| `UpdateSkill` | 🟢 Available | `ToolsetRegistry.AgentSkillToolset.UpdateSkill` |

### EditorToolset

#### `ActorTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_component` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.add_component` |
| `add_tag` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.add_tag` |
| `get_actor_bounds` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_actor_bounds` |
| `get_actor_transform` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_actor_transform` |
| `get_component_actor` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_component_actor` |
| `get_components` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_components` |
| `get_label` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_label` |
| `get_parent_component` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_parent_component` |
| `get_root_component` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_root_component` |
| `get_tags` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.get_tags` |
| `has_tag` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.has_tag` |
| `look_at` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.look_at` |
| `remove_component` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.remove_component` |
| `remove_tag` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.remove_tag` |
| `set_actor_transform` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.set_actor_transform` |
| `set_label` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.set_label` |
| `set_parent_component` | 🟢 Available | `editor_toolset.toolsets.actor.ActorTools.set_parent_component` |

#### `AssetTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `can_edit_asset` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.can_edit_asset` |
| `create_folder` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.create_folder` |
| `delete` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.delete` |
| `duplicate` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.duplicate` |
| `exists` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.exists` |
| `find_assets` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.find_assets` |
| `find_assets` name wildcard matching | 🟢 Project extension | Same `name` argument supports substring OR wildcard (`*`, `?`) |
| `get_asset_class` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.get_asset_class` |
| `get_asset_tags` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.get_asset_tags` |
| `get_dependencies` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.get_dependencies` |
| `get_metadata_tags` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.get_metadata_tags` |
| `get_plugin_content_paths` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.get_plugin_content_paths` |
| `get_referencers` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.get_referencers` |
| `is_checked_out` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.is_checked_out` |
| `is_dirty` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.is_dirty` |
| `list_folders` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.list_folders` |
| `load_asset` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.load_asset` |
| `move` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.move` |
| `read_file` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.read_file` |
| `save_assets` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.save_assets` |
| `update_metadata_tags` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.update_metadata_tags` |
| `write_file` | 🟢 Available | `editor_toolset.toolsets.asset.AssetTools.write_file` |

#### `BlueprintTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_component_bound_event` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_component_bound_event` |
| `add_event` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_event` |
| `add_event_dispatcher` | 🟢 Available | `EditorToolset.BlueprintTools.AddEventDispatcher` |
| `add_function_graph` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_function_graph` |
| `add_function_param` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_function_param` |
| `add_node_pin` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_node_pin` |
| `add_object_function_param` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_object_function_param` |
| `add_object_variable` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_object_variable` |
| `add_struct_function_param` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_struct_function_param` |
| `add_struct_variable` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_struct_variable` |
| `add_variable` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.add_variable` |
| `arrange_nodes` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.arrange_nodes` |
| `break_pins` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.break_pins` |
| `compile_blueprint` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.compile_blueprint` |
| `connect_pins` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.connect_pins` |
| `create` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.create` |
| `create_node` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.create_node` |
| `delete_node` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.delete_node` |
| `find_node_categories` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.find_node_categories` |
| `find_node_types` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.find_node_types` |
| `find_nodes` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.find_nodes` |
| `get_connected_subgraph` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_connected_subgraph` |
| `get_create_event_function` | 🟢 Available | `EditorToolset.BlueprintTools.GetCreateEventFunction` |
| `get_default_object` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_default_object` |
| `get_graph` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_graph` |
| `get_graph_dsl_docs` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_graph_dsl_docs` |
| `get_node_infos` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_node_infos` |
| `get_node_type_pins` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_node_type_pins` |
| `get_parent` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_parent` |
| `get_pin_value` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_pin_value` |
| `get_variable_category` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_variable_category` |
| `get_variable_replication` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.get_variable_replication` |
| `list_compatible_event_functions` | 🟢 Available | `EditorToolset.BlueprintTools.ListCompatibleEventFunctions` |
| `list_component_events` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.list_component_events` |
| `list_event_dispatchers` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.list_event_dispatchers` |
| `list_events` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.list_events` |
| `list_functions` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.list_functions` |
| `list_graphs` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.list_graphs` |
| `list_variables` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.list_variables` |
| `read_graph_dsl` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.read_graph_dsl` |
| `remove_function_graph` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.remove_function_graph` |
| `remove_function_param` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.remove_function_param` |
| `remove_node_pin` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.remove_node_pin` |
| `remove_variable` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.remove_variable` |
| `retarget_node_class` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.retarget_node_class` |
| `set_create_event_function` | 🟢 Available | `EditorToolset.BlueprintTools.SetCreateEventFunction` |
| `set_node_position` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.set_node_position` |
| `set_parent` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.set_parent` |
| `set_pin_value` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.set_pin_value` |
| `set_variable_category` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.set_variable_category` |
| `set_variable_instance_editable` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.set_variable_instance_editable` |
| `set_variable_replication` | 🟢 Available | `editor_toolset.toolsets.blueprint.BlueprintTools.set_variable_replication` |
| `write_graph_dsl` | 🟢 Available | `EditorToolset.BlueprintTools.WriteGraphDsl` |

#### `CurveTableTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_key` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.add_key` |
| `add_row` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.add_row` |
| `create` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.create` |
| `get_keys` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.get_keys` |
| `import_file` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.import_file` |
| `list_rows` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.list_rows` |
| `remove_row` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.remove_row` |
| `rename_row` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.rename_row` |
| `set_keys` | 🟢 Available | `editor_toolset.toolsets.curve_table.CurveTableTools.set_keys` |

#### `DataAssetTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `create` | 🟢 Available | `editor_toolset.toolsets.data_asset.DataAssetTools.create` |

#### `DataTableTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_rows` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.add_rows` |
| `create` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.create` |
| `get_rows` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.get_rows` |
| `get_schema` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.get_schema` |
| `import_file` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.import_file` |
| `list_rows` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.list_rows` |
| `remove_rows` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.remove_rows` |
| `rename_rows` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.rename_rows` |
| `search_row_structs` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.search_row_structs` |
| `set_rows` | 🟢 Available | `editor_toolset.toolsets.data_table.DataTableTools.set_rows` |

#### `EditorAppToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `CaptureAssetImage` | 🟢 Available | `EditorToolset.EditorAppToolset.CaptureAssetImage` |
| `CaptureEditorImage` | 🟢 Available | `EditorToolset.EditorAppToolset.CaptureEditorImage` |
| `CaptureViewport` | 🟢 Available | `EditorToolset.EditorAppToolset.CaptureViewport` |
| `FocusOnActors` | 🟢 Available | `EditorToolset.EditorAppToolset.FocusOnActors` |
| `GetCameraTransform` | 🟢 Available | `EditorToolset.EditorAppToolset.GetCameraTransform` |
| `GetContentBrowserPath` | 🟢 Available | `EditorToolset.EditorAppToolset.GetContentBrowserPath` |
| `GetOpenAssets` | 🟢 Available | `EditorToolset.EditorAppToolset.GetOpenAssets` |
| `GetSelectedActors` | 🟢 Available | `EditorToolset.EditorAppToolset.GetSelectedActors` |
| `GetSelectedAssets` | 🟢 Available | `EditorToolset.EditorAppToolset.GetSelectedAssets` |
| `GetVisibleActors` | 🟢 Available | `EditorToolset.EditorAppToolset.GetVisibleActors` |
| `IsPIERunning` | 🟢 Available | `EditorToolset.EditorAppToolset.IsPIERunning` |
| `OpenEditorForAsset` | 🟢 Available | `EditorToolset.EditorAppToolset.OpenEditorForAsset` |
| `ScreenCoordsToWorld` | 🟢 Available | `EditorToolset.EditorAppToolset.ScreenCoordsToWorld` |
| `SearchCVars` | 🟢 Available | `EditorToolset.EditorAppToolset.SearchCVars` |
| `ExecuteConsoleCommand` | 🟢 Project extension | `EditorToolset.EditorAppToolset.ExecuteConsoleCommand` |
| `SelectActors` | 🟢 Available | `EditorToolset.EditorAppToolset.SelectActors` |
| `SelectAssets` | 🟢 Available | `EditorToolset.EditorAppToolset.SelectAssets` |
| `SetCameraTransform` | 🟢 Available | `EditorToolset.EditorAppToolset.SetCameraTransform` |
| `SetContentBrowserPath` | 🟢 Available | `EditorToolset.EditorAppToolset.SetContentBrowserPath` |
| `StartPIE` | 🟢 Available | `EditorToolset.EditorAppToolset.StartPIE` |
| `StopPIE` | 🟢 Available | `EditorToolset.EditorAppToolset.StopPIE` |
| `WorldPosToScreenCoords` | 🟢 Available | `EditorToolset.EditorAppToolset.WorldPosToScreenCoords` |

#### `LogsToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `GetLogCategories` | 🟢 Available | `EditorToolset.LogsToolset.GetLogCategories` |
| `GetLogEntries` | 🟢 Available | `EditorToolset.LogsToolset.GetLogEntries` |
| `GetVerbosity` | 🟢 Available | `EditorToolset.LogsToolset.GetVerbosity` |
| `SetVerbosity` | 🟢 Available | `EditorToolset.LogsToolset.SetVerbosity` |

#### `MaterialInstanceTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `clear_parameters` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.clear_parameters` |
| `create` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.create` |
| `get_scalar_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.get_scalar_parameter` |
| `get_static_switch_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.get_static_switch_parameter` |
| `get_texture_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.get_texture_parameter` |
| `get_vector_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.get_vector_parameter` |
| `list_parameters` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.list_parameters` |
| `set_parameter_override` | 🟢 Available | `EditorToolset.MaterialInstanceTools.SetParameterOverride` |
| `set_parent` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.set_parent` |
| `set_scalar_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.set_scalar_parameter` |
| `set_static_switch_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.set_static_switch_parameter` |
| `set_texture_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.set_texture_parameter` |
| `set_vector_parameter` | 🟢 Available | `editor_toolset.toolsets.material_instance.MaterialInstanceTools.set_vector_parameter` |

#### `MaterialTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_expression` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.add_expression` |
| `connect_expressions` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.connect_expressions` |
| `connect_to_output` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.connect_to_output` |
| `create_function` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.create_function` |
| `create_material` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.create_material` |
| `create_parameter_collection` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.create_parameter_collection` |
| `delete_expression` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.delete_expression` |
| `delete_parameter_group` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.delete_parameter_group` |
| `delete_unused_expressions` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.delete_unused_expressions` |
| `disconnect_expressions` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.disconnect_expressions` |
| `disconnect_from_output` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.disconnect_from_output` |
| `get_expression_input_names` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.get_expression_input_names` |
| `get_expression_inputs` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.get_expression_inputs` |
| `get_expression_output_names` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.get_expression_output_names` |
| `get_expressions` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.get_expressions` |
| `get_property_input` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.get_property_input` |
| `get_referencing_materials` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.get_referencing_materials` |
| `layout_expressions` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.layout_expressions` |
| `list_expression_classes` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.list_expression_classes` |
| `list_parameter_groups` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.list_parameter_groups` |
| `recompile` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.recompile` |
| `rename_parameter_group` | 🟢 Available | `editor_toolset.toolsets.material.MaterialTools.rename_parameter_group` |

#### `ObjectTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `get_class` | 🟢 Available | `editor_toolset.toolsets.object.ObjectTools.get_class` |
| `get_properties` | 🟢 Available | `editor_toolset.toolsets.object.ObjectTools.get_properties` |
| `list_properties` | 🟢 Available | `editor_toolset.toolsets.object.ObjectTools.list_properties` |
| `reset_properties` | 🟢 Available | `editor_toolset.toolsets.object.ObjectTools.reset_properties` |
| `search_subclasses` | 🟢 Available | `editor_toolset.toolsets.object.ObjectTools.search_subclasses` |
| `set_properties` | 🟢 Available | `editor_toolset.toolsets.object.ObjectTools.set_properties` |

#### `PrimitiveTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_cone` | 🟢 Available | `editor_toolset.toolsets.primitive.PrimitiveTools.add_cone` |
| `add_cube` | 🟢 Available | `editor_toolset.toolsets.primitive.PrimitiveTools.add_cube` |
| `add_cylinder` | 🟢 Available | `editor_toolset.toolsets.primitive.PrimitiveTools.add_cylinder` |
| `add_sphere` | 🟢 Available | `editor_toolset.toolsets.primitive.PrimitiveTools.add_sphere` |

#### `ProgrammaticToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `execute_tool_script` | 🟢 Available | `editor_toolset.toolsets.programmatic.ProgrammaticToolset.execute_tool_script` |
| `get_execution_environment` | 🟢 Available | `editor_toolset.toolsets.programmatic.ProgrammaticToolset.get_execution_environment` |

#### `SceneTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_to_scene_from_asset` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.add_to_scene_from_asset` |
| `add_to_scene_from_class` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.add_to_scene_from_class` |
| `can_edit` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.can_edit` |
| `commit_level_instance` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.commit_level_instance` |
| `create_level_instance` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.create_level_instance` |
| `delete_folder` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.delete_folder` |
| `edit_level_instance` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.edit_level_instance` |
| `find_actors` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.find_actors` |
| `get_actors_in_folder` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.get_actors_in_folder` |
| `get_collision_channels` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.get_collision_channels` |
| `get_current_level` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.get_current_level` |
| `get_folders` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.get_folders` |
| `is_checked_out` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.is_checked_out` |
| `load_level` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.load_level` |
| `merge_actors` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.merge_actors` |
| `remove_from_scene` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.remove_from_scene` |
| `rename_folder` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.rename_folder` |
| `save_actor` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.save_actor` |
| `set_actor_folder` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.set_actor_folder` |
| `trace_world` | 🟢 Available | `editor_toolset.toolsets.scene.SceneTools.trace_world` |

#### `SkeletalMeshTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_socket` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.add_socket` |
| `assign_physics_asset` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.assign_physics_asset` |
| `get_bone_children` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_bone_children` |
| `get_bone_names` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_bone_names` |
| `get_bone_parent` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_bone_parent` |
| `get_bounds` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_bounds` |
| `get_lod_count` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_lod_count` |
| `get_material` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_material` |
| `get_material_slots` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_material_slots` |
| `get_morph_target_names` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_morph_target_names` |
| `get_physics_asset` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_physics_asset` |
| `get_section_count` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_section_count` |
| `get_skeleton` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_skeleton` |
| `get_socket_bone` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_socket_bone` |
| `get_socket_names` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_socket_names` |
| `get_socket_transform` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_socket_transform` |
| `get_vertex_count` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.get_vertex_count` |
| `import_file` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.import_file` |
| `remove_socket` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.remove_socket` |
| `rename_socket` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.rename_socket` |
| `set_material` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.set_material` |
| `set_socket_transform` | 🟢 Available | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools.set_socket_transform` |

#### `StaticMeshTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `generate_convex_collisions` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.generate_convex_collisions` |
| `generate_lods` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.generate_lods` |
| `get_bounds` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.get_bounds` |
| `get_lod_count` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.get_lod_count` |
| `get_lod_thresholds` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.get_lod_thresholds` |
| `get_material` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.get_material` |
| `get_material_slots` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.get_material_slots` |
| `get_triangle_count` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.get_triangle_count` |
| `get_vertex_count` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.get_vertex_count` |
| `import_file` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.import_file` |
| `is_nanite_enabled` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.is_nanite_enabled` |
| `remove_collisions` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.remove_collisions` |
| `remove_lods` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.remove_lods` |
| `set_lod_thresholds` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.set_lod_thresholds` |
| `set_material` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.set_material` |
| `set_nanite_enabled` | 🟢 Available | `editor_toolset.toolsets.static_mesh.StaticMeshTools.set_nanite_enabled` |

#### `StringTableTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `create` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.create` |
| `get_entry` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.get_entry` |
| `get_namespace` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.get_namespace` |
| `get_table_id` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.get_table_id` |
| `import_file` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.import_file` |
| `list_keys` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.list_keys` |
| `remove_entry` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.remove_entry` |
| `set_entry` | 🟢 Available | `editor_toolset.toolsets.string_table.StringTableTools.set_entry` |

#### `TextureTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `get_size` | 🟢 Available | `editor_toolset.toolsets.texture.TextureTools.get_size` |
| `import_file` | 🟢 Available | `editor_toolset.toolsets.texture.TextureTools.import_file` |

### GameplayTagsToolset

#### `GameplayTagsToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddTag` | 🟢 Available | `GameplayTagsToolset.GameplayTagsToolset.AddTag` |
| `FindReferencersByTag` | 🟢 Available | `GameplayTagsToolset.GameplayTagsToolset.FindReferencersByTag` |
| `GetTagInfo` | 🟢 Available | `GameplayTagsToolset.GameplayTagsToolset.GetTagInfo` |
| `ListTags` | 🟢 Available | `GameplayTagsToolset.GameplayTagsToolset.ListTags` |
| `RemoveTag` | 🟢 Available | `GameplayTagsToolset.GameplayTagsToolset.RemoveTag` |
| `RenameTag` | 🟢 Available | `GameplayTagsToolset.GameplayTagsToolset.RenameTag` |

### GASToolsets

#### `AbilitySystemInspectorToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `GetActiveEffects` | 🟢 Available | `GASToolsets.AbilitySystemInspectorToolset.GetActiveEffects` |
| `GetActiveTags` | 🟢 Available | `GASToolsets.AbilitySystemInspectorToolset.GetActiveTags` |
| `GetAttributeValues` | 🟢 Available | `GASToolsets.AbilitySystemInspectorToolset.GetAttributeValues` |
| `GetGrantedAbilities` | 🟢 Available | `GASToolsets.AbilitySystemInspectorToolset.GetGrantedAbilities` |

#### `AttributeSetToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `FindAttributeSetClasses` | 🟢 Available | `GASToolsets.AttributeSetToolset.FindAttributeSetClasses` |
| `ListAttributes` | 🟢 Available | `GASToolsets.AttributeSetToolset.ListAttributes` |

#### `GameplayCueToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddCueTag` | 🟢 Available | `GASToolsets.GameplayCueToolset.AddCueTag` |
| `CreateCueNotifyAsset` | 🟢 Available | `GASToolsets.GameplayCueToolset.CreateCueNotifyAsset` |
| `ExecuteCueOnSelectedActor` | 🟢 Available | `GASToolsets.GameplayCueToolset.ExecuteCueOnSelectedActor` |
| `FindCueNotifyAssets` | 🟢 Available | `GASToolsets.GameplayCueToolset.FindCueNotifyAssets` |
| `FindCueTagsWithoutNotifies` | 🟢 Available | `GASToolsets.GameplayCueToolset.FindCueTagsWithoutNotifies` |
| `GetCueInfo` | 🟢 Available | `GASToolsets.GameplayCueToolset.GetCueInfo` |
| `ListCues` | 🟢 Available | `GASToolsets.GameplayCueToolset.ListCues` |
| `RemoveCueTag` | 🟢 Available | `GASToolsets.GameplayCueToolset.RemoveCueTag` |

### StateTreeToolset

#### `StateTreeTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `get_children` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_children` |
| `get_editor_data` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_editor_data` |
| `get_enter_conditions` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_enter_conditions` |
| `get_evaluators` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_evaluators` |
| `get_global_tasks` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_global_tasks` |
| `get_node_description` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_node_description` |
| `get_root_states` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_root_states` |
| `get_tasks` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_tasks` |
| `get_transitions` | 🟢 Available | `state_tree_toolset.toolsets.state_tree.StateTreeTools.get_transitions` |

### NiagaraToolsets

#### `NiagaraToolset_Assets` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `FindNiagaraScripts` | 🟢 Available | `NiagaraToolsets.NiagaraToolset_Assets.FindNiagaraScripts` |
| `GetAssetDiscoveryInfo` | 🟢 Available | `NiagaraToolsets.NiagaraToolset_Assets.GetAssetDiscoveryInfo` |
| `GetNiagaraScriptDigest` | 🟢 Available | `NiagaraToolsets.NiagaraToolset_Assets.GetNiagaraScriptDigest` |

#### `NiagaraToolset_Blueprint` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `ConstructNiagaraBPWrapperFromComponent` | 🟢 Available | `NiagaraToolsets.NiagaraToolset_Blueprint.ConstructNiagaraBPWrapperFromComponent` |
| `ConstructNiagaraBPWrapperFromSystem` | 🟢 Available | `NiagaraToolsets.NiagaraToolset_Blueprint.ConstructNiagaraBPWrapperFromSystem` |

#### `NiagaraToolset_Component` - 🟡 PARTIAL

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `GetUserVariables` | 🔴 Missing | - |
| `GetVariable` | 🔴 Missing | - |
| `SetSystem` | 🟢 Available | `NiagaraToolsets.NiagaraToolset_Component.SetSystem` |
| `SetVariable` | 🔴 Missing | - |

#### `NiagaraToolset_Info` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `UEnum_Info` | 🟢 Available | `NiagaraToolsets.NiagaraToolset_Info.UEnum_Info` |

#### `NiagaraToolset_System` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddEmitter` | 🔴 Missing | - |
| `AddModule` | 🔴 Missing | - |
| `AddRenderer` | 🔴 Missing | - |
| `AddSetParameterEntry` | 🔴 Missing | - |
| `AddSetParametersModule` | 🔴 Missing | - |
| `AddUserVariables` | 🔴 Missing | - |
| `ApplyStackIssueFix` | 🔴 Missing | - |
| `CreateNiagaraSystem` | 🔴 Missing | - |
| `GetAvailableDynamicInputs` | 🔴 Missing | - |
| `GetDataInterfaceSchema` | 🔴 Missing | - |
| `GetDynamicInputChain` | 🔴 Missing | - |
| `GetDynamicInputSchema` | 🔴 Missing | - |
| `GetDynamicInputSchemaFromAsset` | 🔴 Missing | - |
| `GetEmitterData` | 🔴 Missing | - |
| `GetEmitterInputValues` | 🔴 Missing | - |
| `GetEmitterSchema` | 🔴 Missing | - |
| `GetEmitterSummary` | 🔴 Missing | - |
| `GetEmitterTopology` | 🔴 Missing | - |
| `GetModuleInputValues` | 🔴 Missing | - |
| `GetModuleSchema` | 🔴 Missing | - |
| `GetModuleSchemaFromAsset` | 🔴 Missing | - |
| `GetModuleTopology` | 🔴 Missing | - |
| `GetRendererData` | 🔴 Missing | - |
| `GetRendererSchema` | 🔴 Missing | - |
| `GetScriptStackInputValues` | 🔴 Missing | - |
| `GetScriptStackTopology` | 🔴 Missing | - |
| `GetStackInputData` | 🔴 Missing | - |
| `GetStackInputSchema` | 🔴 Missing | - |
| `GetStackInputTopology` | 🔴 Missing | - |
| `GetStackIssues` | 🔴 Missing | - |
| `GetSystemCompileState` | 🔴 Missing | - |
| `GetSystemData` | 🔴 Missing | - |
| `GetSystemDependencies` | 🔴 Missing | - |
| `GetSystemSchema` | 🔴 Missing | - |
| `GetSystemSummary` | 🔴 Missing | - |
| `GetUserVariables` | 🔴 Missing | - |
| `RemoveEmitter` | 🔴 Missing | - |
| `RemoveModule` | 🔴 Missing | - |
| `RemoveRenderer` | 🔴 Missing | - |
| `RemoveSetParameterEntry` | 🔴 Missing | - |
| `RemoveUserVariables` | 🔴 Missing | - |
| `SetEmitterData` | 🔴 Missing | - |
| `SetModuleEnabled` | 🔴 Missing | - |
| `SetRendererData` | 🔴 Missing | - |
| `SetStackInputData` | 🔴 Missing | - |
| `SetSystemData` | 🔴 Missing | - |

### AutomationTestToolset

#### `AutomationTestToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `DiscoverTests` | 🟢 Available | `AutomationTestToolset.AutomationTestToolset.DiscoverTests` |
| `GetTestResults` | 🟢 Available | `AutomationTestToolset.AutomationTestToolset.GetTestResults` |
| `GetTestStatus` | 🟢 Available | `AutomationTestToolset.AutomationTestToolset.GetTestStatus` |
| `ListTests` | 🟢 Available | `AutomationTestToolset.AutomationTestToolset.ListTests` |
| `RunTests` | 🟢 Available | `AutomationTestToolset.AutomationTestToolset.RunTests` |
| `RunTestsByFilter` | 🟢 Available | `AutomationTestToolset.AutomationTestToolset.RunTestsByFilter` |
| `StopTests` | 🟢 Available | `AutomationTestToolset.AutomationTestToolset.StopTests` |

### AIModuleToolset

#### `BehaviorTreeTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `get_blackboard` | 🟢 Available | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools.get_blackboard` |
| `get_children` | 🟢 Available | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools.get_children` |
| `get_node_depth` | 🟢 Available | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools.get_node_depth` |
| `get_node_depths` | 🟢 Available | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools.get_node_depths` |
| `get_root_decorators` | 🟢 Available | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools.get_root_decorators` |
| `get_subtree` | 🟢 Available | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools.get_subtree` |
| `list_nodes` | 🟢 Available | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools.list_nodes` |

### AnimationAssistantToolset

> Port denemesi: UE 5.8 source-only/plugin Python content kopyası build'e sokuldu ve C++ build geçti.
> MCP health sırasında Python registration `ControlRigTools` üzerinde durdu:
> `RigElementType` enum parametresi için default `None` UE 5.7 Python'da native enum property'ye çevrilemiyor.
> Aynı Python yüzeyinde çok sayıda typed `None` default ve geniş ControlRig/Sequencer editor API kullanımı var.
> 305 tool'luk yüzeyi tek tek signature yamalamak patch zinciri olacağı için rollback edildi.
> A clean solution needs a separate capability-grouped Python/C++ bridge architecture.

#### `ControlRigTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_backward_solve_graph` | 🔴 Missing | - |
| `add_bone` | 🔴 Missing | - |
| `add_control` | 🔴 Missing | - |
| `add_element` | 🔴 Missing | - |
| `add_event_graph` | 🔴 Missing | - |
| `add_event_node` | 🔴 Missing | - |
| `add_graph` | 🔴 Missing | - |
| `add_interaction_graph` | 🔴 Missing | - |
| `add_null` | 🔴 Missing | - |
| `add_variable` | 🔴 Missing | - |
| `add_variable_node` | 🔴 Missing | - |
| `change_variable_type` | 🔴 Missing | - |
| `connect_pins` | 🔴 Missing | - |
| `create` | 🔴 Missing | - |
| `create_node` | 🔴 Missing | - |
| `delete_node` | 🔴 Missing | - |
| `disconnect_pins` | 🔴 Missing | - |
| `get_all_bones` | 🔴 Missing | - |
| `get_all_controls` | 🔴 Missing | - |
| `get_all_nulls` | 🔴 Missing | - |
| `get_backward_solve_graph` | 🔴 Missing | - |
| `get_children` | 🔴 Missing | - |
| `get_connected_pins` | 🔴 Missing | - |
| `get_elements` | 🔴 Missing | - |
| `get_event_graph` | 🔴 Missing | - |
| `get_forward_solve_graph` | 🔴 Missing | - |
| `get_global_transform` | 🔴 Missing | - |
| `get_graph` | 🔴 Missing | - |
| `get_interaction_graph` | 🔴 Missing | - |
| `get_local_transform` | 🔴 Missing | - |
| `get_node_position` | 🔴 Missing | - |
| `get_parent` | 🔴 Missing | - |
| `get_pin_value` | 🔴 Missing | - |
| `get_variable` | 🔴 Missing | - |
| `import_bones_from_asset` | 🔴 Missing | - |
| `list_graphs` | 🔴 Missing | - |
| `list_nodes` | 🔴 Missing | - |
| `list_pins` | 🔴 Missing | - |
| `list_variables` | 🔴 Missing | - |
| `remove_variable` | 🔴 Missing | - |
| `set_global_transform` | 🔴 Missing | - |
| `set_local_transform` | 🔴 Missing | - |
| `set_node_position` | 🔴 Missing | - |
| `set_pin_value` | 🔴 Missing | - |

#### `SequencerConditionTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `clear_section_condition` | 🔴 Missing | - |
| `clear_track_condition` | 🔴 Missing | - |
| `clear_track_row_condition` | 🔴 Missing | - |
| `get_section_condition` | 🔴 Missing | - |
| `get_track_condition` | 🔴 Missing | - |
| `get_track_row_condition` | 🔴 Missing | - |
| `set_section_condition` | 🔴 Missing | - |
| `set_track_condition` | 🔴 Missing | - |
| `set_track_row_condition` | 🔴 Missing | - |

#### `SequencerControlRigTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_layer_from_selection` | 🔴 Missing | - |
| `bake_space` | 🔴 Missing | - |
| `bake_to_control_rig` | 🔴 Missing | - |
| `blend_values_on_selected` | 🔴 Missing | - |
| `clear_selection` | 🔴 Missing | - |
| `collapse_anim_layers` | 🔴 Missing | - |
| `delete_anim_layer` | 🔴 Missing | - |
| `delete_space` | 🔴 Missing | - |
| `duplicate_anim_layer` | 🔴 Missing | - |
| `export_fbx_from_rig` | 🔴 Missing | - |
| `find_or_create_track` | 🔴 Missing | - |
| `frame_selection` | 🔴 Missing | - |
| `get_actor_transform_at_frame` | 🔴 Missing | - |
| `get_anim_layers` | 🔴 Missing | - |
| `get_anim_mode_gizmo_scale` | 🔴 Missing | - |
| `get_anim_mode_hide_manips` | 🔴 Missing | - |
| `get_anim_mode_hierarchy` | 🔴 Missing | - |
| `get_anim_mode_local_spaces` | 🔴 Missing | - |
| `get_anim_mode_nulls` | 🔴 Missing | - |
| `get_anim_mode_only_rig_sel` | 🔴 Missing | - |
| `get_bool` | 🔴 Missing | - |
| `get_control_rigs` | 🔴 Missing | - |
| `get_controls_info` | 🔴 Missing | - |
| `get_controls_mask` | 🔴 Missing | - |
| `get_euler_transform` | 🔴 Missing | - |
| `get_float` | 🔴 Missing | - |
| `get_int` | 🔴 Missing | - |
| `get_position` | 🔴 Missing | - |
| `get_priority_order` | 🔴 Missing | - |
| `get_rotator` | 🔴 Missing | - |
| `get_scale` | 🔴 Missing | - |
| `get_selected_controls` | 🔴 Missing | - |
| `get_transform` | 🔴 Missing | - |
| `get_vector2d` | 🔴 Missing | - |
| `get_world_transform` | 🔴 Missing | - |
| `hide_all_controls` | 🔴 Missing | - |
| `import_fbx_to_rig` | 🔴 Missing | - |
| `is_fk_control_rig` | 🔴 Missing | - |
| `is_layered_control_rig` | 🔴 Missing | - |
| `key_controls` | 🔴 Missing | - |
| `key_controls_at_frames` | 🔴 Missing | - |
| `load_anim_into_rig` | 🔴 Missing | - |
| `merge_anim_layers` | 🔴 Missing | - |
| `mirror_selected_controls` | 🔴 Missing | - |
| `move_space` | 🔴 Missing | - |
| `reorder_anim_layers` | 🔴 Missing | - |
| `select_control` | 🔴 Missing | - |
| `select_mirrored_controls` | 🔴 Missing | - |
| `set_anim_mode_gizmo_scale` | 🔴 Missing | - |
| `set_anim_mode_hide_manips` | 🔴 Missing | - |
| `set_anim_mode_hierarchy` | 🔴 Missing | - |
| `set_anim_mode_local_spaces` | 🔴 Missing | - |
| `set_anim_mode_nulls` | 🔴 Missing | - |
| `set_anim_mode_only_rig_sel` | 🔴 Missing | - |
| `set_bool` | 🔴 Missing | - |
| `set_controls_mask` | 🔴 Missing | - |
| `set_euler_transform` | 🔴 Missing | - |
| `set_float` | 🔴 Missing | - |
| `set_int` | 🔴 Missing | - |
| `set_layered_mode` | 🔴 Missing | - |
| `set_position` | 🔴 Missing | - |
| `set_priority_order` | 🔴 Missing | - |
| `set_rotator` | 🔴 Missing | - |
| `set_scale` | 🔴 Missing | - |
| `set_space` | 🔴 Missing | - |
| `set_transform` | 🔴 Missing | - |
| `set_vector2d` | 🔴 Missing | - |
| `set_world_transform` | 🔴 Missing | - |
| `show_all_controls` | 🔴 Missing | - |
| `snap_control_rig` | 🔴 Missing | - |
| `tween_control_rig` | 🔴 Missing | - |
| `zero_transforms` | 🔴 Missing | - |

#### `SequencerCustomBindingTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `change_actor_template_class` | 🔴 Missing | - |
| `convert_to_custom_binding` | 🔴 Missing | - |
| `convert_to_possessable` | 🔴 Missing | - |
| `convert_to_spawnable` | 🔴 Missing | - |
| `get_custom_binding_objects` | 🔴 Missing | - |
| `get_custom_binding_type` | 🔴 Missing | - |
| `get_custom_bindings_of_type` | 🔴 Missing | - |
| `save_default_spawnable_state` | 🔴 Missing | - |

#### `SequencerImportExportTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `export_anim_sequence` | 🔴 Missing | - |
| `export_fbx` | 🔴 Missing | - |
| `get_linked_anim_sequences` | 🔴 Missing | - |
| `get_linked_level_sequence` | 🔴 Missing | - |
| `import_fbx` | 🔴 Missing | - |
| `link_anim_sequence` | 🔴 Missing | - |

#### `SequencerKeyframingTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_key_bool` | 🔴 Missing | - |
| `add_key_float` | 🔴 Missing | - |
| `add_key_integer` | 🔴 Missing | - |
| `add_key_string` | 🔴 Missing | - |
| `bake_channel_keys` | 🔴 Missing | - |
| `close_curve_editor` | 🔴 Missing | - |
| `curve_editor_empty_selection` | 🔴 Missing | - |
| `curve_editor_select_keys` | 🔴 Missing | - |
| `get_channel_names` | 🔴 Missing | - |
| `get_curve_editor_selected_keys` | 🔴 Missing | - |
| `get_default_value` | 🔴 Missing | - |
| `get_keys` | 🔴 Missing | - |
| `get_keys_by_index` | 🔴 Missing | - |
| `get_selected_channels` | 🔴 Missing | - |
| `get_selected_key_channels` | 🔴 Missing | - |
| `is_curve_editor_open` | 🔴 Missing | - |
| `is_curve_shown` | 🔴 Missing | - |
| `open_curve_editor` | 🔴 Missing | - |
| `remove_key_at_frame` | 🔴 Missing | - |
| `select_channels` | 🔴 Missing | - |
| `set_default_value` | 🔴 Missing | - |
| `show_curve` | 🔴 Missing | - |

#### `SequencerOutlinerTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `get_deactivated_nodes` | 🔴 Missing | - |
| `get_locked_nodes` | 🔴 Missing | - |
| `get_muted_nodes` | 🔴 Missing | - |
| `get_node_label` | 🔴 Missing | - |
| `get_outliner_children` | 🔴 Missing | - |
| `get_outliner_selection` | 🔴 Missing | - |
| `get_outliner_tree` | 🔴 Missing | - |
| `get_pinned_nodes` | 🔴 Missing | - |
| `get_sections_for_nodes` | 🔴 Missing | - |
| `get_soloed_nodes` | 🔴 Missing | - |
| `is_node_expanded` | 🔴 Missing | - |
| `set_node_deactivated` | 🔴 Missing | - |
| `set_node_expanded` | 🔴 Missing | - |
| `set_node_locked` | 🔴 Missing | - |
| `set_node_muted` | 🔴 Missing | - |
| `set_node_pinned` | 🔴 Missing | - |
| `set_node_solo` | 🔴 Missing | - |
| `set_outliner_selection` | 🔴 Missing | - |

#### `SequencerTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_actors` | 🔴 Missing | - |
| `add_actors_by_name` | 🔴 Missing | - |
| `add_actors_to_binding` | 🔴 Missing | - |
| `add_binding_to_folder` | 🔴 Missing | - |
| `add_event_repeater_section` | 🔴 Missing | - |
| `add_event_trigger_section` | 🔴 Missing | - |
| `add_marked_frame` | 🔴 Missing | - |
| `add_root_folder` | 🔴 Missing | - |
| `add_section` | 🔴 Missing | - |
| `add_spawnable_from_class` | 🔴 Missing | - |
| `add_spawnable_from_instance` | 🔴 Missing | - |
| `add_track_to_binding` | 🔴 Missing | - |
| `add_track_to_folder` | 🔴 Missing | - |
| `add_track_to_sequence` | 🔴 Missing | - |
| `bake_transform` | 🔴 Missing | - |
| `close_sequence` | 🔴 Missing | - |
| `copy_bindings` | 🔴 Missing | - |
| `copy_folders` | 🔴 Missing | - |
| `copy_sections` | 🔴 Missing | - |
| `copy_tracks` | 🔴 Missing | - |
| `create_camera` | 🔴 Missing | - |
| `create_level_sequence` | 🔴 Missing | - |
| `delete_all_marked_frames` | 🔴 Missing | - |
| `delete_marked_frame` | 🔴 Missing | - |
| `empty_selection` | 🔴 Missing | - |
| `find_binding_by_name` | 🔴 Missing | - |
| `find_binding_by_tag` | 🔴 Missing | - |
| `find_bindings_by_tag` | 🔴 Missing | - |
| `find_marked_frame_by_label` | 🔴 Missing | - |
| `find_tracks_by_type` | 🔴 Missing | - |
| `fix_actor_references` | 🔴 Missing | - |
| `focus_parent_sequence` | 🔴 Missing | - |
| `focus_sub_sequence` | 🔴 Missing | - |
| `force_evaluate` | 🔴 Missing | - |
| `get_all_binding_tags` | 🔴 Missing | - |
| `get_binding_id` | 🔴 Missing | - |
| `get_binding_name` | 🔴 Missing | - |
| `get_binding_tags` | 🔴 Missing | - |
| `get_bindings` | 🔴 Missing | - |
| `get_bound_objects` | 🔴 Missing | - |
| `get_child_possessables` | 🔴 Missing | - |
| `get_clock_source` | 🔴 Missing | - |
| `get_current_sequence` | 🔴 Missing | - |
| `get_display_rate` | 🔴 Missing | - |
| `get_evaluation_type` | 🔴 Missing | - |
| `get_focused_sequence` | 🔴 Missing | - |
| `get_folder_contents` | 🔴 Missing | - |
| `get_loop_mode` | 🔴 Missing | - |
| `get_marked_frames` | 🔴 Missing | - |
| `get_playback_range` | 🔴 Missing | - |
| `get_playback_speed` | 🔴 Missing | - |
| `get_playhead_frame` | 🔴 Missing | - |
| `get_root_folders` | 🔴 Missing | - |
| `get_section_blend_type` | 🔴 Missing | - |
| `get_section_completion_mode` | 🔴 Missing | - |
| `get_section_ease_in` | 🔴 Missing | - |
| `get_section_ease_out` | 🔴 Missing | - |
| `get_section_post_roll_frames` | 🔴 Missing | - |
| `get_section_pre_roll_frames` | 🔴 Missing | - |
| `get_section_properties` | 🔴 Missing | - |
| `get_section_range` | 🔴 Missing | - |
| `get_section_to_key` | 🔴 Missing | - |
| `get_sections` | 🔴 Missing | - |
| `get_selected_bindings` | 🔴 Missing | - |
| `get_selected_folders` | 🔴 Missing | - |
| `get_selected_sections` | 🔴 Missing | - |
| `get_selected_tracks` | 🔴 Missing | - |
| `get_selection_range` | 🔴 Missing | - |
| `get_sequence_lock_state` | 🔴 Missing | - |
| `get_sub_sequence_hierarchy` | 🔴 Missing | - |
| `get_tick_resolution` | 🔴 Missing | - |
| `get_track_display_name` | 🔴 Missing | - |
| `get_track_filter_names` | 🔴 Missing | - |
| `get_tracks_on_binding` | 🔴 Missing | - |
| `get_tracks_on_sequence` | 🔴 Missing | - |
| `get_view_range` | 🔴 Missing | - |
| `get_work_range` | 🔴 Missing | - |
| `has_section_end_frame` | 🔴 Missing | - |
| `has_section_start_frame` | 🔴 Missing | - |
| `is_camera_cut_locked` | 🔴 Missing | - |
| `is_playback_range_locked` | 🔴 Missing | - |
| `is_playing` | 🔴 Missing | - |
| `is_sequence_locked` | 🔴 Missing | - |
| `is_track_filter_active` | 🔴 Missing | - |
| `open_sequence` | 🔴 Missing | - |
| `paste_bindings` | 🔴 Missing | - |
| `paste_folders` | 🔴 Missing | - |
| `paste_sections` | 🔴 Missing | - |
| `paste_tracks` | 🔴 Missing | - |
| `pause` | 🔴 Missing | - |
| `play` | 🔴 Missing | - |
| `play_to` | 🔴 Missing | - |
| `rebind_component` | 🔴 Missing | - |
| `refresh_sequence` | 🔴 Missing | - |
| `remove_actors_from_binding` | 🔴 Missing | - |
| `remove_all_bindings` | 🔴 Missing | - |
| `remove_binding` | 🔴 Missing | - |
| `remove_binding_tag` | 🔴 Missing | - |
| `remove_invalid_bindings` | 🔴 Missing | - |
| `remove_root_folder` | 🔴 Missing | - |
| `remove_section` | 🔴 Missing | - |
| `remove_track` | 🔴 Missing | - |
| `remove_track_from_sequence` | 🔴 Missing | - |
| `replace_binding_with_actors` | 🔴 Missing | - |
| `select_bindings` | 🔴 Missing | - |
| `select_folders` | 🔴 Missing | - |
| `select_sections` | 🔴 Missing | - |
| `select_tracks` | 🔴 Missing | - |
| `set_binding_name` | 🔴 Missing | - |
| `set_byte_track_enum` | 🔴 Missing | - |
| `set_camera_cut_binding` | 🔴 Missing | - |
| `set_camera_lock` | 🔴 Missing | - |
| `set_clock_source` | 🔴 Missing | - |
| `set_display_rate` | 🔴 Missing | - |
| `set_evaluation_type` | 🔴 Missing | - |
| `set_loop_mode` | 🔴 Missing | - |
| `set_playback_range` | 🔴 Missing | - |
| `set_playback_range_locked` | 🔴 Missing | - |
| `set_playback_speed` | 🔴 Missing | - |
| `set_playhead_frame` | 🔴 Missing | - |
| `set_property_name_and_path` | 🔴 Missing | - |
| `set_section_animation` | 🔴 Missing | - |
| `set_section_blend_type` | 🔴 Missing | - |
| `set_section_completion_mode` | 🔴 Missing | - |
| `set_section_ease_in` | 🔴 Missing | - |
| `set_section_ease_out` | 🔴 Missing | - |
| `set_section_end_bounded` | 🔴 Missing | - |
| `set_section_post_roll_frames` | 🔴 Missing | - |
| `set_section_pre_roll_frames` | 🔴 Missing | - |
| `set_section_range` | 🔴 Missing | - |
| `set_section_start_bounded` | 🔴 Missing | - |
| `set_selection_range` | 🔴 Missing | - |
| `set_sequence_locked` | 🔴 Missing | - |
| `set_tick_resolution` | 🔴 Missing | - |
| `set_track_display_name` | 🔴 Missing | - |
| `set_track_filter_active` | 🔴 Missing | - |
| `set_view_range` | 🔴 Missing | - |
| `set_work_range` | 🔴 Missing | - |
| `tag_binding` | 🔴 Missing | - |
| `untag_binding` | 🔴 Missing | - |

### ChaosClothAssetToolset

#### `ChaosClothAssetToolset` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AssignClothingToSection` | 🔴 Missing | - |
| `ConvertClothingAssetCommonToChaosClothAsset` | 🔴 Missing | - |
| `CreateClothingAsset` | 🔴 Missing | - |
| `GetSectionClothing` | 🔴 Missing | - |
| `ListClothingAssets` | 🔴 Missing | - |
| `RemoveClothingFromSection` | 🔴 Missing | - |

### ConfigSettingsToolset

#### `ConfigSettingsToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `GetSectionPropertyValues` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.GetSectionPropertyValues` |
| `GetSectionSchema` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.GetSectionSchema` |
| `ListCategories` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.ListCategories` |
| `ListContainers` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.ListContainers` |
| `ListSections` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.ListSections` |
| `ResetSectionToDefaults` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.ResetSectionToDefaults` |
| `SaveSection` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.SaveSection` |
| `SetSectionProperties` | 🟢 Available | `ConfigSettingsToolset.ConfigSettingsToolset.SetSectionProperties` |

### ConversationToolset

#### `ConversationTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `get_all_nodes` | 🟢 Available | `conversation_toolset.toolsets.conversation.ConversationTools.get_all_nodes` |
| `get_node_by_guid` | 🟢 Available | `conversation_toolset.toolsets.conversation.ConversationTools.get_node_by_guid` |
| `get_node_connections` | 🟢 Available | `conversation_toolset.toolsets.conversation.ConversationTools.get_node_connections` |
| `get_node_guids` | 🟢 Available | `conversation_toolset.toolsets.conversation.ConversationTools.get_node_guids` |
| `get_sub_nodes` | 🟢 Available | `conversation_toolset.toolsets.conversation.ConversationTools.get_sub_nodes` |
| `list_entry_points` | 🟢 Available | `conversation_toolset.toolsets.conversation.ConversationTools.list_entry_points` |
| `list_speakers` | 🟢 Available | `conversation_toolset.toolsets.conversation.ConversationTools.list_speakers` |

### DataflowAgent

#### `DataflowAgentToolset` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddCommentBox` | 🔴 Missing | - |
| `AddNode` | 🔴 Missing | - |
| `AddVariable` | 🔴 Missing | - |
| `AssignDataflowTemplate` | 🔴 Missing | - |
| `ConnectNodePins` | 🔴 Missing | - |
| `CreateDataflowCompatibleAsset` | 🔴 Missing | - |
| `CreateDataflowCompatibleAssetFromTemplate` | 🔴 Missing | - |
| `CreateGraph` | 🔴 Missing | - |
| `DisconnectNodePins` | 🔴 Missing | - |
| `GetGraphStructure` | 🔴 Missing | - |
| `GetNodeInfo` | 🔴 Missing | - |
| `GetNodeTypeSchema` | 🔴 Missing | - |
| `ListDataflowCompatibleAssetTypes` | 🔴 Missing | - |
| `ListDataflowTemplatesForAssetClass` | 🔴 Missing | - |
| `ListNodeTypes` | 🔴 Missing | - |
| `ListVariables` | 🔴 Missing | - |
| `RemoveCommentBox` | 🔴 Missing | - |
| `RemoveNode` | 🔴 Missing | - |
| `RemoveVariable` | 🔴 Missing | - |
| `RepositionNode` | 🔴 Missing | - |
| `SetVariable` | 🔴 Missing | - |
| `UpdateNode` | 🔴 Missing | - |

> Port denemesi: UE 5.8 source-only kopya build'e sokuldu. İlk bloklayıcı fark `Dataflow/DataflowAssetEditUtils.h`.
> UE 5.7'de bu API yalnızca `DataflowEditor/Private` altında, UE 5.8'de Public API. Private engine header'a
> project plugin bağlamak temiz mimari olmadığı için kademe rollback edildi. Engine patch uygulanmadı.

### DataRegistryToolset

#### `DataRegistryTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `GetItems` | 🟢 Available | `DataRegistryToolset.DataRegistryTools.GetItems` |
| `GetRegistryInfo` | 🟢 Available | `DataRegistryToolset.DataRegistryTools.GetRegistryInfo` |
| `GetSchema` | 🟢 Available | `DataRegistryToolset.DataRegistryTools.GetSchema` |
| `ListDataSources` | 🟢 Available | `DataRegistryToolset.DataRegistryTools.ListDataSources` |
| `ListItems` | 🟢 Available | `DataRegistryToolset.DataRegistryTools.ListItems` |
| `ListRegistries` | 🟢 Available | `DataRegistryToolset.DataRegistryTools.ListRegistries` |
| `ListRuntimeSources` | 🟢 Available | `DataRegistryToolset.DataRegistryTools.ListRuntimeSources` |

### GameFeaturesToolset

#### `GameFeaturesToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `GetGameFeatureState` | 🟢 Available | `GameFeaturesToolset.GameFeaturesToolset.GetGameFeatureState` |
| `IsGameFeatureActive` | 🟢 Available | `GameFeaturesToolset.GameFeaturesToolset.IsGameFeatureActive` |
| `IsGameFeaturePlugin` | 🟢 Available | `GameFeaturesToolset.GameFeaturesToolset.IsGameFeaturePlugin` |
| `ListDiscoveredGameFeaturePlugins` | 🟢 Available | `GameFeaturesToolset.GameFeaturesToolset.ListDiscoveredGameFeaturePlugins` |
| `ListEnabledGameFeaturePlugins` | 🟢 Available | `GameFeaturesToolset.GameFeaturesToolset.ListEnabledGameFeaturePlugins` |
| `RequestActivateGameFeature` | 🟢 Available | `GameFeaturesToolset.GameFeaturesToolset.RequestActivateGameFeature` |
| `RequestDeactivateGameFeature` | 🟢 Available | `GameFeaturesToolset.GameFeaturesToolset.RequestDeactivateGameFeature` |

### LiveCodingToolset

#### `LiveCodingToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `CompileLiveCoding` | 🟢 Available | `LiveCodingToolset.LiveCodingToolset.CompileLiveCoding` |

### MetaHumanGenerator

#### `MetaHumanToolset` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `begin_edit` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `create` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `end_edit` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `get_body_shape` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `get_eye_color` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `get_skin_tone` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `set_body_shape` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `set_eye_color` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |
| `set_skin_tone` | 🔴 Missing | 5.8 Python requires `unreal.MetaHumanGeneratorSubsystemWrapper`; UE 5.7 does not expose it. |

Note: this toolset previously appeared available in the report. The failure was hidden because it did not break compilation. MCP probe confirmed a Python startup `AttributeError`. Disabled by default in PortKit installs. A separate native C++ MetaHuman bridge is required to make it usable.

### MVVMToolset

#### `MVVMToolset` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddViewModelProperty` | 🔴 Missing | - |
| `AddViewModelToWidget` | 🔴 Missing | - |
| `CreateViewBinding` | 🔴 Missing | - |
| `CreateViewModel` | 🔴 Missing | - |
| `ListConversionFunctions` | 🔴 Missing | - |
| `ListViewModels` | 🔴 Missing | - |
| `ListWidgetViewBindings` | 🔴 Missing | - |
| `ListWidgetViewModels` | 🔴 Missing | - |
| `RemoveWidgetViewBinding` | 🔴 Missing | - |

### PCGToolset

> Port notu: UE 5.8 PCGToolset source-only olarak `Plugins/PCGToolset/` altına portlanmıştır.
> Engine source patch yoktur. Health JSON sonucu `pass`: `PCGToolset.PCGToolset` 30 tool,
> `PCGToolset.PCGSpatialToolset` 1 tool göstermektedir. `GetNodeDataView` UE 5.7 inspection data + point-data serializer
> adapter ile açıldı. `DrawSpline` interactive editor mode yerine explicit point listesi alan headless spline actor adapter ile açıldı.

#### `PCGSpatialToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `RunPCGInstantGraph` | 🟢 Available | `PCGToolset.PCGSpatialToolset.RunPCGInstantGraph` |

#### `PCGToolset` - 🟢 COMPLETE (30/30)

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddCommentBox` | 🟢 Available | `PCGToolset.PCGToolset.AddCommentBox` |
| `AddNode` | 🟢 Available | `PCGToolset.PCGToolset.AddNode` |
| `AddSubgraphNode` | 🟢 Available | `PCGToolset.PCGToolset.AddSubgraphNode` |
| `ConnectNodePins` | 🟢 Available | `PCGToolset.PCGToolset.ConnectNodePins` |
| `CreateGraph` | 🟢 Available | `PCGToolset.PCGToolset.CreateGraph` |
| `DisconnectNodePins` | 🟢 Available | `PCGToolset.PCGToolset.DisconnectNodePins` |
| `DrawSpline` | 🟢 Available | `PCGToolset.PCGToolset.DrawSpline` |
| `ExecuteGraphInstance` | 🟢 Available | `PCGToolset.PCGToolset.ExecuteGraphInstance` |
| `GetGraphDescription` | 🟢 Available | `PCGToolset.PCGToolset.GetGraphDescription` |
| `GetGraphInstanceParams` | 🟢 Available | `PCGToolset.PCGToolset.GetGraphInstanceParams` |
| `GetGraphSchema` | 🟢 Available | `PCGToolset.PCGToolset.GetGraphSchema` |
| `GetGraphStructure` | 🟢 Available | `PCGToolset.PCGToolset.GetGraphStructure` |
| `GetNativeNodeSchema` | 🟢 Available | `PCGToolset.PCGToolset.GetNativeNodeSchema` |
| `GetNodeDataView` | 🟢 Available | `PCGToolset.PCGToolset.GetNodeDataView` |
| `GetNodeInfo` | 🟢 Available | `PCGToolset.PCGToolset.GetNodeInfo` |
| `ListAvailableSubgraphs` | 🟢 Available | `PCGToolset.PCGToolset.ListAvailableSubgraphs` |
| `ListGraphInstances` | 🟢 Available | `PCGToolset.PCGToolset.ListGraphInstances` |
| `ListNativeNodes` | 🟢 Available | `PCGToolset.PCGToolset.ListNativeNodes` |
| `RemoveCommentBox` | 🟢 Available | `PCGToolset.PCGToolset.RemoveCommentBox` |
| `RemoveGraphParams` | 🟢 Available | `PCGToolset.PCGToolset.RemoveGraphParams` |
| `RemoveNode` | 🟢 Available | `PCGToolset.PCGToolset.RemoveNode` |
| `RepositionNode` | 🟢 Available | `PCGToolset.PCGToolset.RepositionNode` |
| `ResetGraphInstanceParams` | 🟢 Available | `PCGToolset.PCGToolset.ResetGraphInstanceParams` |
| `SetGraphDescription` | 🟢 Available | `PCGToolset.PCGToolset.SetGraphDescription` |
| `SetGraphInstanceParams` | 🟢 Available | `PCGToolset.PCGToolset.SetGraphInstanceParams` |
| `SetGraphParams` | 🟢 Available | `PCGToolset.PCGToolset.SetGraphParams` |
| `SetNodeComment` | 🟢 Available | `PCGToolset.PCGToolset.SetNodeComment` |
| `SpawnGraphInstance` | 🟢 Available | `PCGToolset.PCGToolset.SpawnGraphInstance` |
| `UpdateCommentBox` | 🟢 Available | `PCGToolset.PCGToolset.UpdateCommentBox` |
| `UpdateNode` | 🟢 Available | `PCGToolset.PCGToolset.UpdateNode` |

> 5.7 adaptasyon notları: `RaiseScriptError` 5.7'de linklenmediği için lokal
> `FFrame::KismetExecutionMessage` bridge'i kullanıldı; `EPCGChangeType::ExternalModification` 5.7'de
> olmadığı için `Structural`; `UPCGEdge` 5.7'de `Get*Node/Get*PinLabel` barındırmadığı için edge'ler pin
> üzerinden traverse edildi; spatial execution 5.7 `UPCGEngineSubsystem::GenerateGraph(FPCGGenerateGraphParams)`
> yoluna map edildi. `GetNodeDataView` için 5.8 `PCGDataView` JSON converter backport edilmedi; 5.7 `FPCGGraphExecutionInspection`
> cache'i ve `UPCGBasePointData` built-in point alanları üzerinden deterministic JSON adapter yazıldı.
> `DrawSpline` için 5.8'in `pcg.EnableTool` / interactive editor mode akışı kullanılmadı; headless MCP uyumu için
> explicit `Points` parametresiyle `AActor + USplineComponent` adapter yazıldı. Engine source patch uygulanmadı.

### PhysicsToolsets

#### `PhysicsAssetToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddBody` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.AddBody` |
| `AddConstraint` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.AddConstraint` |
| `CreateFromMesh` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.CreateFromMesh` |
| `GetBodyMassScale` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.GetBodyMassScale` |
| `GetBodyNames` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.GetBodyNames` |
| `GetBodyPhysicsMode` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.GetBodyPhysicsMode` |
| `GetBodyShapes` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.GetBodyShapes` |
| `GetConstraints` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.GetConstraints` |
| `RemoveBody` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.RemoveBody` |
| `RemoveConstraint` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.RemoveConstraint` |
| `RemoveShape` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.RemoveShape` |
| `SetBodyMassScale` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.SetBodyMassScale` |
| `SetBodyPhysicsMode` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.SetBodyPhysicsMode` |
| `SetBox` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.SetBox` |
| `SetCapsule` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.SetCapsule` |
| `SetConstraintLimits` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.SetConstraintLimits` |
| `SetSphere` | 🟢 Available | `PhysicsToolsets.PhysicsAssetToolset.SetSphere` |

### PluginToolset

#### `PluginToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `AddPluginDependency` | 🟢 Available | `PluginToolset.PluginToolset.AddPluginDependency` |
| `CreatePlugin` | 🟢 Available | `PluginToolset.PluginToolset.CreatePlugin` |
| `GetPluginDependencies` | 🟢 Available | `PluginToolset.PluginToolset.GetPluginDependencies` |
| `GetPluginDependents` | 🟢 Available | `PluginToolset.PluginToolset.GetPluginDependents` |
| `GetPluginDescriptor` | 🟢 Available | `PluginToolset.PluginToolset.GetPluginDescriptor` |
| `GetPluginForAsset` | 🟢 Available | `PluginToolset.PluginToolset.GetPluginForAsset` |
| `GetPluginInfo` | 🟢 Available | `PluginToolset.PluginToolset.GetPluginInfo` |
| `GetPluginTemplateDescriptions` | 🟢 Available | `PluginToolset.PluginToolset.GetPluginTemplateDescriptions` |
| `IsEnabled` | 🟢 Available | `PluginToolset.PluginToolset.IsEnabled` |
| `IsPluginCreationAllowed` | 🟢 Available | `PluginToolset.PluginToolset.IsPluginCreationAllowed` |
| `IsPluginModificationAllowed` | 🟢 Available | `PluginToolset.PluginToolset.IsPluginModificationAllowed` |
| `ListDiscoveredPlugins` | 🟢 Available | `PluginToolset.PluginToolset.ListDiscoveredPlugins` |
| `ListEnabledPlugins` | 🟢 Available | `PluginToolset.PluginToolset.ListEnabledPlugins` |
| `RemovePluginDependency` | 🟢 Available | `PluginToolset.PluginToolset.RemovePluginDependency` |
| `SetPluginEnabled` | 🟢 Available | `PluginToolset.PluginToolset.SetPluginEnabled` |
| `UpdatePluginDescriptor` | 🟢 Available | `PluginToolset.PluginToolset.UpdatePluginDescriptor` |
| `ValidateNewPluginNameAndLocation` | 🟢 Available | `PluginToolset.PluginToolset.ValidateNewPluginNameAndLocation` |

### SemanticSearchToolset

#### `SemanticSearchToolset` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `FindSimilar` | 🔴 Missing | - |
| `Search` | 🔴 Missing | - |

### SequencerAnimMixerToolset

#### `SequencerAnimMixerTools` - 🔴 MISSING

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `add_animation_to_mixer` | 🔴 Missing | - |
| `add_child_track_to_layer` | 🔴 Missing | - |
| `add_decoration` | 🔴 Missing | - |
| `add_mixer_layer` | 🔴 Missing | - |
| `change_transition_type` | 🔴 Missing | - |
| `find_decoration` | 🔴 Missing | - |
| `get_compatible_decorations` | 🔴 Missing | - |
| `get_decorations` | 🔴 Missing | - |
| `get_layer_index` | 🔴 Missing | - |
| `get_layer_name` | 🔴 Missing | - |
| `get_layer_sections` | 🔴 Missing | - |
| `get_mixer_layer_count` | 🔴 Missing | - |
| `get_mixer_layers` | 🔴 Missing | - |
| `get_transition_between` | 🔴 Missing | - |
| `get_transition_info` | 🔴 Missing | - |
| `get_transition_name` | 🔴 Missing | - |
| `get_transitions_for_section` | 🔴 Missing | - |
| `insert_mixer_layer` | 🔴 Missing | - |
| `is_layer_empty` | 🔴 Missing | - |
| `remove_decoration` | 🔴 Missing | - |
| `set_layer_name` | 🔴 Missing | - |

> Port kararı: Atlandı. UE 5.7'de `MovieSceneAnimMixer` plugin'i vardır, fakat UE 5.8 toolset'i
> `MovieSceneAnimMixerScripting` modülünün Python extension API'lerine bağlıdır. Bu modül UE 5.7
> descriptor/source içinde yoktur. Temiz çözüm tek MCP plugin portu değil, MovieSceneAnimMixer scripting
> backport'u olur.

### SlateInspectorToolset

#### `SlateInspectorToolset` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `Click` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Click` |
| `Drag` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Drag` |
| `FillForm` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.FillForm` |
| `Hover` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Hover` |
| `ListObservers` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.ListObservers` |
| `Observe` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Observe` |
| `PressKey` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.PressKey` |
| `Screenshot` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Screenshot` |
| `SelectOption` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.SelectOption` |
| `Snapshot` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Snapshot` |
| `Type` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Type` |
| `Unobserve` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Unobserve` |
| `WaitFor` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.WaitFor` |
| `Windows` | 🟢 Available | `SlateInspectorToolset.SlateInspectorToolset.Windows` |

### WorldConditionsToolset

#### `WorldConditionTools` - 🟢 COMPLETE

| UE 5.8 sub-tools | PortKit status | PortKit schema name |
| :--- | :--- | :--- |
| `GetConditionDescription` | 🟢 Available | `WorldConditionsToolset.WorldConditionTools.GetConditionDescription` |
| `GetQueryDescription` | 🟢 Available | `WorldConditionsToolset.WorldConditionTools.GetQueryDescription` |

## Available Ama UE 5.8 Extract Listesinde Ayrı Eşleşmeyenler

- Yok.

## UE 5.8 Listesinde Olup Ana Tabloya Girmeyen Toolsetler

### UMGToolSet

Status: **Atlandı**

Sebep:
- UE 5.8 source-only kopya build'e sokuldu.
- İki ayrı hata sınıfı çıktı: `UE_LOGF` compatibility eksikliği ve `WidgetBlueprintOperationUtils.h` bulunamaması.
- `WidgetBlueprintOperationUtils.h` UE 5.7 engine/plugin kaynaklarında public API olarak yoktur.
- Bu kademe küçük toolset portu değil, UMG widget blueprint operation utility backport'u olur.
- Rabbit hole stop kuralı gereği rollback edildi.

## Notlar

- Niagara tarafında bizde yalnızca 5.7-safe subset açıktır; `NiagaraToolset_Blueprint` küçük 5.7-safe adapter ile eklendi, 5.8-only `NiagaraToolset_System` araçları bilinçli olarak schema dışıdır.
- BlueprintTools bizde çalışır durumdadır, fakat UE 5.8 BlueprintTools içinde ek DSL/event/dispatcher/metadata alt araçları vardır; eksik olanlar tabloda tek tek gösterildi.
- PhysicsToolsets UE 5.8 source-only olarak `Plugins/PhysicsToolsets/` altına portlandı; 5.8 `RaiseScriptError` bağı 5.7-safe `FFrame::KismetExecutionMessage` helper'ına indirildi.
- Editor kapanış crash'i güncel health probe'da tekrar etmedi; process exit code temizdir.

## Kademe Uygulama Günlüğü

### Kademe 21 - EditorToolset Native Ownership Pass

Status: **Kısmi tamamlandı**

Amaç:
- Editor kapanış crash üretmeden `BlueprintTools`, `CurveTableTools`, `MaterialInstanceTools`, `MaterialTools` araçlarını tekrar kullanılabilir yapmak.
- Python-generated `@unreal.uclass/@unreal.ustruct/@unreal.uenum` toolset ownership yerine C++ `UToolsetDefinition` ownership kullanmak.

Eklenen / geri kazandırılan native toolsetler:
- `EditorToolset.CurveTableTools`: **9 tool**
- `EditorToolset.MaterialInstanceTools`: **12 tool**
- `EditorToolset.MaterialTools`: **22 tool**
- `EditorToolset.BlueprintTools`: **11 tool**

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Toolset count: **41**
- Editor exit code: **0**

Commitler:
- `47a75f1` - `Add native CurveTable MCP toolset ownership`
- `fa4855e` - `Add native MaterialInstance MCP toolset ownership`
- `6c920b5` - `Add native Material MCP toolset ownership`
- `d3156be` - `Add native Blueprint MCP safe subset ownership`

Notlar:
- `MaterialTools` artık Python bridge/schema ownership kullanmadan **22/22** native görünür.
- `CurveTableTools` artık Python struct/toolset ownership kullanmadan **9/9** native görünür.
- `MaterialInstanceTools` native görünür tool sayısı **12**. Python sürümündeki `set_parameter_override` bilinçli açılmadı; UE 5.7 public C++ `UMaterialEditingLibrary` tarafında bu fonksiyon yoktur ve Python-generated ownership geri getirilmeyecektir.
- `BlueprintTools` native güvenli subset olarak **11/53** açıldı. Node creation DSL, event dispatcher, bound event, graph DSL ve node cache tabanlı kalan gruplar tek tek patchlenmeyecek; gerekiyorsa ayrı mimari kademe olarak native `BlueprintGraphEditor`/DSL ownership portu yapılmalıdır.
- Bu pass sonunda editor kapanış crash tekrar etmedi.

### Kademe 1 - SemanticSearchToolset

Status: **Atlandı**

Sebep:
- `SemanticSearchToolset`, UE 5.8 `SemanticSearch` core pluginine bağlıdır.
- UE 5.7 tarafında `SemanticSearch` core plugin yoktur.
- UE 5.8 `SemanticSearch` core plugin, `FAISS` ThirdParty module ister.
- UE 5.7 tarafında `FAISS` ThirdParty module yoktur.

Karar:
- Bu kademe temiz plugin-only MCP toolset portu değildir.
- `SemanticSearch` + `FAISS` backport'u engine/third-party subsystem işi olur.
- Engine source patch yapılmayacağı için kademe pas geçildi.
- Commit atılmadı.

### Kademe 2 - ConfigSettingsToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `ConfigSettingsToolset` eklendi.
- `.uproject` içinde editor-only etkinleştirildi.
- UE 5.7 export etmeyen `UKismetSystemLibrary::RaiseScriptError` kullanımı local `FFrame::KismetExecutionMessage` helper'ına indirildi.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `ConfigSettingsToolset.ConfigSettingsToolset`
- Tool sayısı: **8/8**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 3 - AutomationTestToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `AutomationTestToolset` eklendi.
- `.uproject` içinde editor-only etkinleştirildi.
- UE 5.8 pluginindeki `AutomationTestToolsetTests` module ilk port kapsamı dışında bırakıldı; runtime MCP tool module temiz taşındı.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `AutomationTestToolset.AutomationTestToolset`
- Tool sayısı: **7/7**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 4 - AIModuleToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `AIModuleToolset` eklendi.
- `.uproject` içinde editor-only etkinleştirildi.
- `BehaviorTreeTools` Python toolset'i register edildi.
- UE 5.7 Python API'de expose edilmeyen `BTCompositeNode` ismi kaldırıldı; composite davranışı `BTNode` + property tabanlı kontrol ile çözüldü.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools`
- Tool sayısı: **7/7**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 5 - MaterialTools Missing Tool'lar

Status: **Atlandı**

Sebep:
- Local `MaterialTools` dosyasında UE 5.8 fonksiyonları zaten vardır.
- Missing görünme sebebi port eksikliği değil, capability gate'in bu fonksiyonları schema dışı bırakmasıdır.
- UE 5.7 Python `MaterialEditingLibrary` bu API'lerin çoğunu expose etmez.
- UE 5.7 C++ `UMaterialEditingLibrary` tarafında da eksiklerin çoğu yoktur.
- UE 5.8 C++ tarafında yeni bulunan API'ler: `GetMaterialExpressions`, `GetMaterialFunctionExpressions`, `DeleteUnusedExpressions`, `DisconnectMaterialExpressions`, `DisconnectMaterialProperty`, `GetMaterialExpressionOutputNames`, `GetInputsForMaterialFunctionExpression`, `GetMaterialsReferencingFunction`.
- UE 5.7 C++ tarafında yalnızca `GetInputsForMaterialExpression` ve `GetInputNodeOutputNameForMaterialExpression` görülür; bu tek başına tam tool grubunu güvenli açmaya yetmez.

Karar:
- Bu kademe temiz MCP exposure değişikliği değildir.
- Tam destek için 5.8 MaterialEditingLibrary davranışını project plugin bridge olarak yeniden yazmak gerekir; bu material editor internals'a geniş girer.
- Bozuk/yarım tool advertise edilmemesi için mevcut 14 tool korunmuştur.
- Commit atılmadı.

### Kademe 6 - BlueprintTools Missing Tool'lar

Status: **Kısmi tamamlandı**

Eklenenler:
- `set_variable_instance_editable` schema'ya açıldı; UE 5.7 Python API'de doğrudan mevcut.
- `get_variable_category` ve `set_variable_category` için `BlueprintEditorBridge` içine küçük UE 5.7-safe C++ bridge eklendi.
- BlueprintTools schema sayısı **32/53** -> **35/53** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `editor_toolset.toolsets.blueprint.BlueprintTools`
- Tool sayısı: **35/53**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Kalanların atlanma sebebi:
- `list_functions` ve `list_events` local source'ta 5.8 ile aynı şekilde boş stub döndürür; boş tool advertise edilmedi.
- event dispatcher / function parameter / component event / DSL / retarget / replication grupları daha geniş bridge ve asset mutation testi ister.
- Bu aşamada daha fazla açmak patch zinciri ve rabbit hole riski yaratır.

Karar:
- Küçük ve doğrulanmış Blueprint metadata grubu commitlenecek.
- Kalan 18 tool bilinçli schema dışı kalacak.

### Kademe 7 - NiagaraToolsets Missing/Kısmi Tool'lar

Status: **Kısmi tamamlandı**

Eklenenler:
- `NiagaraToolset_Blueprint` project plugin içinde gerçek C++ toolset olarak açıldı.
- `ConstructNiagaraBPWrapperFromSystem` ve `ConstructNiagaraBPWrapperFromComponent` schema'ya eklendi.
- UE 5.8 `NiagaraExternalSystemEditorUtilities` büyük backport'u yerine, sadece wrapper tool'ların ihtiyacı olan 5.7-safe user parameter adapter yazıldı.
- Niagara toolset sayısı **5/56** -> **7/56** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `NiagaraToolsets.NiagaraToolset_Blueprint`
- Tool sayısı: **2/2**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Kalanların atlanma sebebi:
- `NiagaraToolset_System` 46 tool, UE 5.8 `NiagaraExternalSystemEditorUtilities` / `FNiagaraExternalEditContext` / stack topology-edit API yüzeyine bağlıdır.
- Bu API yüzeyi UE 5.7 Niagara kaynaklarında yoktur.
- Bunu project plugin içinde taklit etmek, NiagaraEditor stack/viewmodel/edit utility backport'u olur; bu kademe için rabbit hole kabul edilir.
- `NiagaraToolset_Component` içindeki `GetUserVariables`, `GetVariable`, `SetVariable` aynı 5.8 `FNiagaraExt_InstancedValue` değer/JSON modeline bağlıdır; bozuk tool advertise edilmemesi için kapalı kaldı.

Karar:
- Niagara Blueprint wrapper grubu commitlenecek.
- System ve Component değişken araçları bilinçli schema dışı kalacak.

### Kademe 8 - WorldConditionsToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `WorldConditionsToolset` eklendi.
- `.uproject` içinde editor-only etkinleştirildi.
- `WorldConditionTools.GetQueryDescription` ve `WorldConditionTools.GetConditionDescription` schema'ya eklendi.
- Toplam mevcut tool sayısı **316** -> **318** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `WorldConditionsToolset.WorldConditionTools`
- Tool sayısı: **2/2**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 9 - DataRegistryToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `DataRegistryToolset` eklendi.
- `.uproject` içinde editor-only etkinleştirildi.
- UE 5.7'de olmayan `GetDataSources` / `GetRuntimeSources` accessor farkı read-only reflection adapter ile çözüldü.
- UE 5.7'de linklenmeyen `RaiseScriptError` çağrıları lokal `FFrame::KismetExecutionMessage` helper'ına indirildi.
- Toplam mevcut tool sayısı **318** -> **325** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `DataRegistryToolset.DataRegistryTools`
- Tool sayısı: **7/7**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 10 - GameFeaturesToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `GameFeaturesToolset` eklendi.
- `.uproject` içinde editor-only etkinleştirildi.
- UE 5.8 `UGameFeaturesSubsystem::IsGameFeaturePlugin` helper'ı UE 5.7'de olmadığından aynı path-domain davranışı plugin-local helper olarak taşındı.
- UE 5.7 `FResult` include farkı explicit `GameFeaturePluginOperationResult.h` include ile çözüldü.
- UE 5.7'de linklenmeyen `RaiseScriptError` çağrısı lokal `FFrame::KismetExecutionMessage` helper'ına indirildi.
- Toplam mevcut tool sayısı **325** -> **332** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `GameFeaturesToolset.GameFeaturesToolset`
- Tool sayısı: **7/7**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.
- Log notu: Asset Manager ayarlarında `GameFeatureData` primary asset rule uyarısı var; bu kademe schema/registration başarısını bloklamadı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 11 - PluginToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `PluginToolset` eklendi.
- `.uproject` içinde editor-only etkinleştirildi.
- UE 5.7 public `IPluginsEditorFeature` default template listesi expose etmediğinden template lookup added-template kapsamına indirildi.
- UE 5.8 post-create Python template hook alanları UE 5.7'de olmadığı için plugin creation params'tan çıkarıldı.
- UE 5.7'de linklenmeyen `RaiseScriptError` çağrısı lokal `FFrame::KismetExecutionMessage` helper'ına indirildi.
- Toplam mevcut tool sayısı **332** -> **349** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `PluginToolset.PluginToolset`
- Tool sayısı: **17/17**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Not:
- `GetPluginTemplateDescriptions` UE 5.7'de yalnızca public added-template listesini döndürür; engine default template listesi için engine patch yapılmadı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 12 - LiveCodingToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `LiveCodingToolset` eklendi.
- Test modülü descriptor'dan çıkarıldı; yalnızca editor toolset modülü portlandı.
- `.uproject` içinde editor-only etkinleştirildi.
- Toplam mevcut tool sayısı **349** -> **350** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `LiveCodingToolset.LiveCodingToolset`
- Tool sayısı: **1/1**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 13 - SemanticSearchToolset

Status: **Atlandı**

Hedef:
- `SemanticSearchToolset` 2/2.

Sebep:
- UE 5.7 engine pluginlerinde `SemanticSearch` dependency'si yok.
- UE 5.8 `SemanticSearch` ayrı Experimental plugin olarak FAISS, HTTP embedding provider, asset processor, editor integration ve index lifecycle stack'i getiriyor.
- Bu kademe tek toolset portu değil, geniş dependency/plugin backport olur.

Karar:
- Rabbit hole stop kuralı gereği pas geçildi.
- Engine patch yapılmadı.
- Tool sayısı değişmedi: **350** mevcut / **503** eksik.

### Kademe 14 - MVVMToolset

Status: **Atlandı**

Hedef:
- `MVVMToolset` 9/9.

Deneme sonucu:
- UE 5.8 source-only kopya ve `.uproject` entry ile full build geçti.
- MCP health sırasında module init fail oluştu; toolset schema'ya girmedi.
- Log kök sinyal: `UnrealEdGlobals.cpp` içinde `Internal::EditorModeToolsSingleton.IsValid()` ensure; Level Editor hazır olmadan editor mode/global editor state'e erişiliyor.

Karar:
- Bu kademede deferred/lazy registration mimarisi gerekir.
- Kısa ve güvenli port kapsamını aştığı için rollback yapıldı.
- Engine patch yapılmadı.
- Tool sayısı değişmedi: **350** mevcut / **503** eksik.

### Kademe 15 - ConversationToolset

Status: **Tamamlandı**

Eklenenler:
- Project plugin olarak `ConversationToolset` eklendi.
- Python test runner import'u port kapsamından çıkarıldı.
- UE 5.7 Python'da expose olmayan conversation struct return annotation'ları string liste özetine indirildi.
- `.uproject` içinde editor-only etkinleştirildi.
- Toplam mevcut tool sayısı **350** -> **357** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `conversation_toolset.toolsets.conversation.ConversationTools`
- Tool sayısı: **7/7**
- Editor exit code: **3**, bilinen PythonScriptPlugin shutdown crash; probe status ve schema başarılı.

Karar:
- Kademe başarılı.
- Non-markdown değişiklikler commitlenecek.

### Kademe 16 - ChaosClothAssetToolset

Status: **Atlandı**

Hedef:
- `ChaosClothAssetToolset` 6/6.

Sebep:
- UE 5.8 descriptor `ChaosClothAssetEditorCore` dependency'si istiyor.
- UE 5.7 engine pluginlerinde `ChaosClothAssetEditorCore` yok; sadece `ChaosClothAsset` ve `ChaosClothAssetEditor` var.
- Bu kademe tek toolset portu değil, 5.8-only editor core plugin backport olur.

Karar:
- Rabbit hole stop kuralı gereği pas geçildi.
- Engine patch yapılmadı.
- Tool sayısı değişmedi: **357** mevcut / **496** eksik.

### Kademe 17 - BlueprintTools Tam Portu (C++ Köprüsü)

Status: **Tamamlandı**

Eklenenler:
- `BlueprintEditorBridge` modülü altında `ListBlueprintFunctions` ve `ListBlueprintEvents` C++ fonksiyonları gerçeklendi.
- `blueprint.py` dosyası üzerinde kalan 18 aracın tamamı C++ köprüsüne yönlendirilerek açıldı.
- `_TOOLSET_SPECS` listesine eklenerek yükleyicide aktif hale getirildi.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `editor_toolset.toolsets.blueprint.BlueprintTools`
- Tool sayısı: **53/53** (Tüm fonksiyonlar aktif)
- Editor exit code: **1**, bilinen PythonScriptPlugin shutdown uyarısı; probe status ve schema başarılı.

Karar:
- Kalan tüm Blueprint araçları C++ köprüsüyle tam sürüme yükseltildi.

### Kademe 18 - MaterialTools Tam Portu (C++ Köprüsü)

Status: **Tamamlandı**

Eklenenler:
- `EditorToolset` modülü altında project-local material editor bridge C++ sınıfı oluşturuldu.
- `GetMaterialExpressions`, `DeleteUnusedExpressions`, `DisconnectMaterialExpressions` gibi eksik olan 8 adet fonksiyon C++ tarafında UE 5.7 API'leri ile simüle edilerek yazıldı.
- `material.py` üzerindeki yönlendirmeler C++ köprüsüne bağlandı.
- `_TOOLSET_SPECS` listesine eklenerek yükleyicide aktif hale getirildi.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `editor_toolset.toolsets.material.MaterialTools`
- Tool sayısı: **22/22** (Tüm fonksiyonlar aktif)
- Editor exit code: **1**, bilinen PythonScriptPlugin shutdown uyarısı; probe status ve schema başarılı.

Karar:
- Kalan tüm Material araçları C++ köprüsüyle tam sürüme yükseltildi.

## Geri Alma Notu - Blueprint/Material Port Denemesi

Status: **Geri alındı**

Geri alınan commitler:
- `2268cac` - `Fix Python MCP shutdown lifecycle`
- `d82a46e` - `Feature: Port remaining Blueprint and Material toolsets for UE 5.7 MCP integration`

Elde edilen önemli bulgular:
- Blueprint/Material C++ bridge yaklaşımı build seviyesinde çalışabildi.
- Ancak `BlueprintTools`, `MaterialTools`, `MaterialInstanceTools`, `CurveTableTools` ve `ProgrammaticToolset` aktif registration ile açık kaldığında editor kapanışında `PythonScriptPlugin` içinde crash tekrarlandı.
- MCP merkezi shutdown içinde Python cleanup'ı registry reset öncesine almak tek başına yeterli olmadı.
- Bu toolsetleri schema dışına almak crash'i durdurdu ama kabul edilen mimari değil; çünkü hedef tool'ları kullanılabilir tutmak.

Sonraki doğru hedef:
- Tool'lar açık kalacak.
- Editor kapanış crash'i olmayacak.
- Çözüm tool kapatma değil, Python `@unreal.uclass`, `@unreal.ustruct`, `@unreal.uenum` lifecycle riskini ortadan kaldıran mimari olacak.
- Bir sonraki denemede öncelik: Blueprint/Material toolsetlerini Python-generated type registration'a bağımlı bırakmadan native C++ toolset veya güvenli C++ wrapper mimarisiyle taşımak.

Doğrulama:
- İki revert sonrası full editor build: **pass**

## Ek Deneme Notu - Tool Açık Kalırken Shutdown Fix

Status: **Başarısız, geri alındı**

Denendi:
- `BlueprintTools`, `MaterialTools`, `MaterialInstanceTools`, `CurveTableTools`, `ProgrammaticToolset` tekrar aktif edildi.
- Python `bDeveloperMode=False` ile kapanıştaki stub generation devre dışı bırakıldı.
- MCP shutdown içinde Python cleanup registry reset öncesine alındı.
- `editor_toolset.shutdown` unregister + module/class reference cleanup yapacak şekilde denendi.
- `ProgrammaticToolset` tek başına kapatılarak izole edildi.

Sonuç:
- Tool schema ve probe aşamaları geçti.
- Editor exit code yine **3** oldu.
- Crash yine `PythonScriptPlugin + CoreUObject` içinde devam etti.
- `ProgrammaticToolset` tek başına kök sebep değil.
- Stub generation tek başına kök sebep değil.
- Registry unregister/cleanup tek başına kesin çözüm değil.

Karar:
- Bu yol rabbit hole kabul edildi ve geri alındı.
- C++ bridge + Python `@unreal.uclass/@unreal.ustruct/@unreal.uenum` registration mimarisi kabul edilmeyecek.
- Bir sonraki gerçek çözüm: riskli toolsetlerin tool registration sahipliği native C++ `UToolsetDefinition` tarafına taşınacak; Python-generated `UClass/UStruct/UEnum` public tool contract üretmeyecek.

### Kademe 22 - BlueprintTools Native Expansion

Status: **Tamamlandı**

Eklenenler:
- BlueprintTools natif C++ kütüphanesi (`BlueprintEditorBridge`) genişletilerek struct/object değişkenleri, event dispatcher'lar, bileşen olayları (component-bound events), node konumlandırma ve node sınıfı retargeting gibi ileri seviye araçların tamamı native C++ katmanında (`UToolsetDefinition`) expose edildi.
- Python tabanlı kararsız tip kayıt sistemi (unreal.uclass vb.) devre dışı bırakıldı; tüm araçlar C++ modülü üzerinden yüklendi.
- Toplam mevcut tool sayısı **380** -> **417** oldu.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `editor_toolset.toolsets.blueprint.BlueprintTools`
- Tool sayısı: **48/53** (Sadece 5 adet DSL/create-event delegesi kapalı kaldı)
- Editor exit code: **0** (Kapanış çökmesi tamamen çözüldü)

### Kademe 23 - BlueprintTools Kalan 5 Native Port

Status: **Tamamlandı**

Eklenenler:
- `add_event_dispatcher`
- `get_create_event_function`
- `set_create_event_function`
- `list_compatible_event_functions`
- `write_graph_dsl`

Mimari karar:
- Python-generated `BlueprintTools` toolset ownership geri getirilmedi.
- Event dispatcher üretimi native `BlueprintEditorBridge` köprüsüne taşındı.
- Create Event delegate fonksiyon okuma/yazma UE 5.7 public `UK2Node_CreateDelegate` API'si ile çözüldü.
- `write_graph_dsl` full UE 5.8 DSL parity değil; MCP için güvenli native minimum DSL subset olarak açıldı.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `EditorToolset.BlueprintTools`
- Tool sayısı: **53/53**
- Editor exit code: **0**

Commitler:
- `75be07e` - `Add native Blueprint event dispatcher MCP tool`
- `98211ec` - `Add native Blueprint create event delegate tools`
- `28e2fd4` - `Add native Blueprint graph DSL MCP writer`

Sonuç:
- BlueprintTools UE 5.8 listesindeki tüm 53 ana/alt tool şemada mevcut hale geldi.
- Bu kademede editor kapanış crash'i tekrar etmedi.

### Kademe 24 - MaterialInstanceTools Parameter Override

Status: **Tamamlandı**

Eklenenler:
- `set_parameter_override`

Mimari karar:
- Python-generated `MaterialInstanceTools` ownership geri getirilmedi.
- UE 5.8 `SetMaterialInstanceParameterOverride` davranışı UE 5.7 public C++ API'leriyle native `UToolsetDefinition` içine taşındı.
- Engine source patch uygulanmadı.
- Destek kapsamı mevcut native MaterialInstanceTools kapsamıyla sınırlı tutuldu: scalar, vector, texture, static switch.

Doğrulama:
- Full editor build: **pass**
- MCP health probe status: **pass**
- Registry: `EditorToolset.MaterialInstanceTools`
- Tool sayısı: **13/13**
- Editor exit code: **0**

Sonuç:
- MaterialInstanceTools UE 5.8 listesindeki tüm 13 tool ile tamamlandı.

## Port Taktikleri ve Mimari Kurallar

Bu bölüm sonraki port denemelerinde uygulanacak ortak karar setidir.

### Temel Kurallar

- Engine source patch uygulanmayacak.
- UE 5.7 ve UE 5.8 engine/plugin kaynakları sadece referans olarak okunacak; asıl kaynaklar değiştirilmeyecek.
- Değişiklikler project plugin/module sınırında kalacak.
- Available `Content/` asset'lerine dokunulmayacak.
- Tool schema'da görünüyorsa gerçekten çalışacak.
- Çalışmayan, unsupported veya kırılgan tool schema dışında kalacak.
- Python-generated `@unreal.uclass`, `@unreal.ustruct`, `@unreal.uenum` public tool ownership tekrar kullanılmayacak.
- Riskli toolsetlerde sahiplik native C++ `UToolsetDefinition` tarafında olacak.
- Her kademe full editor build + MCP health pass olmadan başarılı sayılmayacak.
- Editor exit code `0` önemli kabul kriteridir.
- Rabbit hole başladığında kademe durdurulacak, rollback edilecek, sebep rapora yazılacak.
- Başarılı her kademe ayrı ve dar kapsamlı commitlenecek.
- Markdown raporlar kullanıcı ayrıca istemedikçe commitlenmeyecek.

### Başarılı Taktikler

#### 1. Native C++ Toolset Ownership

Kullanıldığı yerler:
- `BlueprintTools`
- `MaterialTools`
- `MaterialInstanceTools`
- `CurveTableTools`

Sonuç:
- Python shutdown crash riski ortadan kalktı.
- Tool'lar açık kalırken editor kapanışı temiz oldu.
- MCP schema daha deterministik hale geldi.

Kural:
- Public MCP contract C++ `UToolsetDefinition` üstünden expose edilmeli.
- Python sadece yardımcı/internal kalabilir; public tool ownership Python-generated type olmamalı.

#### 2. 5.8 Contract, 5.7 Implementation

Kullanıldığı yerler:
- `BlueprintTools` kalan event/DSL araçları.
- `MaterialInstanceTools.set_parameter_override`.

Sonuç:
- UE 5.8 tool adı ve davranış kontratı korundu.
- UE 5.7 public API'leriyle native karşılık yazıldı.
- Engine patch gerekmedi.

Kural:
- 5.8 kodu birebir kopyalanmayacak.
- 5.8 davranışı referans alınacak.
- 5.7 public API ile küçük adapter/bridge yazılacak.

#### 3. Source-Only Plugin Port

Kullanıldığı yerler:
- `PhysicsToolsets`
- `PCGToolset`
- `GameplayTagsToolset`
- benzer düşük riskli toolsetler

Sonuç:
- Binaries/Intermediate taşınmadan temiz port yapılabildi.
- 5.8 compile farkları küçük 5.7 adaptasyonlarıyla çözüldü.

Kural:
- Sadece `.uplugin`, `Source`, gerekiyorsa `Resources` taşınacak.
- `Binaries`, `Intermediate`, generated files taşınmayacak.
- Compile farkı iki farklı yeni hata sınıfına yayılırsa rabbit hole kabul edilecek.

#### 4. Capability Gate / Safe Subset

Kullanıldığı yerler:
- `MaterialTools`
- `BlueprintTools`
- `PCGToolset`

Sonuç:
- Bozuk tool schema'da görünmedi.
- Önce çalışan subset açıldı, sonra kalanlar ayrı kademede tamamlandı.

Kural:
- Tam parity zorlanmayacak.
- Tool kazanımı güvenli subset ile başlatılacak.
- Kalanlar ayrı mimari kademe olarak ele alınacak.

#### 5. Headless-Safe Reimplementation

Kullanıldığı yerler:
- `PCGToolset.DrawSpline`

Sonuç:
- UE 5.8 interactive editor mode akışı birebir taşınmadı.
- MCP/headless kullanım için explicit parametre alan güvenli karşılık yazıldı.

Kural:
- Interactive editor mode, modal UI veya editor tool manager lifecycle gerektiren akışlar aynen taşınmayacak.
- MCP için headless-safe contract yazılacak.

### Başarısız Taktikler

#### 1. Python Shutdown Cleanup Patch

Denendi:
- Python cleanup registry reset öncesine alındı.
- `editor_toolset.shutdown` unregister/reference cleanup denendi.
- Stub generation kapatıldı.

Sonuç:
- Editor kapanış crash'i devam etti.
- `PythonScriptPlugin + CoreUObject` lifecycle problemi kesin çözülmedi.

Karar:
- Python shutdown patch zinciri bırakıldı.
- Tool ownership C++ tarafına taşındı.

#### 2. Python-Generated Toolsetleri Açık Tutmak

Denendi:
- `BlueprintTools`, `MaterialTools`, `MaterialInstanceTools`, `CurveTableTools`, `ProgrammaticToolset` Python registration ile tekrar açıldı.

Sonuç:
- Tool schema çalıştı ama editor kapanış crash'i geri geldi.

Karar:
- Public MCP tool contract Python-generated type üretmeyecek.

#### 3. Engine Private Header'a Bağlanmak

Görüldüğü yer:
- `DataflowAgentToolset`

Blok:
- UE 5.8 `Dataflow/DataflowAssetEditUtils.h` public.
- UE 5.7 karşılığı `DataflowEditor/Private` altında.

Karar:
- Project plugin engine private header'a bağlanmayacak.
- Gerekirse 5.8 public contract referans alınarak project-owned 5.7 adapter yazılacak.

#### 4. 5.8 Subsystem Backport

Görüldüğü yerler:
- `PCGToolset.GetNodeDataView`
- bazı Dataflow/template akışları için potansiyel risk

Karar:
- 5.8-only subsystem backport edilmeyecek.
- Engine-level subsystem gerekiyorsa tool atlanacak veya safe alternative yazılacak.

### DataflowAgent İçin Çıkarım

- `DataflowAgentToolset` direkt 5.8 source-only port ile alınmamalı.
- Ana blok Dataflow'un yokluğu değil; 5.7'de bazı pratik editor helper'ların public API olmamasıdır.
- Engine private `DataflowAssetEditUtils` kullanılmayacak.
- Doğru yol:
  - 5.8 `DataflowAgentToolset` contract'ı referans alınır.
  - Project plugin içinde `McpDataflowAssetEditUtils` benzeri project-owned public adapter yazılır.
  - Adapter sadece UE 5.7 public Dataflow/DataflowEditor API'lerine bağlanır.
  - Önce read-only tools, sonra mutation tools, en son asset/template tools denenir.
- İlk hedef 22/22 zorlamak değil; çalışan, headless-safe, public API tabanlı subset kazanmaktır.
