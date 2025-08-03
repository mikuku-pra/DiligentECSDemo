#include <iostream>
#include <DiligentCore/Graphics/GraphicsEngine/interface/EngineFactory.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <DiligentCore/Graphics/GraphicsEngine/interface/DeviceContext.h>

int main()
{
    std::cout << "Diligent Engine Vulkan Demo Start\n";

    Diligent::RefCntAutoPtr<Diligent::IRenderDevice> renderDevice;
    Diligent::RefCntAutoPtr<Diligent::IDeviceContext> deviceContext;

    // 这里简单示意初始化，实际使用请参考Diligent Engine文档
    Diligent::EngineCreateInfo engineCI;
    Diligent::CreateEngineD3D11(engineCI, &renderDevice, &deviceContext);  // 这里示例用D3D11替代，Vulkan用CreateEngineVk

    std::cout << "Demo ended.\n";
    return 0;
}
