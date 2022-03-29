
#ifndef SHADER_H
#define SHADER_H


#include "includes.h"
#include "defines.h"


namespace le
{

class Shader {
public:

	b8 init();
	void close();

	void use() const;

private:

	u32 shaderProgram{ 0 };

};


}


#endif
