# Licensing

This PortKit does not redistribute Epic Unreal Engine source code.

It fetches required UE 5.8 plugin source from the user's licensed
`EpicGames/UnrealEngine` access, then applies local patches.

Repository contents:

- Port orchestration scripts.
- Patch files.
- Documentation.
- Independently authored adapter code under `owned/`, including
  `MaterialGraphDSLBridge`.

The Material Graph DSL follows the same boundary:

- `owned/MaterialGraphDSLBridge` contains the original native UE 5.7 bridge,
  strict Python parser, and parser tests.
- `patches/0001-generated-ue57-port.patch` contains only the registration and
  integration changes applied to source fetched through the user's licensed
  Epic Games access.
- No fetched UE 5.8 source is copied into `owned/` or committed as a standalone
  source file.

Generated or downloaded during tool execution:

- UE 5.8 plugin/source inputs under `cache/`.
- Generated compatibility plugins inside the target project.
- Verification reports under `reports/`.

Optional repository hygiene check:

```powershell
python Scripts/ModelContextProtocolPort/mcp_port_kit.py license-audit
```
