
#ifndef INPUT_H
#define INPUT_H


#include "includes.h"
#include "defines.h"


namespace le
{


class Window;
class Camera;


struct InputSpecification {

	Window* pWindow{ nullptr };
	Camera* pCamera{ nullptr };

};


class Input {
public:

	b8 init(InputSpecification _inputSpecs);
	void close();

	void process() const;

private:

	InputSpecification inputSpecs;

};


}


#endif
