
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
#include "renderer/Mesh.h"
#include "renderer/Colors.h"


auto main() -> i32 {
    le::WindowSpecification windowSpecs;
    windowSpecs.width = 800;
    windowSpecs.height = 600;
    windowSpecs.name = "LittleEngineOpenGL v0.1 OpenGL 4.6.0";
    windowSpecs.aspectRatio = (f32)windowSpecs.width / (f32)windowSpecs.height;

    le::Window window;
    window.init(windowSpecs);

    le::CameraSpecification camSpecs;
    camSpecs.aspectRatio = windowSpecs.aspectRatio;
    camSpecs.position = { 7.5f, 0.f, 3.f };
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

    le::BufferSpecification bufferSpecsCube;
    bufferSpecsCube.pVertices = cube.vertices();
    bufferSpecsCube.countVertices = cube.countVertices();
    bufferSpecsCube.sizeofVertices = cube.sizeofVertices();
    bufferSpecsCube.pIndices = cube.indices();
    bufferSpecsCube.countIndices = cube.countIndices();
    bufferSpecsCube.sizeofIndices = cube.sizeofIndices();

    le::Buffer bufferCube;
    bufferCube.init(bufferSpecsCube);

    auto rotateFunc = []()->f32 {
        return (f32)glfwGetTime();
    };
    auto generateMeshSpecification = [&rotateFunc](f32 x, f32 y, f32 z, le::ColorType ct)->std::vector<le::MeshSpecification> {
        return {
            { le::Colors::red(ct), le::point3{1.f + x, 0.f + y, -2.f + z}, le::rotation3{0.3f, 0.5f, 1.f}, rotateFunc},
            { le::Colors::green(ct), le::point3{ -1.f + x, 0.f + y, -2.f + z }, le::rotation3{ 0.3f, 0.5f, 1.f }, rotateFunc },
            { le::Colors::blue(ct), le::point3{ 0.f + x, 1.f + y, -3.f + z }, le::rotation3{ 0.3f, 0.5f, 1.f }, rotateFunc },
            { le::Colors::yellow(ct), le::point3{ 0.f + x, -1.f + y, -2.f + z }, le::rotation3{ 0.3f, 0.5f, 1.f }, rotateFunc },
            { le::Colors::orange(ct), le::point3{ 1.f + x, 2.f + y, -2.f + z }, le::rotation3{ 0.3f, 0.5f, 1.f }, rotateFunc },
            { le::Colors::pink(ct), le::point3{ -1.f + x, 2.f + y, -2.f + z }, le::rotation3{ 0.3f, 0.5f, 1.f }, rotateFunc },
        };
    };

    auto meshSpecifications1{ generateMeshSpecification(0.f, 0.f, 0.f, le::ColorType::DEFAULT) };
    auto meshSpecifications2{ generateMeshSpecification(6.f, 0.f, 0.f, le::ColorType::LIGHT) };
    auto meshSpecifications3{ generateMeshSpecification(-6.f, 0.f, 0.f, le::ColorType::DARK) };

    auto transformObject = [](le::Camera* pCamera, le::Shader* pShader, le::MeshSpecification* pMeshSpecs) {
        const le::mat4 transform = pCamera->getProjectionMatrix() *
            pCamera->getViewMatrix() *
            le::mat4::translation(pMeshSpecs->position) *
            le::mat4::rotation(pMeshSpecs->rotateFunc(), pMeshSpecs->rotation) *
            le::mat4::scale({ 1.f, 1.f, 1.f });
        pShader->setMat4("uTransform", transform);
        pShader->setVec4("uColor", pMeshSpecs->color);
    };

    le::RenderModelSpecification renderModelSpecs;
    renderModelSpecs.pShader = &shader;
    renderModelSpecs.pBuffer = &bufferCube;
    renderModelSpecs.pUniformSetupFunc = transformObject;

    while (!window.isGoingToClose()) {
        window.updateDeltaTime();
        input.process();

        renderSpecs.clearColor = le::color4::random(0.f, 0.1f);
        renderer.updateSpecs(renderSpecs);

        renderer.clearScreen();
        for (auto& meshSpecs : meshSpecifications1) {
            renderModelSpecs.pMeshSpecs = &meshSpecs;
            renderer.draw(renderModelSpecs);
        }
        for (auto& meshSpecs : meshSpecifications2) {
            renderModelSpecs.pMeshSpecs = &meshSpecs;
            renderer.draw(renderModelSpecs);
        }
        for (auto& meshSpecs : meshSpecifications3) {
            renderModelSpecs.pMeshSpecs = &meshSpecs;
            renderer.draw(renderModelSpecs);
        }

        window.swapBuffers();
    }

    bufferCube.close();
    shader.close();
    input.close();
    window.close();
    
    return 0;
}
