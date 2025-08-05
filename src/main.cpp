#include "DiligentCore/Graphics/GraphicsEngine/interface/EngineFactory.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h"
#include "DiligentCore/Graphics/GraphicsEngine/interface/SwapChain.h"
#include "DiligentCore/Common/interface/RefCntAutoPtr.hpp"

#include "DiligentCore/Graphics/GraphicsEngineVulkan/interface/EngineFactoryVk.h"
#include "DiligentCore/Platforms/Basic/interface/BasicPlatformMisc.hpp"
#include "DiligentCore/Platforms/interface/NativeWindow.h"

#include "GLFW/glfw3.h"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <windows.h>
#include "GLFW/glfw3native.h"
#endif

#include <iostream>

using namespace Diligent;

int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW 初始化失败\n";
        return -1;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Diligent Vulkan Minimal", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "窗口创建失败\n";
        glfwTerminate();
        return -1;
    }

#ifdef _WIN32
    HWND hwnd = glfwGetWin32Window(window);
    NativeWindow nativeWindow{ hwnd };
#else
    std::cerr << "仅支持 Windows 平台\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
#endif

    auto* GetEngineFactoryVk = LoadGraphicsEngineVk();
    auto* pFactoryVk = GetEngineFactoryVk();

    RefCntAutoPtr<IRenderDevice> pDevice;
    RefCntAutoPtr<IDeviceContext> pImmediateContext;
    RefCntAutoPtr<ISwapChain> pSwapChain;

    EngineVkCreateInfo EngCreateInfo{};

    // 如需启用动态渲染及其依赖扩展，可取消以下注释
    /*
    const char* Extensions[] = {
        "VK_KHR_dynamic_rendering",
        "VK_KHR_depth_stencil_resolve"
    };
    EngCreateInfo.ppDeviceExtensionNames = Extensions;
    EngCreateInfo.DeviceExtensionCount = _countof(Extensions);
    */

    // 创建设备和上下文
    pFactoryVk->CreateDeviceAndContextsVk(
        EngCreateInfo,
        &pDevice,
        &pImmediateContext
    );

    SwapChainDesc SCDesc{};
    SCDesc.Width = 1280;
    SCDesc.Height = 720;
    SCDesc.ColorBufferFormat = TEX_FORMAT_RGBA8_UNORM;
    SCDesc.DepthBufferFormat = TEX_FORMAT_D32_FLOAT;

    pFactoryVk->CreateSwapChainVk(
        pDevice,
        pImmediateContext,
        SCDesc,
        nativeWindow,
        &pSwapChain
    );

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        const float clearColor[] = {0.2f, 0.3f, 0.3f, 1.0f};

        auto* pRTV = pSwapChain->GetCurrentBackBufferRTV();
        auto* pDSV = pSwapChain->GetDepthBufferDSV();

        // 设置渲染目标
        pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

        // 清除颜色和深度缓冲
        pImmediateContext->ClearRenderTarget(pRTV, clearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.0f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

        pSwapChain->Present();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
