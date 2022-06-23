
#include "Renderer.h"
#include "Shader.h"
#include "Buffer.h"
#include "Mesh.h"


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


void Renderer::draw(const RenderModelSpecification& renderModelSpecs) const {
    renderModelSpecs.pShader->use();
    renderModelSpecs.pUniformSetupFunc(mRenderSpecs.pCamera,
                                       renderModelSpecs.pShader,
                                       renderModelSpecs.pMeshSpecs,
                                       renderModelSpecs.pPointLight);
    renderModelSpecs.pBuffer->use();
    glDrawElements(GL_TRIANGLES, renderModelSpecs.pBuffer->getSpecs().countIndices, GL_UNSIGNED_INT, 0);
}


}
