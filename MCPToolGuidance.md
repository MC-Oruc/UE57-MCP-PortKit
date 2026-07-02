# MCP Agent Tool Guidance

This guide tells an AI agent which Unreal MCP toolset to use first, how to avoid
tool confusion, and how to finish common editor tasks with minimal calls.

Use this document as an operating checklist. Do not try to memorize every tool.
Pick the task family, call the smallest discovery tool, then call the narrowest
editing or verification tool.

Tool names in this guide are usually shortened for readability. When calling
through MCP tool-search mode, use the exact tool name returned by
`describe_toolset`.

Important naming rule for tool-search mode:

- Use the exact registered toolset name as `toolset_name`.
- Use the short function name as `tool_name` when `call_tool` expects a tool
  inside that toolset, for example `toolset_name:
  "editor_toolset.toolsets.scene.SceneTools"` and `tool_name:
  "get_current_level"`.
- If direct native MCP tools are exposed instead of tool-search mode, use the
  native fully qualified tool name shown by the client.

## Prime Rules

1. Prefer tool-search mode: use `list_toolsets` only when the needed toolset is
   unknown, `describe_toolset` only for that toolset, and `call_tool` for the
   exact tool. Do not list every tool for ordinary tasks.
2. Query before editing: inspect the target asset, actor, property, graph, or
   plugin state before writing.
3. Keep writes narrow: use the domain toolset that owns the thing being changed.
   Do not use generic file edits when a structured tool exists.
4. Save explicitly after asset or level changes: use `AssetTools.save_assets` or
   `SceneTools.save_actor` as appropriate.
5. Verify with the cheapest signal first: read back the changed value, then use
   screenshots, logs, PIE, or automation tests only when needed.
6. Never modify an unintended level. Use `SceneTools.get_current_level` before
   scene work and `SceneTools.load_level` only when the user explicitly named the
   target level.
7. Avoid destructive operations unless directly requested. For delete/move,
   check referencers/dependencies first.
8. If a tool fails, read `LogsToolset.GetLogEntries` before retrying with a
   different tool.
9. Prefer selected actors/assets when the user is working in the editor. Use
   broad searches only when there is no selected or exact-path target.
10. If a tool rejects a plain asset path, call `AssetTools.load_asset` and use
    the returned object/ref path.

## Operating Model

This is not a mandatory call sequence. It is the decision model an agent should
use to avoid unnecessary tools:

1. Classify the task: level design, asset discovery, property edit, material,
   Blueprint, data, PCG, runtime inspection, UI automation, or tests.
2. If the target is already selected or named by exact path, use that target.
   Do not search broadly.
3. If the task is visual, set the editor camera to see the changed area and
   capture a viewport/editor image for verification.
4. If the task is non-visual, prefer value readback over screenshots.
5. If the task creates temporary scene content, clean it up and verify removal.
6. If a tool call fails, read recent logs before trying a different tool family.

Only execute the steps needed for the current task. Do not run the whole model as
a checklist.

## Fast Tool Selection

