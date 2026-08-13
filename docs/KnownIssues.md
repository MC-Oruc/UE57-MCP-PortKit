# Known Issues

- The kit requires the user's GitHub account to have access to
  `EpicGames/UnrealEngine`.
- The default target is UE 5.7.4. Other UE 5.7 patch versions are best effort.
- `MetaHumanGenerator` is a project-owned UE 5.7 bridge. Its native wrapper
  supplies the missing `unreal.MetaHumanGeneratorSubsystemWrapper`; the MCP
  probe currently registers all 9 MetaHuman tools successfully. It is enabled
  through its project descriptor and still requires the MetaHuman Character,
  Core Tech, SDK, and Toolset Registry plugins.
- Patch conflicts stop the install. The script does not attempt automatic
  source-code repair.
- `install` expects to run from the project root or below it. Use `--project`
  only for unusual layouts.
- `cache/`, `temp/`, and `reports/` are local state and are safe to delete with:

```powershell
python Scripts/ModelContextProtocolPort/mcp_port_kit.py clean
```
