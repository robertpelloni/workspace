# Project Dashboard

## Project Structure
- **src/main/java/com/bobsgame/**: Main game source code.
  - **puzzle/**: New Puzzle Engine core (backported from C++).
  - **client/**: Client-side logic (Rendering, Audio, Input).
  - **server/**: Server-side logic.
  - **shared/**: Shared data structures.
  - **net/**: Networking protocol definitions (`BobNet`).
- **cpp_repo/**: Reference C++ repository.
- **libs/**: External libraries and submodules.

## Submodules
The project uses the following submodules located in `libs/`:

| Path | URL | Description |
| :--- | :--- | :--- |
| `libs/GeoIP2-java` | https://github.com/maxmind/GeoIP2-java | GeoIP lookup |
| `libs/lwjgl3` | https://github.com/LWJGL/lwjgl3 | Lightweight Java Game Library 3 |
| `libs/lz4-java` | https://github.com/lz4/lz4-java | LZ4 Compression |
| `libs/jinput` | https://github.com/jinput/jinput | Java Input API |
| `libs/micromod` | https://github.com/martincameron/micromod | MOD/XM Audio Player |
| `libs/twl-lwjgl3` | https://github.com/ThemableWidgetLibrary/twl-lwjgl3 | Themable Widget Library (GUI) |
| `libs/mysql-connector-j` | https://github.com/mysql/mysql-connector-j | MySQL JDBC Driver |
| `libs/xpp3` | https://github.com/codelibs/xpp3 | XML Pull Parser |
| `libs/xz-java` | https://github.com/tukaani-project/xz-java | XZ Compression |
| `libs/commons-lang` | https://github.com/apache/commons-lang | Apache Commons Lang |

## Build Status
- **Current Version:** 0.0.2
- **Build System:** Gradle
- **Command:** `./gradlew clean build`