| Goal | First Toolset | Why |
| --- | --- | --- |
| Find assets, folders, dependencies, metadata, dirty state | `editor_toolset.toolsets.asset.AssetTools` | Asset registry and package operations |
| Place, find, remove, folder, trace, or save level actors | `editor_toolset.toolsets.scene.SceneTools` | Level/world actor operations |
| Move actors, add components, tags, labels, bounds | `editor_toolset.toolsets.actor.ActorTools` | Actor and component structure |
| Read/write arbitrary UObject properties | `editor_toolset.toolsets.object.ObjectTools` | Generic reflected properties |
| Editor camera, screenshots, selection, PIE, console commands | `EditorToolset.EditorAppToolset` | Editor session state |
| Read logs or change log verbosity | `EditorToolset.LogsToolset` | Output Log access |
| Create or edit Blueprints and graphs | `EditorToolset.BlueprintTools` | Blueprint variables, nodes, graphs, compile |
| Create/edit materials or material functions | `EditorToolset.MaterialTools` | Material graph expressions |
| Create/edit material instances | `EditorToolset.MaterialInstanceTools` | Instance parameters and parent |
| Static mesh import, materials, LODs, collision, Nanite | `editor_toolset.toolsets.static_mesh.StaticMeshTools` | Static mesh asset operations |
| Skeletal mesh import, sockets, bones, physics asset assignment | `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools` | Skeletal mesh asset operations |
| Textures | `editor_toolset.toolsets.texture.TextureTools` | Texture import and size |
| Data tables | `editor_toolset.toolsets.data_table.DataTableTools` | Rows, schemas, import |
| Curve tables | `EditorToolset.CurveTableTools` | Curve rows and keys |
| Data assets | `editor_toolset.toolsets.data_asset.DataAssetTools` | Data asset creation |
| String tables/localization tables | `editor_toolset.toolsets.string_table.StringTableTools` | String table entries |
| Project/editor config sections | `ConfigSettingsToolset.ConfigSettingsToolset` | Structured ini-backed settings |
| Automation tests | `AutomationTestToolset.AutomationTestToolset` | Discover, run, results |
| Gameplay tags | `GameplayTagsToolset.GameplayTagsToolset` | Tags and referencers |
| GAS runtime inspection, attributes, cues | `GASToolsets.*` | Ability System state and cue assets |
| Behavior Trees | `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools` | BT node and blackboard inspection |
| State Trees | `state_tree_toolset.toolsets.state_tree.StateTreeTools` | StateTree structure inspection |
| Conversation assets | `conversation_toolset.toolsets.conversation.ConversationTools` | Conversation node structure |
| Data Registries | `DataRegistryToolset.DataRegistryTools` | Registry metadata and items |
| Game Feature Plugins | `GameFeaturesToolset.GameFeaturesToolset` | List/activate/deactivate features |
| Plugins | `PluginToolset.PluginToolset` | Plugin descriptors, dependencies, enable state |
| Niagara discovery/components/BP wrappers | `NiagaraToolsets.*` | FX scripts, components, wrappers |
| PCG graphs and graph instances | `PCGToolset.PCGToolset` | Build/modify/execute PCG |
| One-off PCG spatial query graph | `PCGToolset.PCGSpatialToolset` | Instant spatial graph |
| Physics assets | `PhysicsToolsets.PhysicsAssetToolset` | Bodies, shapes, constraints |
| Slate UI automation | `SlateInspectorToolset.SlateInspectorToolset` | Editor UI snapshots and actions |
| WorldCondition structs | `WorldConditionsToolset.WorldConditionTools` | Query/condition descriptions |
| Live Coding compile | `LiveCodingToolset.LiveCodingToolset` | Trigger editor live compile |
| Agent skills | `ToolsetRegistry.AgentSkillToolset` | List/read/write agent skills |

## Discovery Pattern

Use this sequence unless the user already named a tool:

1. If the task matches a recipe in **Direct-Call Recipes**, call that recipe
   directly. Do not call `describe_toolset` first.
2. If there is no recipe, match the request to one row in **Fast Tool
   Selection**.
3. Call `describe_toolset` for that toolset only.
4. Pick the exact read tool first.
5. Pick the exact write tool second.
6. Read back the result.

Only call `list_toolsets` when the request does not fit the table.

Use `describe_toolset` only when:

- There is no direct-call recipe for the task.
- A direct-call recipe fails input validation.
- The task needs an unlisted tool in the same toolset.
- You need the exact schema for a complex write.

## Direct-Call Recipes

These recipes cover common tasks without a prior `describe_toolset` call. In
tool-search mode, pass the listed exact `toolset_name` and short `tool_name` to
`call_tool`.

### R1: Current Level

Use to confirm the open level before any scene mutation.

```json
{
  "toolset_name": "editor_toolset.toolsets.scene.SceneTools",
  "tool_name": "get_current_level",
  "arguments": {}
}
```

If the level is wrong, stop scene work. Use `load_level` only when the user
explicitly named the target level.

### R2: Find Asset

Use exact folder/name when possible. `name` supports substring and `*` / `?`
wildcards.

