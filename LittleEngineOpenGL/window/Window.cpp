
#include "Window.h"
#include "renderer/Camera.h"


namespace le
{


f32 lastX{ 0.f };
f32 lastY{ 0.f };
b8 firstMouse{ LTRUE };
Window* sWindow{ nullptr };
Camera* sCamera{ nullptr };


static void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
static void mouseCallback(GLFWwindow* pWindow, f64 xposIn, f64 yposIn);
static void scrollCallback(GLFWwindow* pWindow, f64 xoffset, f64 yoffset);


b8 Window::init(WindowSpecification _windowSpecs) {
    windowSpecs = _windowSpecs;
    sWindow = this;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    pWindow = glfwCreateWindow(windowSpecs.width, windowSpecs.height, windowSpecs.name.c_str(), nullptr, nullptr);
    if (!pWindow) {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return LFALSE;
    }
    glfwMakeContextCurrent(pWindow);
    glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);
    glfwSetInputMode(pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    std::cout << "Window initialized!\n";
    return LTRUE;
}


void Window::close() {
    glfwTerminate();
    std::cout << "Window closed!\n";
}


void Window::updateDeltaTime() {
    const f32 currentFrame{ (f32)glfwGetTime() };
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}


void Window::swapBuffers() const {
    glfwSwapBuffers(pWindow);
    glfwPollEvents();
}


b8 Window::isGoingToClose() const {
    return glfwWindowShouldClose(pWindow) ? LTRUE : LFALSE;
}


f32 Window::getDeltaTime() const {
    return deltaTime;
}


void Window::setSize(i32 w, i32 h) {
    windowSpecs.width = w;
    windowSpecs.height = h;
    windowSpecs.aspectRatio = (f32)w / (f32)h;
}


void Window::updateCallbacksForCamera(Camera* _pCamera) {
    pCamera = _pCamera;
    sCamera = pCamera;
    lastX = (f32)windowSpecs.width / 2.f;
    lastY = (f32)windowSpecs.height / 2.f;
    firstMouse = LTRUE;
    glfwSetCursorPosCallback(pWindow, mouseCallback);
    glfwSetScrollCallback(pWindow, scrollCallback);
}


void framebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
    sWindow->setSize(width, height);
    glViewport(0, 0, width, height);
}


void mouseCallback(GLFWwindow* pWindow, f64 xposIn, f64 yposIn) {
    const f32 xpos{ (f32)xposIn };
    const f32 ypos{ (f32)yposIn };

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    f32 xoffset{ xpos - lastX };
    f32 yoffset{ lastY - ypos };

    lastX = xpos;
    lastY = ypos;

    if (sCamera) {
        // sCamera->ProcessMouseMovement(xoffset, yoffset);
    }
}


void scrollCallback(GLFWwindow* pWindow, f64 xoffset, f64 yoffset) {
    if (sCamera) {
        // sCamera->ProcessMouseScroll((f32)yoffset);
    }
}


}
