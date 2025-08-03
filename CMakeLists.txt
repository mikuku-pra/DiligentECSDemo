cmake_minimum_required(VERSION 3.16)
project(DiligentECSDemo LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 Vulkan SDK 路径环境变量（请根据你本地实际路径修改）
set(ENV{VULKAN_SDK} "D:/file/vulkanSdk")
set(Vulkan_INCLUDE_DIR "$ENV{VULKAN_SDK}/Include")
set(Vulkan_LIBRARY "$ENV{VULKAN_SDK}/Lib/vulkan-1.lib")

find_package(Vulkan REQUIRED)

if(NOT TARGET Vulkan::Vulkan)
    add_library(Vulkan::Vulkan UNKNOWN IMPORTED)
    set_target_properties(Vulkan::Vulkan PROPERTIES
        IMPORTED_LOCATION "${Vulkan_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${Vulkan_INCLUDE_DIR}"
    )
endif()

add_subdirectory(third_party/DiligentEngine)
add_subdirectory(third_party/entt)

file(GLOB_RECURSE DEMO_SRC CONFIGURE_DEPENDS
    src/*.cpp
    src/*.h
)

add_executable(${PROJECT_NAME} ${DEMO_SRC})

target_link_libraries(${PROJECT_NAME}
    DiligentEngine
    Vulkan::Vulkan
)

target_include_directories(${PROJECT_NAME} PRIVATE third_party/entt/single_include)

target_include_directories(${PROJECT_NAME} PRIVATE
    third_party/DiligentEngine/Components
    third_party/DiligentEngine/DiligentCore
    third_party/DiligentEngine/Platforms
)