```json
{
  "toolset_name": "editor_toolset.toolsets.asset.AssetTools",
  "tool_name": "find_assets",
  "arguments": {
    "folder_path": "/Engine/BasicShapes",
    "name": "Cube",
    "asset_type": {"refPath": "/Script/Engine.StaticMesh"},
    "recursive": false,
    "tags": {}
  }
}
```

For project assets use a narrow `/Game/...` folder. Use empty folder only when
you intentionally want `/Game` plus plugin content paths.

If the class filter is not known, use `asset_type: {"refPath": ""}` and filter
the returned package paths by exact name.

### R3: Place Asset as Top-Level Actor

Call R1 first. Then:

```json
{
  "toolset_name": "editor_toolset.toolsets.scene.SceneTools",
  "tool_name": "add_to_scene_from_asset",
  "arguments": {
    "asset_path": "/Engine/BasicShapes/Cube",
    "name": "MCP_Test_Cube",
    "xform": {
      "location": {"x": 200, "y": 0, "z": 100},
      "rotation": {"pitch": 0, "yaw": 0, "roll": 0},
      "scale": {"x": 1, "y": 1, "z": 1}
    },
    "parent": {"refPath": ""},
    "snap_to_ground": false
  }
}
```

Then label/transform with R4 and R5. Clean transient tests with R8.

### R4: Label Actor

```json
{
  "toolset_name": "editor_toolset.toolsets.actor.ActorTools",
  "tool_name": "set_label",
  "arguments": {
    "actor": {"refPath": "<actor-ref>"},
    "label": "MCP_Test_Cube"
  }
}
```

### R5: Set Actor Transform

```json
{
  "toolset_name": "editor_toolset.toolsets.actor.ActorTools",
  "tool_name": "set_actor_transform",
  "arguments": {
    "actor": {"refPath": "<actor-ref>"},
    "xform": {
      "location": {"x": 200, "y": 0, "z": 100},
      "rotation": {"pitch": 0, "yaw": 0, "roll": 0},
      "scale": {"x": 1, "y": 1, "z": 1}
    },
    "worldspace": true
  }
}
```

Verify with `get_actor_transform` using the same toolset.

### R6: Focus and Capture Viewport

```json
{
  "toolset_name": "EditorToolset.EditorAppToolset",
  "tool_name": "FocusOnActors",
  "arguments": {
    "actors": [{"refPath": "<actor-ref>"}]
  }
}
```

Then read the focused camera transform:

```json
{
  "toolset_name": "EditorToolset.EditorAppToolset",
  "tool_name": "GetCameraTransform",
  "arguments": {}
}
```

```json
{
  "toolset_name": "EditorToolset.EditorAppToolset",
  "tool_name": "CaptureViewport",
  "arguments": {
    "captureTransform": {
      "location": {"x": 0, "y": 0, "z": 0},
      "rotation": {"pitch": 0, "yaw": 0, "roll": 0},
      "scale": {"x": 1, "y": 1, "z": 1}
    },
    "annotations": {
      "gridSpacing": 100,
      "gridExtent": 1000,
      "gridHeight": 0,
      "maxLabelDistance": 5000,
      "classFilter": {"refPath": "/Script/Engine.Actor"},
      "maxLabels": 50
    },
    "bShowUI": false
  }
}
```

Replace `captureTransform` with the `GetCameraTransform` result. Use the
capture metadata for labeled actor verification when available.

### R7: Find Actor by Label

```json
{
  "toolset_name": "editor_toolset.toolsets.scene.SceneTools",
  "tool_name": "find_actors",
  "arguments": {
    "root": {"refPath": ""},
    "name": "MCP_Test_Cube",
    "actor_type": {"refPath": ""},
    "tag": "",
    "bounds": {
      "min": {"x": 0, "y": 0, "z": 0},
      "max": {"x": 0, "y": 0, "z": 0},
      "isValid": false
    },
    "use_bounds": false,
    "collision_channels": []
  }
}
```

### R8: Remove Transient Actor

```json
{
  "toolset_name": "editor_toolset.toolsets.scene.SceneTools",
  "tool_name": "remove_from_scene",
  "arguments": {
    "actor": {"refPath": "<actor-ref>"}
  }
}
```

