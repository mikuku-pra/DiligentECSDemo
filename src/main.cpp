
#include "Renderer/Renderer.hpp"
#include "UI/EditorUI.hpp"

int main() {
    Renderer renderer;
    if (renderer.Initialize()) {
        while (renderer.RenderFrame()) {
            EditorUI::Render(renderer.GetRegistry());
        }
    }
    renderer.Shutdown();
    return 0;
}
