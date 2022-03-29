
#include "Input.h"
#include "Window.h"
#include "renderer/Camera.h"


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
	const f32 deltaTime{ inputSpecs.pWindow->getDeltaTime() };
	Camera* pCamera{ inputSpecs.pCamera };
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(pGLFWWindow, true);
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_W) == GLFW_PRESS)
		pCamera->ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_S) == GLFW_PRESS)
		pCamera->ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_A) == GLFW_PRESS)
		pCamera->ProcessKeyboard(CameraMovement::LEFT, deltaTime);
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_D) == GLFW_PRESS)
		pCamera->ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}


}
