
#ifndef WINDOW_H
#define WINDOW_H


#include "../includes.h"
#include "../defines.h"


namespace le
{


struct WindowSpecification {

	std::string name{ "LittleEngineOpenGL" };
	i32 width{ 0 };
	i32 height{ 0 };

};


class Window {

	friend class Input;

public:

	b8 init(WindowSpecification specs);
	void close();

	void swapBuffers() const;

	b8 isGoingToClose() const;

private:

	GLFWwindow* pWindow{ nullptr };

};


}


#endif
