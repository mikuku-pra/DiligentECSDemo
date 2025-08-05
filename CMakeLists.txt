cmake_minimum_required(VERSION 3.16)
project(DiligentECSDemo LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===== 后端支持开关 =====
option(D3D11_SUPPORTED "Enable D3D11 backend" OFF)
option(D3D12_SUPPORTED "Enable D3D12 backend" OFF)
option(VULKAN_SUPPORTED "Enable Vulkan backend" ON)
option(GL_SUPPORTED "Enable OpenGL backend" OFF)

set(PLATFORM_WIN32 ON)

add_subdirectory(third_party/DiligentEngine/DiligentSamples/ThirdParty/glfw)

# ===== Vulkan SDK =====
find_package(Vulkan REQUIRED)

# ===== 添加子模块 =====
add_subdirectory(third_party/DiligentEngine)
add_subdirectory(third_party/entt)

# ===== 源文件 =====
file(GLOB_RECURSE DEMO_SRC CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(${PROJECT_NAME} ${DEMO_SRC})

# ===== Include路径 =====
target_include_directories(${PROJECT_NAME} PRIVATE
    third_party/entt/single_include
    third_party/DiligentEngine
)

# ===== 编译宏定义 =====
target_compile_definitions(${PROJECT_NAME} PRIVATE
    PLATFORM_WIN32
    ENGINE_DLL=1
    UNICODE
)

# ===== 链接基础模块 =====
target_link_libraries(${PROJECT_NAME} PRIVATE
    Diligent-BuildSettings
    Diligent-GraphicsTools
    Diligent-BasicPlatform
    Diligent-PlatformInterface
    glfw
)

# ===== 后端链接控制 =====
if(D3D11_SUPPORTED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Diligent-GraphicsEngineD3D11-shared)
endif()

if(D3D12_SUPPORTED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Diligent-GraphicsEngineD3D12-shared)
endif()

if(VULKAN_SUPPORTED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Diligent-GraphicsEngineVk-shared Vulkan::Vulkan)
endif()

if(GL_SUPPORTED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Diligent-GraphicsEngineOpenGL-shared)
endif()

# ===== 可选：拷贝运行所需 DLL =====
copy_required_dlls(${PROJECT_NAME})

# ===== 设置 VS 工程文件夹（可选）=====
set_target_properties(${PROJECT_NAME} PROPERTIES
    FOLDER DiligentSamples/ECSDemo
)
