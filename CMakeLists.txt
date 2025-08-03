cmake_minimum_required(VERSION 3.16)
project(DiligentECSDemo LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 手动指定 Vulkan 路径（你自己备份的）
set(ENV{VULKAN_SDK} "D:/file/vulkanSdk")

# 必须在 find_package 前设定
set(ENV{VULKAN_SDK} "D:/file/vulkanSdk")
set(Vulkan_INCLUDE_DIR "D:/file/vulkanSdk/Include")
set(Vulkan_LIBRARY "D:/file/vulkanSdk/Lib/vulkan-1.lib")

find_package(Vulkan REQUIRED)

# 手动创建导入目标，防止找不到 Vulkan::Vulkan
if(NOT TARGET Vulkan::Vulkan)
    add_library(Vulkan::Vulkan UNKNOWN IMPORTED)
    set_target_properties(Vulkan::Vulkan PROPERTIES
        IMPORTED_LOCATION "${Vulkan_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${Vulkan_INCLUDE_DIR}"
    )
endif()

# 添加第三方依赖
add_subdirectory(third_party/DiligentEngine)
add_subdirectory(third_party/entt)

# 设置你的源码路径
file(GLOB_RECURSE DEMO_SRC CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(${PROJECT_NAME} ${DEMO_SRC})

# 链接 DiligentEngine 的核心模块（根据需求添加更多）
target_link_libraries(${PROJECT_NAME}
    Diligent-Common
    Diligent-GraphicsEngine
    Diligent-GraphicsTools
    Diligent-GraphicsAccessories
    Diligent-ShaderTools
    Diligent-Platforms
    Diligent-BuildSettings
    Vulkan::Vulkan
)

# 链接 EnTT（头文件库）
target_include_directories(${PROJECT_NAME} PRIVATE third_party/entt/single_include)

# 添加 DiligentEngine 的 include（某些模块没用 target_include_directories）
target_include_directories(${PROJECT_NAME} PRIVATE
    third_party/DiligentEngine/Components
    third_party/DiligentEngine/DiligentCore
    third_party/DiligentEngine/Platforms
)
