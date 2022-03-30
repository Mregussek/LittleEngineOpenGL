
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


auto main() -> i32 {
    le::WindowSpecification windowSpecs;
    windowSpecs.width = 800;
    windowSpecs.height = 600;
    windowSpecs.name = "LittleEngineOpenGL v0.1 OpenGL 4.6.0";

    le::Window window;
    window.init(windowSpecs);

    le::CameraSpecification camSpecs;
    camSpecs.aspectRatio = (f32)windowSpecs.width / (f32)windowSpecs.height;
    camSpecs.position = { 0.f, 0.f, 1.f };
    camSpecs.up = { 0.f, 1.f, 0.f };
    camSpecs.front = { 0.f, 0.f, -1.f };
    camSpecs.yaw = -90.f;
    camSpecs.pitch = 0.f;
    camSpecs.movementSpeed = 2.5f;
    camSpecs.sensitivity = 0.1f;
    camSpecs.zoom = 45.f;

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

    std::array<f32, 24> vertices{
        -1.f, -1.f,  0.5f, // 0
         1.f, -1.f,  0.5f, // 1
        -1.f,  1.f,  0.5f, // 2
         1.f,  1.f,  0.5f, // 3
        -1.f, -1.f, -0.5f, // 4
         1.f, -1.f, -0.5f, // 5
        -1.f,  1.f, -0.5f, // 6
         1.f,  1.f, -0.5f  // 7
    };
    std::array<u32, 36> indices{
        // Top
        2, 6, 7,
        2, 3, 7,
        // Bottom
        0, 4, 5,
        0, 1, 5,
        // Left
        0, 2, 6,
        0, 4, 6,
        // Right
        1, 3, 7,
        1, 5, 7,
        // Front
        0, 2, 3,
        0, 1, 3,
        // Back
        4, 6, 7,
        4, 5, 7
    };

    le::BufferSpecification bufferSpecs;
    bufferSpecs.pVertices = vertices.data();
    bufferSpecs.countVertices = (u32)vertices.size();
    bufferSpecs.sizeofVertices = (u32)vertices.size() * sizeof(decltype(vertices[0]));
    bufferSpecs.pIndices = indices.data();
    bufferSpecs.countIndices = (u32)indices.size();
    bufferSpecs.sizeofIndices = (u32)indices.size() * sizeof(decltype(indices[0]));

    le::Buffer buffer;
    buffer.init(bufferSpecs);

    auto rotateObject = [](le::Camera* pCamera, le::Shader* pShader) {
        const le::mat4 p{ pCamera->GetProjectionMatrix() };
        const le::mat4 v{ pCamera->GetViewMatrix() };
        const le::mat4 t{ le::mat4::translation({ 0.f, 0.f, -1.f }) };
        const le::mat4 r{ le::mat4::rotation((f32)glfwGetTime(), { 0.f, 0.f, 1.f }) };
        const le::mat4 calc{ r };
        pShader->setMat4("transform", calc);
    };

    while (!window.isGoingToClose()) {
        window.updateDeltaTime();
        input.process();

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
