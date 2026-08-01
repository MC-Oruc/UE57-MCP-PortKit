# Port Matrix

Default source pin:

```text
7deeb413d3dc1fc034f48d1aacc0861301829d32
```

Known local launcher equivalent:

```text
UE 5.8.0
CL 55116800
++UE5+Release-5.8
```

Pinned GitHub `Build.version` branch value:

```text
UE5
```

The authoritative import/plugin list is `../portkit.manifest.json`.
The authoritative tool coverage report is `docs/ValidationReport.md`.

## Project Extensions

These are intentional project additions on top of the UE 5.8 parity matrix:

- `editor_toolset.toolsets.material.MaterialTools`: 28 project-owned Python
  tools, including the atomic graph DSL read/validate/apply workflow and
  compiled shader statistics.
- `EditorToolset.EditorAppToolset.ExecuteConsoleCommand`: executes editor console commands such as `viewmode unlit`.
- `editor_toolset.toolsets.asset.AssetTools.find_assets`: enhanced `name` matching. The same `name` argument supports both case-insensitive substring matching and wildcard matching with `*` / `?`.

They are not counted in the UE 5.8 parity sub-tool totals.

Current report summary:

- UE 5.8 total sub-tools: 853
- Current UE 5.7 ported sub-tools: 414
- Missing sub-tools: 439
- Registered parity toolsets: 40
- Registered runtime toolsets including Material DSL: 41

`install` applies the compatibility patch and copies the project-local plugin
descriptors. `EnabledByDefault` in those descriptors is the activation policy;
the installer does not rewrite the target `.uproject` plugin list.

## Covered By Current Port

These groups are complete in the current validation report and are covered by
the current patch/import flow:

| Group | Coverage |
| :--- | :--- |
| `EditorToolset` | 251/251 + project extensions, including the 28-tool Material surface |
| `PCGToolset` | 31/31 |
| `AIModuleToolset` | 7/7 |
| `AutomationTestToolset` | 7/7 |
| `ConfigSettingsToolset` | 8/8 |
| `ConversationToolset` | 7/7 |
| `DataRegistryToolset` | 7/7 |
| `GameFeaturesToolset` | 7/7 |
| `GameplayTagsToolset` | 6/6 |
| `GASToolsets` | 14/14 |
| `PhysicsToolsets` | 17/17 |
| `PluginToolset` | 17/17 |
| `SlateInspectorToolset` | 14/14 |
| `StateTreeToolset` | 9/9 |
| `ToolsetRegistry` | 4/4 |
| `WorldConditionsToolset` | 2/2 |

## Known Partial Or Missing Groups

| Group | Status | Reason |
| :--- | :--- | :--- |
| `NiagaraToolsets` | 7/56 | 5.7-safe asset/blueprint/info subset is enabled. `NiagaraToolset_System` depends on UE 5.8 external system edit context and stack topology APIs. |
| `AnimationAssistantToolset` | 0/319 | Large Sequencer/ControlRig Python/editor API surface. Porting it as patches would be a rabbit hole; needs separate native architecture. |
| `DataflowAgent` | 0/22 | UE 5.8 uses public Dataflow edit helpers that are private/not available in UE 5.7. Needs a public adapter, not private header use. |
| `MVVMToolset` | 0/9 | Needs deferred/lazy registration architecture. Short safe port was rolled back. |
| `ChaosClothAssetToolset` | 0/6 | UE 5.8-only cloth asset editor API surface; skipped by rabbit-hole rule. |
| `MetaHumanGenerator` | 0/9 | UE 5.8 Python expects `unreal.MetaHumanGeneratorSubsystemWrapper`, absent in UE 5.7. Requires a dedicated native bridge; disabled by default. |
| `SemanticSearchToolset` | 0/2 | Depends on UE 5.8 `SemanticSearch` core plugin, absent in UE 5.7. |
| `SequencerAnimMixerToolset` | 0/21 | Depends on UE 5.8 `MovieSceneAnimMixerScripting`, absent in UE 5.7. |

## Tactics

Successful:

- Native C++ `UToolsetDefinition` ownership for risky Python-generated toolsets.
- UE 5.8 contract with UE 5.7 public C++ implementation.
- Source-only plugin import from the user's licensed UE 5.8 source.
- Capability gating: hidden if unsupported, visible only if usable.
- Headless-safe reimplementation instead of interactive editor lifecycle calls.

Rejected:

- Python `atexit`/shutdown cleanup patching.
- Python-generated `@unreal.uclass/@unreal.ustruct/@unreal.uenum` as public toolset ownership for crash-prone groups.
- UE private header inclusion.
- Full UE 5.8 subsystem backport for one MCP toolset.