Verify with R7.

### R9: Selected Actor Property Edit Path

Use this order. Call `describe_toolset` only if a schema rejects the input.

1. Get selected actors:

```json
{
  "toolset_name": "EditorToolset.EditorAppToolset",
  "tool_name": "GetSelectedActors",
  "arguments": {}
}
```

2. If editing a component, get components:

```json
{
  "toolset_name": "editor_toolset.toolsets.actor.ActorTools",
  "tool_name": "get_components",
  "arguments": {
    "actor": {"refPath": "<actor-ref>"},
    "component_type": {"refPath": ""}
  }
}
```

3. List, read, set, read back reflected properties:

```json
{
  "toolset_name": "editor_toolset.toolsets.object.ObjectTools",
  "tool_name": "list_properties",
  "arguments": {
    "instance": {"refPath": "<object-or-component-ref>"}
  }
}
```

```json
{
  "toolset_name": "editor_toolset.toolsets.object.ObjectTools",
  "tool_name": "get_properties",
  "arguments": {
    "instance": {"refPath": "<object-or-component-ref>"},
    "properties": ["<PropertyName>"]
  }
}
```

```json
{
  "toolset_name": "editor_toolset.toolsets.object.ObjectTools",
  "tool_name": "set_properties",
  "arguments": {
    "instance": {"refPath": "<object-or-component-ref>"},
    "values": "{\"<PropertyName>\": \"<value>\"}"
  }
}
```

### R10: Known Plugin Enabled State

When the plugin name is known, never list all plugins first.

```json
{
  "toolset_name": "PluginToolset.PluginToolset",
  "tool_name": "IsEnabled",
  "arguments": {
    "pluginName": "ModelContextProtocol"
  }
}
```

Use `GetPluginInfo`, `GetPluginDescriptor`, `GetPluginDependencies`, or
`GetPluginDependents` next only if needed.

### R11: Narrow Automation Test Flow

Discover once, then run a narrow exact name or filter. Do not run all tests.

```json
{
  "toolset_name": "AutomationTestToolset.AutomationTestToolset",
  "tool_name": "DiscoverTests",
  "arguments": {
    "bForceRediscover": false
  }
}
```

```json
{
  "toolset_name": "AutomationTestToolset.AutomationTestToolset",
  "tool_name": "RunTestsByFilter",
  "arguments": {
    "filterExpression": "<narrow-filter>"
  }
}
```

Then poll:

```json
{
  "toolset_name": "AutomationTestToolset.AutomationTestToolset",
  "tool_name": "GetTestStatus",
  "arguments": {}
}
```

Read results:

```json
{
  "toolset_name": "AutomationTestToolset.AutomationTestToolset",
  "tool_name": "GetTestResults",
  "arguments": {}
}
```

If no filter is provided, plan only or use `ListTests` with a narrow name filter.

### R12: Recent Logs

```json
{
  "toolset_name": "EditorToolset.LogsToolset",
  "tool_name": "GetLogEntries",
  "arguments": {
    "category": "",
    "pattern": "<optional-pattern>",
    "maxEntries": 50
  }
}
```

Use after a failed tool call, failed test, or runtime warning.

## Level Design Tool Reference

Use these toolsets directly for level design, layout, dressing, visual
verification, and scene cleanup. These are fully listed because they are the
highest-risk, highest-frequency editor manipulation tools.

### `editor_toolset.toolsets.scene.SceneTools`

World/level actor operations:

- `get_current_level`
- `load_level`
- `find_actors`
- `add_to_scene_from_asset`
- `add_to_scene_from_class`
- `remove_from_scene`
- `get_collision_channels`
- `get_folders`
- `get_actors_in_folder`
- `set_actor_folder`
- `rename_folder`
- `delete_folder`
- `trace_world`
- `merge_actors`
- `create_level_instance`
- `edit_level_instance`
- `commit_level_instance`
- `can_edit`
- `is_checked_out`
- `save_actor`

Use `get_current_level` before scene writes. Use `load_level` only when the user
explicitly named the target level.

### `editor_toolset.toolsets.actor.ActorTools`

