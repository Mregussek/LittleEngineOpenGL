
#ifndef SHADER_H
#define SHADER_H


#include "includes.h"
#include "defines.h"


namespace le
{


struct vec3;
struct vec4;
struct mat4;


enum class ShaderType {
	NONE, VERTEX, FRAGMENT
};


struct ShaderInfo {
	std::string path;
	ShaderType type{ ShaderType::NONE };
	u32 id{}; // will be filled as internal variable!
};


struct ShaderSpecification {
	std::vector<ShaderInfo> infos;
};


class Shader {
public:

	b8 init(ShaderSpecification shaderSpecs);
	void close();

	void use() const;

	void setBool(const char* name, b32 value) const;
	void setInt(const char* name, i32 value) const;
	void setFloat(const char* name, f32 value) const;
	void setVec3(const char* name, vec3 value) const;
	void setVec3(const char* name, f32 x, f32 y, f32 z) const;
	void setVec4(const char* name, const vec4& value) const;
	void setVec4(const char* name, f32 x, f32 y, f32 z, f32 w) const;
	void setMat4(const char* name, const mat4& mat) const;
	void setMat4(const char* name, const f32* mat) const;

private:

	ShaderSpecification mShaderSpecs{};
	u32 mShaderProgram{ 0 };

};


}


#endif
