# Loyalty Backend

C++ HTTP service for a store loyalty program: SQLite persistence, REST-style routes, and a schema covering users, stores, orders, promotions, points, and NFC/QR cards. The codebase is organized into entities, DTOs, repositories, and **services**.

---

## Requirements

---

- **CMake** 3.20 or newer
- **C++17** compiler
- **[vcpkg](https://github.com/microsoft/vcpkg)** for dependencies (manifest mode via `vcpkg.json`)

## Dependencies (vcpkg)

| Package            | Role                                        |
| ------------------ | ------------------------------------------- |
| cpp-httplib        | Embedded HTTP server                        |
| sqlite3, sqlitecpp | SQLite access via SQLiteCpp wrapper         |
| nlohmann-json      | JSON serialization                          |
| spdlog, fmt        | Logging and formatting                      |
| jwt-cpp            | JWT handling (wired for future auth)        |
| libsodium          | Password hashing (`crypto_pwhash`)          |
| boost-uuid         | Listed for ID generation (see `vcpkg.json`) |

CMake also links these targets: `unofficial::sqlite3::sqlite3`, `httplib::httplib`, `nlohmann_json::nlohmann_json`, `spdlog::spdlog`, `fmt::fmt`, `jwt-cpp::jwt-cpp`, `unofficial-sodium::sodium`, `SQLiteCpp`.

## Build

Point CMake at the vcpkg toolchain file (adjust `VCPKG_ROOT` to your install):

```bash
export VCPKG_ROOT=/path/to/vcpkg

cmake -B build -S . \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake"

cmake --build build
```

The executable is `loyalty_backend` under the build directory (e.g. `build/loyalty_backend` or `build/Debug/loyalty_backend` depending on generator).

## Configuration

| Setting        | Location                                                      | Default                                                  |
| -------------- | ------------------------------------------------------------- | -------------------------------------------------------- |
| Listen address | `includes/configs/server-config.hpp` (`ServerConfig::HOST`)   | `0.0.0.0`                                                |
| Port           | `ServerConfig::PORT`                                          | `8080`                                                   |
| SQLite file    | `includes/configs/db-config.hpp` (`DatabaseConfig::filename`) | `loyalty.db` (relative to the process working directory) |

Compile-time defines in `CMakeLists.txt` set `PROJECT_ROOT`, `MIGRATION_PATH`, and `SEED_PATH` for migration SQL under `src/migrations/`.

## Run

From the project root (so `loyalty.db` resolves as expected):

```bash
./build/loyalty_backend
```

The process initializes **libsodium** before starting the server.

## Database

- **Schema**: `src/migrations/init.sql` defines tables for users, owners, stores, staff, customers, products, orders, promotions, points history, cards, and related junction tables.
- **Seeds**: `src/migrations/seeds.sql` (optional sample data).
- Automatic migration calls in `Server::setup()` are currently commented out; to apply SQL manually, use `SqliteRepo::migrate()` with paths consistent with `SqliteRepo` (paths are resolved relative to the current working directory when using relative filenames).

## HTTP API (current)

| Method | Path                | Description                                                                          |
| ------ | ------------------- | ------------------------------------------------------------------------------------ |
| `GET`  | `/api/v1/users/:id` | Returns user JSON if found; `404` with plain text if missing; `500` on server errors |

Additional user routes and auth flows are partially scaffolded in services and commented code (e.g. pagination, insert/update).

## Project layout

```
includes/     # Headers: configs, entities, dtos, mappers, repositories, services
src/          # Implementation (.cpp), migrations, main entry
CMakeLists.txt
vcpkg.json
```

## Development notes

- `CMAKE_EXPORT_COMPILE_COMMANDS` is enabled for tooling (e.g. clangd).
- Source files under `src/` are collected with `GLOB_RECURSE`; add new `.cpp` files under `src/` and reconfigure the build.