Actor/component structure and transforms:

- `get_label`
- `set_label`
- `get_tags`
- `has_tag`
- `add_tag`
- `remove_tag`
- `get_actor_transform`
- `set_actor_transform`
- `look_at`
- `get_root_component`
- `get_component_actor`
- `get_parent_component`
- `set_parent_component`
- `get_actor_bounds`
- `get_components`
- `add_component`
- `remove_component`

Use this for labels, transforms, hierarchy, tags, component enumeration, and
component add/remove. Use `ObjectTools` after `get_components` when editing
reflected component properties.

### `editor_toolset.toolsets.primitive.PrimitiveTools`

Greybox primitives:

- `add_cube`
- `add_sphere`
- `add_cylinder`
- `add_cone`

Use these for fast blockout when a real asset is not required.

### `editor_toolset.toolsets.object.ObjectTools`

Generic reflected property access:

- `search_subclasses`
- `get_class`
- `list_properties`
- `get_properties`
- `set_properties`
- `reset_properties`

Use this for light intensity/color, component settings, and other reflected
values when no specialized tool owns the operation. Always `list_properties`
before `set_properties` unless the property name is already known.

### `EditorToolset.EditorAppToolset`

Editor state, viewport, PIE, screenshots, selection, and console commands:

- `CaptureAssetImage`
- `CaptureEditorImage`
- `CaptureViewport`
- `ExecuteConsoleCommand`
- `FocusOnActors`
- `GetCameraTransform`
- `GetContentBrowserPath`
- `GetOpenAssets`
- `GetSelectedActors`
- `GetSelectedAssets`
- `GetVisibleActors`
- `IsPIERunning`
- `OpenEditorForAsset`
- `ScreenCoordsToWorld`
- `SearchCVars`
- `SelectActors`
- `SelectAssets`
- `SetCameraTransform`
- `SetContentBrowserPath`
- `StartPIE`
- `StopPIE`
- `WorldPosToScreenCoords`

For visual work, use `FocusOnActors` or `SetCameraTransform`, then
`CaptureViewport` or `CaptureEditorImage`. Use `ExecuteConsoleCommand` only when
a direct editor command is the shortest correct path.

## PCG Tool Reference

Use PCG tools when the task involves procedural graph authoring, procedural
placement, graph instances, node wiring, graph parameters, or instant spatial
queries.

### `PCGToolset.PCGToolset`

- `AddCommentBox`
- `AddNode`
- `AddSubgraphNode`
- `ConnectNodePins`
- `CreateGraph`
- `DisconnectNodePins`
- `DrawSpline`
- `ExecuteGraphInstance`
- `GetGraphDescription`
- `GetGraphInstanceParams`
- `GetGraphSchema`
- `GetGraphStructure`
- `GetNativeNodeSchema`
- `GetNodeDataView`
- `GetNodeInfo`
- `ListAvailableSubgraphs`
- `ListGraphInstances`
- `ListNativeNodes`
- `RemoveCommentBox`
- `RemoveGraphParams`
- `RemoveNode`
- `RepositionNode`
- `ResetGraphInstanceParams`
- `SetGraphDescription`
- `SetGraphInstanceParams`
- `SetGraphParams`
- `SetNodeComment`
- `SpawnGraphInstance`
- `UpdateCommentBox`
- `UpdateNode`

PCG workflow:

1. Inspect: `GetGraphSchema`, `GetGraphStructure`, `ListNativeNodes`, or
   `GetNativeNodeSchema`.
2. Edit: `AddNode`, `ConnectNodePins`, `SetGraphParams`, `UpdateNode`.
3. Place/run: `SpawnGraphInstance`, `SetGraphInstanceParams`,
   `ExecuteGraphInstance`.
4. Verify: `GetGraphStructure`, `GetGraphInstanceParams`, `GetNodeDataView`,
   and viewport capture if visual output matters.

### `PCGToolset.PCGSpatialToolset`

- `RunPCGInstantGraph`

Use this for one-off spatial queries where creating or editing a persistent PCG
graph would be unnecessary.

## Common Workflows

