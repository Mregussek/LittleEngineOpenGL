
#ifndef SHADER_H
#define SHADER_H


#include "../includes.h"
#include "../defines.h"


namespace le
{

class Shader {
public:

	b8 init();
	void close();

	void use() const;

	void setBool(const char* name, b32 value) const;
	void setInt(const char* name, i32 value) const;
	void setFloat(const char* name, f32 value) const;

private:

	u32 shaderProgram{ 0 };

};


}


#endif
