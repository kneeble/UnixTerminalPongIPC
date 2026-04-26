## Architecture Change

Originally planned:
- Client/server using Unix sockets

Actual implementation:
- Single-kernel architecture
- Modular components:
  - Input
  - Game logic
  - Rendering

Reason:
- Bare-metal environment does not support processes or IPC