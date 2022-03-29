
#include "includes.h"
#include "defines.h"
#include "math/vec3.h"
#include "window/Window.h"
#include "window/Input.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/Buffer.h"


auto main() -> i32 {
    le::WindowSpecification windowSpecs;
    windowSpecs.width = 800;
    windowSpecs.height = 600;
    windowSpecs.name = "LittleEngineOpenGL v0.1 OpenGL 4.6.0";

    le::Window window;
    window.init(windowSpecs);

    le::InputSpecification inputSpecs;
    inputSpecs.pWindow = &window;

    le::Input input;
    input.init(inputSpecs);

    le::RendererSpecification renderSpecs;
    renderSpecs.clearColor = le::color4{ 0.2f, 0.3f, 0.7f, 1.f };

    le::Renderer renderer;
    renderer.init(renderSpecs);

    le::Shader shader;
    shader.init();
    shader.use();
    shader.setFloat("uColor", 0.5f);

    std::vector<f32> vertices{
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f 
    };
    std::vector<u32> indices{
        0, 1, 3,
        1, 2, 3,
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

    while (!window.isGoingToClose()) {
        input.process();

        renderer.clearScreen();
        renderer.draw(&shader, &buffer);

        window.swapBuffers();
    }

    buffer.close();
    shader.close();
    input.close();
    window.close();
    
    return 0;
}
