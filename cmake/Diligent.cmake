# cmake/diligent.cmake

option(DILIGENT_BUILD_TOOLS "Build DiligentTools module" ON)
option(DILIGENT_BUILD_FX "Build DiligentFX module" ON)
option(DILIGENT_BUILD_SAMPLES "Build DiligentSamples module" OFF)  # 你不用samples默认关掉
option(DILIGENT_BUILD_DOCS "Build documentation" OFF)

# 只添加子模块路径，没有变动你本地目录结构
add_subdirectory(third_party/DiligentCore)

if(${DILIGENT_BUILD_TOOLS})
    add_subdirectory(third_party/DiligentTools)
else()
    if(${DILIGENT_BUILD_FX})
        message(STATUS "Disabling DiligentFX module as it requires DiligentTools module to be enabled")
        set(DILIGENT_BUILD_FX OFF CACHE BOOL "Build DiligentFX module" FORCE)
    endif()

    if (${DILIGENT_BUILD_SAMPLES})
        message(STATUS "Disabling DiligentSamples module as it requires DiligentTools module to be enabled")
        set(DILIGENT_BUILD_SAMPLES OFF CACHE BOOL "Build DiligentSamples module" FORCE)
    endif()
endif()

if(${DILIGENT_BUILD_FX})
    add_subdirectory(third_party/DiligentFX)
endif()

if(${DILIGENT_BUILD_SAMPLES})
    add_subdirectory(third_party/DiligentSamples)
endif()

if(${DILIGENT_BUILD_DOCS})
    add_subdirectory(Doc)
endif()

# 这里根据你情况选，通常你项目里不会用社区模块，暂时注释
#if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/DiligentCommunity")
#    add_subdirectory(DiligentCommunity)
#endif()
