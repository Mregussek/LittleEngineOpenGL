
#include "Renderer.h"
#include "Shader.h"
#include "Buffer.h"


namespace le
{


b8 Renderer::init(RendererSpecification _renderSpecs) {
    mRenderSpecs = _renderSpecs;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LLOG("Failed to initialize GLAD");
        return LFALSE;
    }
    glEnable(GL_DEPTH_TEST);
    LLOG("Renderer initialized!");
    return LTRUE;
}


void Renderer::updateSpecs(RendererSpecification _renderSpecs) {
    mRenderSpecs = _renderSpecs;
}


void Renderer::clearScreen() const {
    glClearColor(mRenderSpecs.clearColor.r, mRenderSpecs.clearColor.g,
                 mRenderSpecs.clearColor.b, mRenderSpecs.clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::draw(Shader* pShader, Buffer* pBuffer, void(*uniformSetupFunc)(Camera* pCamera, Shader* pShader)) const {
    pShader->use();
    uniformSetupFunc(mRenderSpecs.pCamera, pShader);
    pBuffer->use();
    glDrawElements(GL_TRIANGLES, pBuffer->getSpecs().countIndices, GL_UNSIGNED_INT, 0);
}


}
