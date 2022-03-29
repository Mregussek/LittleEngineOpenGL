
#include "Input.h"
#include "Window.h"


namespace le
{


b8 Input::init(InputSpecification _inputSpecs) {
	inputSpecs = _inputSpecs;
	std::cout << "Input initialized!\n";
	return LTRUE;
}


void Input::close() {
	std::cout << "Input closed!\n";
}


void Input::process() const {
	GLFWwindow* pGLFWWindow{ inputSpecs.pWindow->pWindow };
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(pGLFWWindow, true);
}


}
