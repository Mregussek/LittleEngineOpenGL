
#include "Renderer.h"
#include "Shader.h"
#include "Buffer.h"


namespace le
{


b8 Renderer::init(RendererSpecification _renderSpecs) {
    renderSpecs = _renderSpecs;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return LFALSE;
    }
    glEnable(GL_DEPTH_TEST);
    std::cout << "Renderer initialized!\n";
    return LTRUE;
}


void Renderer::clearScreen() const {
    glClearColor(renderSpecs.clearColor.r, renderSpecs.clearColor.g,
                 renderSpecs.clearColor.b, renderSpecs.clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::draw(Shader* pShader, Buffer* pBuffer, void(*uniformSetupFunc)(Shader* pShader)) const {
    pShader->use();
    uniformSetupFunc(pShader);
    pBuffer->use();
    glDrawElements(GL_TRIANGLES, pBuffer->getSpecs().countIndices, GL_UNSIGNED_INT, 0);
}


}
