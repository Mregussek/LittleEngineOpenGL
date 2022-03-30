
#include "includes.h"
#include "defines.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "window/Window.h"
#include "window/Input.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/Buffer.h"
#include "renderer/Camera.h"
#include "models/Mesh.h"


auto main() -> i32 {
    le::WindowSpecification windowSpecs;
    windowSpecs.width = 800;
    windowSpecs.height = 600;
    windowSpecs.name = "LittleEngineOpenGL v0.1 OpenGL 4.6.0";
    windowSpecs.aspectRatio = 800.f / 600.f;

    le::Window window;
    window.init(windowSpecs);

    le::CameraSpecification camSpecs;
    camSpecs.aspectRatio = windowSpecs.aspectRatio;
    camSpecs.position = { 0.f, 0.f, 3.f };
    camSpecs.worldUp = { 0.f, 1.f, 0.f };
    camSpecs.front = { 0.f, 0.f, -1.f };
    camSpecs.yaw = -90.f;
    camSpecs.pitch = 0.f;
    camSpecs.movementSpeed = 2.5f;
    camSpecs.sensitivity = 0.1f;
    camSpecs.zoom = 45.f;
    camSpecs.near = 0.1f;
    camSpecs.far = 100.f;

    le::Camera camera;
    camera.init(camSpecs);
    window.updateCallbacksForCamera(&camera);

    le::InputSpecification inputSpecs;
    inputSpecs.pWindow = &window;
    inputSpecs.pCamera = &camera;

    le::Input input;
    input.init(inputSpecs);

    le::RendererSpecification renderSpecs;
    renderSpecs.clearColor = le::color4{ 0.2f, 0.3f, 0.7f, 1.f };
    renderSpecs.pCamera = &camera;

    le::Renderer renderer;
    renderer.init(renderSpecs);

    le::Shader shader;
    shader.init();
    shader.use();

    le::Cube cube;

    le::BufferSpecification bufferSpecs;
    bufferSpecs.pVertices = cube.vertices();
    bufferSpecs.countVertices = cube.countVertices();
    bufferSpecs.sizeofVertices = cube.sizeofVertices();
    bufferSpecs.pIndices = cube.indices();
    bufferSpecs.countIndices = cube.countIndices();
    bufferSpecs.sizeofIndices = cube.sizeofIndices();

    le::Buffer buffer;
    buffer.init(bufferSpecs);

    auto transformObject1 = [](le::Camera* pCamera, le::Shader* pShader) {
        const le::mat4 transform = pCamera->getProjectionMatrix() *
            pCamera->getViewMatrix() *
            le::mat4::translation({ 1.f, 0.f, -2.f }) *
            le::mat4::rotation((f32)glfwGetTime(), { 0.3f, 0.5f, 1.f }) *
            le::mat4::scale({ 1.f, 1.f, 1.f });
        pShader->setMat4("uTransform", transform);
        pShader->setVec4("uColor", le::vec4{ 0.8f, 0.1f, 0.3f, 1.f });
    };
    auto transformObject2 = [](le::Camera* pCamera, le::Shader* pShader) {
        const le::mat4 transform = pCamera->getProjectionMatrix() *
            pCamera->getViewMatrix() *
            le::mat4::translation({ -1.f, 0.f, -1.f }) *
            le::mat4::rotation((f32)glfwGetTime(), { 1.f, 0.5f, 0.3f }) *
            le::mat4::scale({ 1.f, 1.f, 1.f });
        pShader->setMat4("uTransform", transform);
        pShader->setVec4("uColor", le::vec4{ 0.1f, 0.8f, 0.3f, 1.f });
    };

    le::RenderModelSpecification renderModelSpecs1;
    renderModelSpecs1.pShader = &shader;
    renderModelSpecs1.pBuffer = &buffer;
    renderModelSpecs1.pUniformSetupFunc = transformObject1;

    le::RenderModelSpecification renderModelSpecs2;
    renderModelSpecs2.pShader = &shader;
    renderModelSpecs2.pBuffer = &buffer;
    renderModelSpecs2.pUniformSetupFunc = transformObject2;

    while (!window.isGoingToClose()) {
        window.updateDeltaTime();
        input.process();

        renderSpecs.clearColor = le::color4::random(0.f, 0.1f);
        renderer.updateSpecs(renderSpecs);

        renderer.clearScreen();
        renderer.draw(renderModelSpecs1);
        renderer.draw(renderModelSpecs2);

        window.swapBuffers();
    }

    buffer.close();
    shader.close();
    input.close();
    window.close();
    
    return 0;
}
