# F-Zero X PC Port Layer

This directory contains the code specific to the native PC port of F-Zero X.

## Architecture
The PC port uses a Hardware Abstraction Layer (HAL) to separate game logic from platform-specific APIs.

- **Game Logic**: Uses the original N64 engine code (mostly preserved).
- **HAL**: `include/pc/hal.h` defines the interface.
- **Backends**: Implementations of the HAL (currently **SDL2**).

## Implemented Backends
- **Video**: SDL2 Window + OpenGL Context.
- **Audio**: SDL2 Audio (stub/queue).
- **Input**: SDL2 Event Polling.

## Build Instructions

### Prerequisites
- GCC or Clang
- SDL2 Development Libraries (`libsdl2-dev`)
- OpenGL Development Libraries

### Compiling
Run the standalone PC makefile from the root directory:

```bash
make -f Makefile.pc
```

The executable will be generated at `build/pc/fzerox_pc`.

### Running
```bash
./build/pc/fzerox_pc
```
