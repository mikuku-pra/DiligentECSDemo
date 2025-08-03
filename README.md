# DiligentECSDemo

A minimal example integrating **Diligent Engine**, **Dear ImGui**, and **EnTT** using CMake and submodules.

## Features

- 🧱 DiligentEngine as backend (Vulkan default)
- 🎨 ImGui integration via DiligentTools
- 🧠 ECS powered by EnTT
- 🛠️ CMake build system
- 🧩 Git submodules

## Build

```bash
git clone --recursive https://github.com/yourname/DiligentECSDemo.git
cd DiligentECSDemo
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Run

Executable will be located in `bin/`. Press Esc to close the window.
