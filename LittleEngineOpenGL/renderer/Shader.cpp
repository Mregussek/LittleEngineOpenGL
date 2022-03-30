
#include "Shader.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"


namespace le
{

const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0);\n"
    "}\0";
const char* fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "uniform float uColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(uColor, uColor, uColor, 1.0f);\n"
    "}\n\0";


b8 Shader::init() {
    i32 success;
    char infoLog[512];

    u32 vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        LLOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED " + std::string(infoLog));
        return LFALSE;
    }

    u32 fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        LLOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED " + std::string(infoLog));
        return LFALSE;
    }

    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, vertexShader);
    glAttachShader(mShaderProgram, fragmentShader);
    glLinkProgram(mShaderProgram);
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mShaderProgram, 512, nullptr, infoLog);
        LLOG("ERROR::SHADER::PROGRAM::LINKING_FAILED " + std::string(infoLog));
        return LFALSE;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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
