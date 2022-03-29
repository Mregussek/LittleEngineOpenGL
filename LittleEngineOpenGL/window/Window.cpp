
#include "Window.h"


namespace le
{


b8 Window::init(WindowSpecification windowSpecs) {
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
    
    auto framebufferSizeCallback = [](GLFWwindow* window, i32 width, i32 height) {
        glViewport(0, 0, width, height);
    };
    glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);
    std::cout << "Window initialized!\n";
    return LTRUE;
}


void Window::close() {
    glfwTerminate();
    std::cout << "Window closed!\n";
}


void Window::swapBuffers() const {
    glfwSwapBuffers(pWindow);
    glfwPollEvents();
}


b8 Window::isGoingToClose() const {
    return glfwWindowShouldClose(pWindow) ? LTRUE : LFALSE;
}


}
