
#include "Shader.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "filesystem/path.h"


namespace le
{

const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 uTransform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = uTransform * vec4(aPos, 1.0);\n"
    "}\0";
const char* fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 uColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = uColor;\n"
    "}\n\0";


static std::pair<u32, std::string> retrieveOpenGLShaderType(ShaderType type) {
    switch (type) {
    case ShaderType::VERTEX: return std::make_pair(GL_VERTEX_SHADER, "VERTEX");
    case ShaderType::FRAGMENT: return std::make_pair(GL_FRAGMENT_SHADER, "FRAGMENT");
    default: return std::make_pair(0, "NONE");
    }
}


static b8 compileShader(u32 shaderType, std::string shaderTypeStr, const char* shaderSource, u32* pID) {
    i32 success;

    *pID = glCreateShader(shaderType);
    glShaderSource(*pID, 1, &shaderSource, nullptr);
    glCompileShader(*pID);
    glGetShaderiv(*pID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(*pID, 512, nullptr, infoLog);
        LLOG("ERROR::SHADER::" + shaderTypeStr + "::COMPILATION_FAILED " + std::string(infoLog));
        return LFALSE;
    }
    LLOG("INFO::SHADER::" + shaderTypeStr + "::COMPILATION_SUCCESS");
    return LTRUE;
}


static b8 attachShader(ShaderInfo& info, u32 shaderProgram) {
    if (Path::exists(info.path.c_str())) {
        LLOG("Attaching shader " + info.path + " ...");
        std::string source;
        Path::readFile(info.path.c_str(), &source);
        auto [internalType, internalStr] = retrieveOpenGLShaderType(info.type);
        b8 success{ compileShader(internalType, internalStr, source.c_str(), &info.id) };
        if (success) {
            glAttachShader(shaderProgram, info.id);
            return LTRUE;
        }
        return LFALSE;
    }
    return LFALSE;
}


b8 Shader::init(ShaderSpecification shaderSpecs) {
    mShaderSpecs = shaderSpecs;

    i32 success;
    
    mShaderProgram = glCreateProgram();

    for (auto& info : mShaderSpecs.infos) {
        attachShader(info, mShaderProgram);
    }

    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);
        LLOG("ERROR::SHADER::PROGRAM::LINKING_FAILED " + std::string(infoLog));
        return LFALSE;
    }

    for (auto& info : mShaderSpecs.infos) {
        glDeleteShader(info.id);
    }

    LLOG("Shader initialized!");
    return LTRUE;
}


void Shader::close() {
    glDeleteProgram(mShaderProgram);
    LLOG("Shader closed!");
}


void Shader::use() const {
    glUseProgram(mShaderProgram);
}


void Shader::setBool(const char* name, b32 value) const {
    glUniform1i(glGetUniformLocation(mShaderProgram, name), value);
}


void Shader::setInt(const char* name, i32 value) const {
    glUniform1i(glGetUniformLocation(mShaderProgram, name), value);
}


void Shader::setFloat(const char* name, f32 value) const {
    glUniform1f(glGetUniformLocation(mShaderProgram, name), value);
}


void Shader::setVec3(const char* name, vec3 value) const {
    glUniform3fv(glGetUniformLocation(mShaderProgram, name), 1, &value.x);
}


void Shader::setVec3(const char* name, f32 x, f32 y, f32 z) const {
    glUniform3f(glGetUniformLocation(mShaderProgram, name), x, y, z);
}


void Shader::setVec4(const char* name, const vec4& value) const {
    glUniform4fv(glGetUniformLocation(mShaderProgram, name), 1, &value.x);
}


void Shader::setVec4(const char* name, f32 x, f32 y, f32 z, f32 w) const {
    glUniform4f(glGetUniformLocation(mShaderProgram, name), x, y, z, w);
}


void Shader::setMat4(const char* name, const mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram, name), 1, GL_FALSE, &mat.elements[0]);
}


void Shader::setMat4(const char* name, const f32* mat) const {
    glUniformMatrix4fv(glGetUniformLocation(mShaderProgram, name), 1, GL_FALSE, mat);
}


}
