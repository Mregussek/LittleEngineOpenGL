
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
#include "renderer/PointLight.h"

#include "game/Entity.h"
#include "game/Utilities.h"
#include "game/Place.h"


auto main() -> i32 {
    le::WindowSpecification windowSpecs;
    windowSpecs.width = 800;
    windowSpecs.height = 600;
    windowSpecs.name = "LittleEngineOpenGL v0.5 OpenGL 4.6.0";
    windowSpecs.aspectRatio = (f32)windowSpecs.width / (f32)windowSpecs.height;

    le::Window window;
    window.init(windowSpecs);

    le::CameraSpecification camSpecs;
    camSpecs.aspectRatio = windowSpecs.aspectRatio;
    camSpecs.position = { 3.f, 2.f, 3.f };
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

    le::ShaderInfo vertexShader;
    vertexShader.type = le::ShaderType::VERTEX;
    vertexShader.path = "resources/default.vertex.glsl";

    le::ShaderInfo fragmentShader;
    fragmentShader.type = le::ShaderType::FRAGMENT;
    fragmentShader.path = "resources/default.fragment.glsl";

    le::ShaderSpecification shaderSpecs;
    shaderSpecs.infos = { vertexShader, fragmentShader };

    le::Shader shader;
    shader.init(shaderSpecs);
    shader.use();

    le::PointLightSpecification pointLightSpecs;
    pointLightSpecs.position = { 2.f, 2.f, 1.f };
    pointLightSpecs.color = { 0.5f, 1.f, 0.5f };

    le::PointLight pointLight(pointLightSpecs);

    le::ObjMeshFactory objMeshFactory;
    objMeshFactory.init();

    le::BufferFactory bufferFactory;
    for (u32 i = 0; i < objMeshFactory.size(); i++) {
        bufferFactory.add(objMeshFactory.get(i));
    }

    le::ParkingEntity parkingEntity;
    le::CarEntity carEntity;

    le::EntityPointerVector entityPointerVector{
        &parkingEntity, &carEntity
    };

    for (le::Entity* pEntity : entityPointerVector) {
        pEntity->start();
    }
    
    le::MeshRuntimeSpecificationVector meshRuntimeSpecsVector;
    fillMeshRuntimeSpecsWithParkingEntity(&parkingEntity, &meshRuntimeSpecsVector);

    auto uniformSetupFunc = [](le::Camera* pCamera, le::Shader* pShader, le::MeshRuntimeSpecification* pMeshSpecs,
                               le::PointLight* pPointLight) {
        const le::mat4 objectMatrix =
            le::mat4::translation(pMeshSpecs->position) *
            le::mat4::rotation(pMeshSpecs->rotateFunc(pMeshSpecs->angle), pMeshSpecs->rotation) *
            le::mat4::scale(pMeshSpecs->scale);
        const le::mat4 objectSeenThroughCameraMatrix =
            pCamera->getProjectionMatrix() *
            pCamera->getViewMatrix() *
            pCamera->getModelMartix() *
            objectMatrix;

        // Vertex Uniforms
        pShader->setMat4("uModel", pCamera->getModelMartix());
        pShader->setMat4("uObjectMatrix", objectMatrix);
        pShader->setMat4("uTransform", objectSeenThroughCameraMatrix);
        // Fragment Uniforms
        pShader->setVec4("uMeshColor", pMeshSpecs->color);
        pShader->setVec3("uLightColor", pPointLight->getColor());
        pShader->setVec3("uLightPosition", pPointLight->getPosition());
        pShader->setVec3("uCameraPosition", pCamera->getPositionVec());
    };

    le::RenderModelSpecification renderModelSpecs;
    renderModelSpecs.pShader = &shader;
    renderModelSpecs.pBuffer = nullptr; // to be filled later...
    renderModelSpecs.pPointLight = &pointLight;
    renderModelSpecs.pUniformSetupFunc = uniformSetupFunc;
    renderModelSpecs.pMeshSpecs = nullptr; // To be filled later...

    LLOG("Starting rendering!");

    while (!window.isGoingToClose()) {
        window.updateDeltaTime();
        input.process();

        renderSpecs.clearColor = le::color4::random(0.f, 0.1f);
        renderer.updateSpecs(renderSpecs);

        renderer.clearScreen();
        for (u32 i = 0; i < meshRuntimeSpecsVector.size(); i++) {
            le::MeshRuntimeSpecification& meshSpecs{ meshRuntimeSpecsVector[i] };
            renderModelSpecs.pBuffer = bufferFactory.get(meshSpecs.type);
            renderModelSpecs.pMeshSpecs = &meshSpecs;

            renderer.draw(renderModelSpecs);
        }

        window.swapBuffers();
    }


    for (le::Entity* pEntity : entityPointerVector) {
        pEntity->close();
    }
    bufferFactory.clear();
    objMeshFactory.close();
    meshRuntimeSpecsVector.clear();
    shader.close();
    input.close();
    window.close();
    
    return 0;
}
