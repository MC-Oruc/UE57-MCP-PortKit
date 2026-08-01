# Material Graph DSL Bridge

[![Unreal Engine 5.7](https://img.shields.io/badge/Unreal%20Engine-5.7-blue.svg)](https://www.unrealengine.com/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

Project-owned native bridge and Python parser for atomic MCP material graph operations.

## Installation

Run the PortKit installer from the project root:

```powershell
python Scripts/ModelContextProtocolPort/mcp_port_kit.py install
```

The installer copies this owned plugin into `Plugins/MaterialGraphDSLBridge`, enables it in the project descriptor, builds the Editor target, and verifies the tool schema.

## License

MIT. See [LICENSE](LICENSE).
