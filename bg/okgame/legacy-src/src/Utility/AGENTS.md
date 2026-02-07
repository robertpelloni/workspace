# Utility Subsystem - AGENTS.md

> Part of [bob's game / OKGame](../../AGENTS.md)

## Overview

The Utility subsystem (66 files) provides shared utilities used throughout the codebase including rendering, input handling, file I/O, audio, and common data structures.

## Directory Structure

```
Utility/
├── ArrayList.h              # std::vector alias
├── AssetData.h/cpp          # Asset loading/caching
├── BobColor.h/cpp           # Color utilities (also OKColor)
├── BobConsole.h/cpp         # Debug console
├── BobFont.h/cpp            # Font rendering (also OKFont)
├── BobMenu.h/cpp            # Menu system (also OKMenu)
├── BobTexture.h/cpp         # Texture management
├── Caption.h/cpp            # On-screen text display
├── ControlsManager.h/cpp    # Input handling
├── Easing.h/cpp             # Animation easing functions
├── FileUtils.h/cpp          # File I/O, compression
├── Logger.h                 # Logging system
├── System.h/cpp             # System utilities, timing
├── audio/                   # Audio subsystem (8 files)
│   ├── AudioManager.h/cpp   # Audio coordination
│   ├── Music.h/cpp          # Music playback
│   └── Sound.h/cpp          # Sound effects
└── gl/                      # OpenGL utilities (6 files)
    ├── GLUtils.h/cpp        # GL initialization, helpers
    ├── Shader.h/cpp         # Shader management
    └── Sprite.h/cpp         # Sprite rendering
```

## Core Classes

### BobColor / OKColor (BobColor.h)
Color utilities with preset colors.

```cpp
class BobColor {
    static void initPresetColors();
    static Color white, black, red, green, blue;
    // ... preset colors
    
    static Color lerp(Color a, Color b, float t);
    static Color fromHSV(float h, float s, float v);
};
```

### BobFont / OKFont (BobFont.h)
Font rendering using SDL_ttf and custom bitmap fonts.

```cpp
class BobFont {
    static void initFonts();
    static void drawString(string text, int x, int y, Color color);
    static int getStringWidth(string text);
};
```

### BobMenu / OKMenu (BobMenu.h)
Menu system for game UI.

```cpp
class BobMenu {
    vector<MenuItem> items;
    int selectedIndex;
    
    void update();
    void render();
    void addItem(string label, function<void()> callback);
};
```

### ControlsManager (ControlsManager.h)
Input handling for keyboard, gamepad, touch.

```cpp
class ControlsManager {
    static void initControllers();
    static bool isKeyPressed(int key);
    static bool isButtonPressed(int player, int button);
    static float getAxis(int player, int axis);
    
    // Per-player input state
    vector<PlayerControls> playerControls;
};
```

### FileUtils (FileUtils.h)
File I/O with compression support.

```cpp
class FileUtils {
    static void initCache();
    static string readFile(string path);
    static void writeFile(string path, string content);
    static vector<u8> compress(vector<u8> data);
    static vector<u8> decompress(vector<u8> data);
    static bool fileExists(string path);
};
```

### Logger (Logger.h)
Logging system with levels.

```cpp
class Logger {
    static void initLogger();
    static void log(string message);
    static void warn(string message);
    static void error(string message);
    static void debug(string message);
};
```

### System (System.h)
System utilities and timing.

```cpp
class System {
    static void updateRenderTimers();
    static void updateStats();
    static long long getTime();
    static float getDeltaTime();
    static int getFPS();
};
```

### Easing (Easing.h)
Animation easing functions.

```cpp
class Easing {
    static float linear(float t);
    static float easeInQuad(float t);
    static float easeOutQuad(float t);
    static float easeInOutQuad(float t);
    // ... more easing functions
};
```

## Audio Subsystem (audio/)

### AudioManager (AudioManager.h)
Central audio coordination.

```cpp
class AudioManager {
    static void initAudioLibrary();
    void playMusic(string path);
    void playSound(string path);
    void setMusicVolume(float volume);
    void setSFXVolume(float volume);
    
    // For projectM visualizer
    void getPCMData(float* buffer, int samples);
};
```

### Music (Music.h)
Background music playback.

### Sound (Sound.h)
Sound effect playback with pooling.

## OpenGL Utilities (gl/)

### GLUtils (GLUtils.h)
OpenGL initialization and helpers.

```cpp
class GLUtils {
    static void initGL();
    static void clear();
    static void setViewport(int x, int y, int w, int h);
    static void setProjection(float fov, float aspect);
};
```

### Shader (Shader.h)
GLSL shader management.

```cpp
class Shader {
    void load(string vertexPath, string fragmentPath);
    void use();
    void setUniform(string name, float value);
    void setUniform(string name, mat4 value);
};
```

### Sprite (Sprite.h)
2D sprite rendering.

```cpp
class Sprite {
    shared_ptr<BobTexture> texture;
    float x, y, width, height;
    float rotation, scale;
    Color tint;
    
    void render();
};
```

## Naming Convention: Bob* vs OK*

Many classes have dual names (e.g., `BobColor`/`OKColor`). This is a branding artifact:
- `Bob*` - Original "bob's game" naming
- `OK*` - Alternative "OKGame" naming

Both typically alias to the same implementation.

## Key Patterns

### Static Initialization
Many utility classes use static initialization:
```cpp
// In main.cpp startup
BobColor::initPresetColors();
FileUtils::initCache();
BobFont::initFonts();
AudioManager::initAudioLibrary();
```

### Singleton Access
```cpp
// Via Main class (global access)
Main::getAudioManager()->playSound("click.wav");
Main::getFileUtils()->readFile("config.xml");
```

### Smart Pointer Usage
```cpp
shared_ptr<BobTexture> texture = ms<BobTexture>("sprite.png");
shared_ptr<Sprite> sprite = ms<Sprite>(texture);
```

## Dependencies

- SDL2 (core functionality)
- SDL_ttf (font rendering)
- SDL_image (texture loading)
- SDL_mixer (audio playback)
- OpenGL / GLEW (rendering)
- zlib (compression)
- Boost.Serialization (save/load)

## Related Documentation

- [Root AGENTS.md](../../AGENTS.md)
- [Engine AGENTS.md](../Engine/AGENTS.md)
- [Puzzle AGENTS.md](../Puzzle/AGENTS.md)
