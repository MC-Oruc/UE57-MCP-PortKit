# Licensing

This PortKit does not redistribute Epic Unreal Engine source code.

It fetches required UE 5.8 plugin source from the user's licensed
`EpicGames/UnrealEngine` access, then applies local patches.

Repository contents:

- Port orchestration scripts.
- Patch files.
- Documentation.
- Project-local adapter code under `owned/`.

Generated or downloaded during tool execution:

- UE 5.8 plugin/source inputs under `cache/`.
- Generated compatibility plugins inside the target project.
- Verification reports under `reports/`.

Optional repository hygiene check:

```powershell
python Scripts/ModelContextProtocolPort/mcp_port_kit.py license-audit
```
