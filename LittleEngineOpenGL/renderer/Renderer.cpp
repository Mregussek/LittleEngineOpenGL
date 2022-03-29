
#include "Renderer.h"
#include "Shader.h"
#include "Buffer.h"


namespace le
{


b8 Renderer::init(RendererSpecification _renderSpecs) {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return LFALSE;
    }
    renderSpecs = _renderSpecs;
    std::cout << "Renderer initialized!\n";
    return LTRUE;
}


void Renderer::clearScreen() const {
    glClearColor(renderSpecs.clearColor.r, renderSpecs.clearColor.g,
                 renderSpecs.clearColor.b, renderSpecs.clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::draw(Shader* pShader, Buffer* pBuffer) const {
    pShader->use();
    pBuffer->use();
    glDrawElements(GL_TRIANGLES, pBuffer->getSpecs().countIndices, GL_UNSIGNED_INT, 0);
}


}
