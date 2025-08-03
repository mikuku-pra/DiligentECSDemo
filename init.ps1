# init.ps1 - 初始化脚本，带临时代理参数

$RootDir = Get-Location

Write-Host "=== Step 1: Remove existing DiligentEngine submodule if any ==="
$enginePath = Join-Path $RootDir "third_party/DiligentEngine"
if (Test-Path $enginePath) {
    git -c http.proxy="127.0.0.1:7890" submodule deinit -f -- "third_party/DiligentEngine" | Out-Null
    git -c http.proxy="127.0.0.1:7890" rm -f "third_party/DiligentEngine" | Out-Null
    Remove-Item -Recurse -Force $enginePath
    Remove-Item -Recurse -Force ".git/modules/third_party/DiligentEngine" -ErrorAction SilentlyContinue
    Write-Host "Removed old DiligentEngine submodule."
} else {
    Write-Host "No existing DiligentEngine submodule directory."
}

Write-Host "=== Step 2: Add submodules ==="
git -c http.proxy="127.0.0.1:7890" submodule add https://github.com/DiligentGraphics/DiligentEngine.git third_party/DiligentEngine
git -c http.proxy="127.0.0.1:7890" submodule add https://github.com/skypjack/entt.git third_party/entt

Write-Host "=== Step 3: Initialize and update all submodules recursively ==="
git -c http.proxy="127.0.0.1:7890" submodule update --init --recursive

Write-Host "=== Step 4: Generate CMakeLists.txt ==="
$cmakeContent = @"
cmake_minimum_required(VERSION 3.16)
project(DiligentECSDemo LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 请自行在此处设置 Vulkan 路径和环境变量

find_package(Vulkan REQUIRED)

if(NOT TARGET Vulkan::Vulkan)
    add_library(Vulkan::Vulkan UNKNOWN IMPORTED)
    set_target_properties(Vulkan::Vulkan PROPERTIES
        IMPORTED_LOCATION "\${Vulkan_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "\${Vulkan_INCLUDE_DIR}"
    )
endif()

add_subdirectory(third_party/DiligentEngine)
add_subdirectory(third_party/entt)

file(GLOB_RECURSE DEMO_SRC CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(\${PROJECT_NAME} \${DEMO_SRC})

target_link_libraries(\${PROJECT_NAME}
    DiligentEngine
    Vulkan::Vulkan
)

target_include_directories(\${PROJECT_NAME} PRIVATE third_party/entt/single_include)

target_include_directories(\${PROJECT_NAME} PRIVATE
    third_party/DiligentEngine/Components
    third_party/DiligentEngine/DiligentCore
    third_party/DiligentEngine/Platforms
)
"@

$cmakeFilePath = Join-Path $RootDir "CMakeLists.txt"
Set-Content -Path $cmakeFilePath -Value $cmakeContent -Encoding UTF8

Write-Host ""
Write-Host "==== 脚本执行完毕 ===="
Write-Host "请自行在 CMakeLists.txt 中配置 Vulkan SDK 路径相关设置。"
Write-Host "建议执行："
Write-Host "  git -c http.proxy=\"127.0.0.1:7890\" submodule update --init --recursive"
Write-Host "  cmake -S . -B build"
Write-Host "  cmake --build build --config Debug"
