# Publishing Checklist

Before publishing:

- Run `python mcp_port_kit.py license-audit`.
- Run `python -m py_compile mcp_port_kit.py`.
- Verify `cache/`, `temp/`, `reports/`, `Binaries/`, `Intermediate/`, and
  generated Unreal build artifacts are not tracked.
- Confirm no raw Unreal Engine source checkout is present.
- Confirm `README.md` install command points to the final GitHub repository URL.
- Confirm the patch applies to the pinned UE 5.8 source ref.

Recommended GitHub settings:

- Repository URL:
  `https://github.com/MC-Oruc/UE57-MCP-PortKit`
- Description:
  `Automated utility & patch kit to backport UE 5.8 Model Context Protocol (MCP) toolsets and Atomic Material Graph DSL to UE 5.7 projects.`
- Topics:
  `unreal-engine`, `ue57`, `model-context-protocol`, `mcp`, `material-dsl`, `shader-diagnostics`, `ai-agents`, `editor-tools`
- Visibility:
  Public only after the publishing checklist passes.
