
#ifndef WINDOW_H
#define WINDOW_H


#include "includes.h"
#include "defines.h"


namespace le
{


class Camera;


struct WindowSpecification {

	std::string name{ "LittleEngineOpenGL" };
	i32 width{ 0 };
	i32 height{ 0 };
	f32 aspectRatio{ 0.f };

};


class Window {

	friend class Input;

public:

	b8 init(WindowSpecification _windowSpecs);
	void close();

	void updateDeltaTime();
	void swapBuffers() const;

	b8 isGoingToClose() const;
	f32 getDeltaTime() const;
	
	void setSize(i32 w, i32 h);

	void updateCallbacksForCamera(Camera* _pCamera);

private:

	WindowSpecification windowSpecs{};
	GLFWwindow* pWindow{ nullptr };
	Camera* pCamera{ nullptr };
	f32 deltaTime{ 0.0f };
	f32 lastFrame{ 0.0f };

};


}


#endif
