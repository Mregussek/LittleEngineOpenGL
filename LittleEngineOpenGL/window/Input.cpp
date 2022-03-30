
#include "Input.h"
#include "Window.h"
#include "renderer/Camera.h"


namespace le
{


b8 Input::init(InputSpecification _inputSpecs) {
	inputSpecs = _inputSpecs;
	LLOG("Input initialized!");
	return LTRUE;
}


void Input::close() {
	LLOG("Input closed!");
}


void Input::process() const {
	GLFWwindow* pGLFWWindow{ inputSpecs.pWindow->pWindow };
	const f32 deltaTime{ inputSpecs.pWindow->getDeltaTime() };
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(pGLFWWindow, true);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_W) == GLFW_PRESS) {
		inputSpecs.pCamera->processKeyboard(CameraMovement::FORWARD, deltaTime);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_S) == GLFW_PRESS) {
		inputSpecs.pCamera->processKeyboard(CameraMovement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_A) == GLFW_PRESS) {
		inputSpecs.pCamera->processKeyboard(CameraMovement::LEFT, deltaTime);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_D) == GLFW_PRESS) {
		inputSpecs.pCamera->processKeyboard(CameraMovement::RIGHT, deltaTime);
	}
}


}
