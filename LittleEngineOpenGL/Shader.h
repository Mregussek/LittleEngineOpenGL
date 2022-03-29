
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

	void setBool(const std::string& name, b32 value) const;
	void setInt(const std::string& name, i32 value) const;
	void setFloat(const std::string& name, f32 value) const;

private:

	u32 shaderProgram{ 0 };

};


}


#endif