These notes describe task flow only. Use **Direct-Call Recipes** for exact
payloads, or `describe_toolset` when no recipe exists.

- Asset placement: find a narrow asset candidate, confirm the current level,
  place, label/transform, focus the camera, capture the viewport, then clean up
  transient test actors. `find_assets.name` supports substring and `*` / `?`
  wildcard matching.
- Greyboxing: use `PrimitiveTools` for quick blockout shapes, then
  `ActorTools` for transform/label/folder organization.
- Actor/component properties: select or find the actor, get components if
  needed, `ObjectTools.list_properties`, read the current value, set only the
  target property, read back to verify.
- Material edits: use `MaterialInstanceTools` for instance parameters and
  `MaterialTools` only for graph edits. If an instance exposes no parameters,
  do not guess names.
- Mesh material slots: use `StaticMeshTools` or `SkeletalMeshTools` for asset
  slots. Use `ActorTools.get_components` plus `ObjectTools` for placed actor
  component overrides.
- Blueprint edits: inspect graphs/variables first, make the smallest edit,
  compile, then read compile results or graph state.
- Data edits: inspect schema first, mutate rows/keys/entries narrowly, then read
  back. Do not create string tables through generic asset/file hacks if the
  dedicated tool reports a runtime limitation.
- Runtime inspection: do not start PIE for pure asset-structure inspection.
  Start PIE only for runtime state, use the relevant inspector, then stop PIE.
- UI automation: observe the target window, snapshot/wait, perform the smallest
  UI action, screenshot only when visual proof matters, then unobserve.
- Tests: discover once, run a narrow filter, poll status, read results, and read
  logs only on failure. Do not run all tests unless explicitly requested.
- Plugins: use `PluginToolset` for normal plugins. Use `GameFeaturesToolset`
  only for Game Feature Plugins. If the plugin name is known, avoid broad plugin
  listing.

## Expensive or Risky Tools

| Tool family | Use only when |
| --- | --- |
| `AssetTools.delete`, `move`, `duplicate` | User requested asset mutation; check referencers first |
| `SceneTools.load_level` | User explicitly named a target level |
| `SceneTools.remove_from_scene`, `delete_folder` | User requested deletion/removal |
| `BlueprintTools.WriteGraphDsl` | Many graph edits are needed |
| `PluginToolset.SetPluginEnabled` | User requested plugin state change |
| `GameFeaturesToolset.RequestActivateGameFeature` | User requested feature activation or runtime validation |
| `EditorAppToolset.ExecuteConsoleCommand` | A direct editor console command is the shortest correct path |
| `SlateInspectorToolset` input actions | UI cannot be controlled by a structured non-UI tool |
| `LiveCodingToolset.CompileLiveCoding` | User wants live compile from the open editor |

For disposable assets created by the current run under a dedicated temporary
folder, if `get_referencers` itself errors, delete only the exact temporary
paths you created and verify with `AssetTools.exists == false`.

## Minimal Verification Matrix

| Change | Verify with |
| --- | --- |
| Asset created/moved/deleted | `AssetTools.exists`, `find_assets`, referencers |
| Asset metadata/property | `AssetTools.get_metadata_tags`, `ObjectTools.get_properties` |
| Actor placed/moved | `SceneTools.find_actors`, `ActorTools.get_actor_transform` |
| Component added/changed | `ActorTools.get_components`, `ObjectTools.get_properties` |
| Material instance parameter | Matching `MaterialInstanceTools.Get*Parameter` |
| Material graph | `MaterialTools.GetExpressions`, `Recompile` |
| Blueprint graph | `ReadGraphDsl`, `CompileBlueprint` |
| Data table/curve/string | Matching list/get rows/keys/entries |
| Config | `ConfigSettingsToolset.GetSectionPropertyValues` |
| Runtime behavior | PIE + domain inspector + logs |
| Visual/editor state | `CaptureViewport`, `CaptureEditorImage`, or Slate screenshot |

## Token Discipline

- Do not call both `list_toolsets` and many `describe_toolset` calls when the
  task maps to one row.
