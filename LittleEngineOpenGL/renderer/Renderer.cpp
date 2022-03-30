
#include "Renderer.h"
#include "Shader.h"
#include "Buffer.h"


namespace le
{


b8 Renderer::init(RendererSpecification _renderSpecs) {
    renderSpecs = _renderSpecs;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LLOG("Failed to initialize GLAD");
        return LFALSE;
    }
    glEnable(GL_DEPTH_TEST);
    LLOG("Renderer initialized!");
    return LTRUE;
}


void Renderer::clearScreen() const {
    glClearColor(renderSpecs.clearColor.r, renderSpecs.clearColor.g,
                 renderSpecs.clearColor.b, renderSpecs.clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::draw(Shader* pShader, Buffer* pBuffer, void(*uniformSetupFunc)(Camera* pCamera, Shader* pShader)) const {
    pShader->use();
    uniformSetupFunc(renderSpecs.pCamera, pShader);
    pBuffer->use();
    glDrawElements(GL_TRIANGLES, pBuffer->getSpecs().countIndices, GL_UNSIGNED_INT, 0);
}


}
