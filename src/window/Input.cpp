
#include "Input.h"
#include "Window.h"
#include "renderer/Camera.h"


namespace le
{


b8 Input::init(InputSpecification _inputSpecs) {
	mInputSpecs = _inputSpecs;
	LLOG("Input initialized!");
	return LTRUE;
}


void Input::close() {
	LLOG("Input closed!");
}


void Input::process() const {
	GLFWwindow* pGLFWWindow{ mInputSpecs.pWindow->pWindow };
	const f32 deltaTime{ mInputSpecs.pWindow->getDeltaTime() };
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(pGLFWWindow, true);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_W) == GLFW_PRESS) {
		mInputSpecs.pCamera->processKeyboard(CameraMovement::FORWARD, deltaTime);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_S) == GLFW_PRESS) {
		mInputSpecs.pCamera->processKeyboard(CameraMovement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_A) == GLFW_PRESS) {
		mInputSpecs.pCamera->processKeyboard(CameraMovement::LEFT, deltaTime);
	}
	if (glfwGetKey(pGLFWWindow, GLFW_KEY_D) == GLFW_PRESS) {
		mInputSpecs.pCamera->processKeyboard(CameraMovement::RIGHT, deltaTime);
	}
}


}