- Do not ask for screenshots until a non-visual readback is insufficient.
- Do not run automation tests for simple asset edits.
- Do not inspect all dependencies/referencers unless deleting, moving, or
  changing a shared asset.
- Prefer exact paths and selected actors over broad searches.
- Stop when the readback proves the requested change.
- For multi-domain tasks, finish one domain with readback before switching to
  the next. This prevents asset/actor/toolset cross-talk.

## If Unsure

Use this fallback:

1. `list_toolsets`.
2. Pick one likely toolset by name and description.
3. `describe_toolset` for that one toolset.
4. Use one read-only tool.
5. Continue only if the result proves the toolset is relevant.

Do not shotgun-call multiple unrelated toolsets.

## Exact Toolset Appendix

These are the registered toolsets covered by this guide. Use this appendix when
the MCP server requires an exact `toolset_name`.

| Exact toolset | Route |
| --- | --- |
| `ToolsetRegistry.AgentSkillToolset` | Agent skills |
| `AutomationTestToolset.AutomationTestToolset` | Tests |
| `EditorToolset.EditorAppToolset` | Editor state, camera, PIE, screenshots, console |
| `EditorToolset.LogsToolset` | Logs |
| `EditorToolset.BlueprintTools` | Blueprints |
| `EditorToolset.CurveTableTools` | Curve tables |
| `EditorToolset.MaterialInstanceTools` | Material instances |
| `EditorToolset.MaterialTools` | Materials |
| `ConfigSettingsToolset.ConfigSettingsToolset` | Config settings |
| `LiveCodingToolset.LiveCodingToolset` | Live Coding compile |
| `GameplayTagsToolset.GameplayTagsToolset` | Gameplay tags |
| `GASToolsets.GameplayCueToolset` | Gameplay cues |
| `GASToolsets.AttributeSetToolset` | AttributeSet discovery |
| `GASToolsets.AbilitySystemInspectorToolset` | Runtime ASC inspection |
| `DataRegistryToolset.DataRegistryTools` | Data registries |
| `NiagaraToolsets.NiagaraToolset_Info` | Niagara enum/type info |
| `NiagaraToolsets.NiagaraToolset_Component` | Niagara component assignment |
| `NiagaraToolsets.NiagaraToolset_Assets` | Niagara script discovery |
| `NiagaraToolsets.NiagaraToolset_Blueprint` | Niagara Blueprint wrappers |
| `PCGToolset.PCGToolset` | PCG graphs |
| `PCGToolset.PCGSpatialToolset` | Instant PCG spatial graph |
| `PhysicsToolsets.PhysicsAssetToolset` | Physics assets |
| `GameFeaturesToolset.GameFeaturesToolset` | Game Feature Plugins |
| `PluginToolset.PluginToolset` | Plugins |
| `WorldConditionsToolset.WorldConditionTools` | WorldCondition descriptions |
| `SlateInspectorToolset.SlateInspectorToolset` | Slate UI automation |
| `state_tree_toolset.toolsets.state_tree.StateTreeTools` | State Trees |
| `editor_toolset.toolsets.actor.ActorTools` | Actors/components/tags/transforms |
| `editor_toolset.toolsets.asset.AssetTools` | Assets/folders/packages |
| `editor_toolset.toolsets.data_asset.DataAssetTools` | Data assets |
| `editor_toolset.toolsets.data_table.DataTableTools` | Data tables |
| `editor_toolset.toolsets.object.ObjectTools` | Generic UObject properties |
| `editor_toolset.toolsets.primitive.PrimitiveTools` | Greybox primitives |
| `editor_toolset.toolsets.scene.SceneTools` | Level actors/world |
| `editor_toolset.toolsets.skeletal_mesh.SkeletalMeshTools` | Skeletal mesh assets |
| `editor_toolset.toolsets.static_mesh.StaticMeshTools` | Static mesh assets |
| `editor_toolset.toolsets.string_table.StringTableTools` | String tables |
| `editor_toolset.toolsets.texture.TextureTools` | Textures |
| `conversation_toolset.toolsets.conversation.ConversationTools` | Conversations |
| `aimodule_toolset.toolsets.behavior_tree.BehaviorTreeTools` | Behavior Trees |
