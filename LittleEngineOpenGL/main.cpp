
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


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static glm::mat4 convert(const le::mat4& m) {
    glm::mat4 rtn{
        m[0 + 0 * 4], m[1 + 0 * 4], m[2 + 0 * 4], m[3 + 0 * 4],
        m[0 + 1 * 4], m[1 + 1 * 4], m[2 + 1 * 4], m[3 + 1 * 4],
        m[0 + 2 * 4], m[1 + 2 * 4], m[2 + 2 * 4], m[3 + 2 * 4],
        m[0 + 3 * 4], m[1 + 3 * 4], m[2 + 3 * 4], m[3 + 3 * 4]
    };
    //rtn = {
    //    m[0 + 0 * 4], m[0 + 1 * 4], m[0 + 2 * 4], m[0 + 3 * 4],
    //    m[1 + 0 * 4], m[1 + 1 * 4], m[1 + 2 * 4], m[1 + 3 * 4],
    //    m[2 + 0 * 4], m[2 + 1 * 4], m[2 + 2 * 4], m[2 + 3 * 4],
    //    m[3 + 0 * 4], m[3 + 1 * 4], m[3 + 2 * 4], m[3 + 3 * 4]
    //};
    return rtn;
}


static glm::vec3 convert(le::vec3 v) {
    return { v.x, v.y, v.z };
}


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
        const glm::mat4 p = convert(pCamera->GetProjectionMatrix() * pCamera->GetViewMatrix());
        const glm::mat4 t = glm::translate(glm::mat4(1.f), { 1.f, 0.f, -2.f });
        const glm::mat4 r = glm::rotate(glm::mat4(1.f), (f32)glfwGetTime(), { 0.3f, 0.5f, 1.f });
        pShader->setMat4("transform", glm::value_ptr(p * t * r));
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
