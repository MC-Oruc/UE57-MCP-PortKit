# UE 5.7 MCP PortKit

Bring Unreal Engine 5.8 Model Context Protocol editor toolsets to Unreal Engine
5.7 projects with one command.

This repository is a small installer and patch kit. It does not vendor Unreal
Engine source. It fetches the pinned UE 5.8 MCP/toolset source from the user's
licensed Epic Games GitHub access, ports it into the current UE 5.7 project,
enables the plugins, builds the editor target, and verifies the MCP tool schema.

## Why This Exists

Epic's MCP editor toolsets are available in UE 5.8, but many UE projects still
ship on UE 5.7. This kit keeps that workflow usable without patching engine
source and without advertising broken MCP tools.

If a tool appears in MCP schema, it is expected to work.

## Available MCP Coverage

Current port coverage:

- 414 available MCP sub-tools
- 40 registered toolsets
- UE 5.8 source baseline pinned to `5.8.0-release`
- UE 5.7 project-plugin install, no engine source patch

Included/high-value toolset groups:

| Toolset group | Available tools |
| :--- | ---: |
| EditorToolset: actors, assets, Blueprint, materials, scene, logs, textures, tables and more | 251 |
| PCGToolset and PCGSpatialToolset | 31 |
| PhysicsToolsets | 17 |
| PluginToolset | 17 |
| SlateInspectorToolset | 14 |
| GASToolsets | 14 |
| StateTreeToolset | 9 |
| ConfigSettingsToolset | 8 |
| AIModuleToolset | 7 |
| AutomationTestToolset | 7 |
| ConversationToolset | 7 |
| DataRegistryToolset | 7 |
| GameFeaturesToolset | 7 |
| GameplayTagsToolset | 6 |
| Niagara safe subset | 7 |
| ToolsetRegistry | 4 |
| WorldConditionsToolset | 2 |
| LiveCodingToolset | 1 |

For the full matrix, skipped areas, and known limitations, see:

- `docs/PortMatrix.md`
- `docs/ValidationReport.md`
- `docs/KnownIssues.md`
- `docs/Licensing.md`

## Requirements

- Windows
- Python 3.10+
- Git
- Unreal Engine 5.7 project
- Local UE 5.7 installation
- GitHub access to `EpicGames/UnrealEngine`

The UE 5.7 engine root is detected from the `.uproject`, `UE_ROOT`,
`UNREAL_ENGINE_ROOT`, or common Epic Launcher install paths.

## Install

Run from your Unreal project root:

```powershell
git clone https://github.com/MC-Oruc/UE57-MCP-PortKit.git Scripts/ModelContextProtocolPort
python Scripts/ModelContextProtocolPort/mcp_port_kit.py install
```

`git clone <repo> Scripts/ModelContextProtocolPort` clones directly into that
folder. It does not create an extra `UE57-MCP-PortKit` directory.

The installer:

- Finds the target `.uproject`
- Finds the UE 5.7 engine root
- Sparse-fetches only the required UE 5.8 source paths with a shallow
  treeless Git fetch
- Imports required plugins into `Plugins/`
- Generates compatibility support code where needed
- Applies the UE 5.7 port patch
- Enables required plugins in the `.uproject`
- Avoids duplicate plugin entries
- Runs a full editor build
- Runs an MCP toolset probe

## Update The Patch

After making port changes inside a project:

```powershell
python Scripts/ModelContextProtocolPort/mcp_port_kit.py create-patch
```

Generated patch:

```text
Scripts/ModelContextProtocolPort/patches/0001-generated-ue57-port.patch
```

## Useful Commands

```powershell
python Scripts/ModelContextProtocolPort/mcp_port_kit.py doctor
python Scripts/ModelContextProtocolPort/mcp_port_kit.py license-audit
python Scripts/ModelContextProtocolPort/mcp_port_kit.py clean
```

## Repository Safety

- No full Unreal Engine source checkout is stored here.
- Temporary UE source/cache data is ignored.
- Generated build artifacts are ignored.
- Compatibility code generated from UE source is produced during install.

## Suggested GitHub Description

```text
UE 5.7 MCP PortKit: one-command installer for Unreal Engine 5.8 Model Context Protocol toolsets ported to UE 5.7 projects.
```
