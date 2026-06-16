# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

Mini Creator is a lightweight 3D rendering engine in C++17 using OpenGL via Qt 6. It loads multiple 3D models (Assimp), renders them in real time, and lets the user select, transform, and inspect models through a Qt Widgets UI. The README is written in Korean; this project targets Windows 11 + Qt 6.7.1 but builds anywhere Qt 6 is available.

## Build & Run

```bash
mkdir build && cd build
cmake ..                 # requires Qt6 on CMAKE_PREFIX_PATH / env vars
cmake --build .          # produces the `mini_creator` executable
```

- Qt6 must be installed and discoverable (`find_package(Qt6 ...)`). Components used: Core, Gui, OpenGL, OpenGLWidgets, Widgets.
- **Assimp** and **glm** are fetched automatically at configure time via CMake `FetchContent` (see `cmake/3rdparty/`) — no manual install. First configure is slow because it clones and builds Assimp.
- There is **no test suite, linter, or CI config** in this repo. Don't invent test commands.
- Source files are collected with `file(GLOB_RECURSE ...)` per directory in `CMakeLists.txt`. **Adding a new top-level `src/` subdirectory requires adding a matching GLOB and including it in `qt_add_executable`** — new files inside existing globbed directories are picked up on reconfigure.

## Architecture

Entry point: `main.cpp` → `App` (owns `QApplication` + `MainWindow`) → `App::Execute()` runs the Qt event loop.

Everything lives under namespace `mini_creator`, with sub-namespaces matching directories (`ui`, `ui::widgets`, `graphics`, `graphics::physics`, `graphics::shader`, `core`, `commands`).

### Layers

- **`src/ui/`** — Qt Widgets layer. `MainWindow` assembles a `MenuBar` (with `menu_bar/` submenus: file/edit/camera/animation), a `ToolBar`, an `ObjectControlWidget` (transform editing for the selected model), and the `RenderWidget`.
- **`src/ui/widgets/render_widget.*`** — The heart of the app: a `QOpenGLWidget` that owns the `Camera` and `Light`, drives a 16ms repaint timer, and handles all keyboard/mouse input. `paintGL()` iterates `ModelManager::GetAllModels()` and draws each, then draws the light cube and the selected model's bounding box. Mouse-left does picking via `Raycast`; middle-drag orbits the camera; wheel zooms; `F` toggles first/third person; `WASD` moves.
- **`src/core/model_manager.*`** — `ModelManager` is an **all-static global registry** of loaded models plus the current selection. UI, rendering, and raycasting all coordinate through it. The `is_bounding_box_changed_` flag is set when models change so `RenderWidget::paintGL` can auto-fit the camera on the next frame. There is no instance — call methods statically.
- **`src/graphics/`** — Rendering primitives. `Model` (transform + list of `Mesh` + shaders + bounding box), `Mesh` (VBO/EBO geometry + textures), `Camera` (view/projection matrices, first/third-person modes, screen→world ray for picking, bounding-box auto-fit), `Light`, `ShaderProgram` (thin wrapper over `QOpenGLShaderProgram` with `SetUniform`/`SetAttribute` overloads).
- **`src/graphics/physics/raycast.*`** — `Raycast::Execute(origin, dir)` returns the picked `Model` (ray vs. model AABB) for selection.
- **`src/commands/command_import.*`** — `CommandImport` is a **singleton** (`instance()`) that uses Assimp to load a model file, walks the scene (`ProcessNode`/`ProcessMesh`), builds a `Model`, and registers it with `ModelManager`. Emits the `ProgressUpdated(int)` signal during import, which `RenderWidget` connects to its progress bar.

### Shaders

Shaders are compiled from **inline source strings embedded in C++ headers** under `src/graphics/shader/` (e.g. `mesh_vs.h` defines `static const char *mesh_vs = R"(...)";` in namespace `mini_creator::graphics::shader`). `ShaderProgram::Load(vertexSrc, fragmentSrc)` takes these source strings directly. `Model` includes the relevant `*_vs.h`/`*_fs.h` headers and passes the strings.

> Note: the matching `.vs`/`.fs` plain-text files in the same directory are **not** loaded at runtime — they are legacy/reference copies of the same source. When editing a shader, change the `*.h` version (that is what compiles).

### Conventions

- Data flows through the static `ModelManager`, not through direct widget references — when adding selection/transform features, read and write model state via it.
- Models are held as `std::shared_ptr<graphics::Model>` throughout.
- Mixed math types: `glm::vec3`/`glm::mat4` for model/geometry data, `QMatrix4x4`/`QVector3D` for the rendering API surface. Watch for conversions at boundaries.
- `samples/` contains test `.obj` models (trees, cottage, skull) for manually exercising import.
