
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
#include "models/Cube.h"


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
    shader.setFloat("uColor", 0.5f);

    le::Cube cube;

    le::BufferSpecification bufferSpecs;
    bufferSpecs.pVertices = cube.vertices.data();
    bufferSpecs.countVertices = (u32)cube.vertices.size();
    bufferSpecs.sizeofVertices = (u32)cube.vertices.size() * sizeof(decltype(cube.vertices[0]));
    bufferSpecs.pIndices = cube.indices.data();
    bufferSpecs.countIndices = (u32)cube.indices.size();
    bufferSpecs.sizeofIndices = (u32)cube.indices.size() * sizeof(decltype(cube.indices[0]));

    le::Buffer buffer;
    buffer.init(bufferSpecs);

    auto rotateObject = [](le::Camera* pCamera, le::Shader* pShader) {
        const le::mat4 transform = pCamera->getProjectionMatrix() *
                                   pCamera->getViewMatrix() *
                                   le::mat4::translation({ 1.f, 0.f, -2.f }) *
                                   le::mat4::rotation((f32)glfwGetTime(), { 0.3f, 0.5f, 1.f }) *
                                   le::mat4::scale({ 1.f, 1.f, 1.f });
        pShader->setMat4("transform", transform);
    };

    while (!window.isGoingToClose()) {
        window.updateDeltaTime();
        input.process();

        renderSpecs.clearColor = le::color4::random(0.f, 0.1f);
        renderer.updateSpecs(renderSpecs);

        renderer.clearScreen();
        renderer.draw(&shader, &buffer, rotateObject);

        window.swapBuffers();
    }

    buffer.close();
    shader.close();
    input.close();
    window.close();
    
    return 0;
}
