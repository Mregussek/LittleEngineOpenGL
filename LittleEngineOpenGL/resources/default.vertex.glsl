
#version 460 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

out vec3 vFragPosition;
out vec3 vNormal;

uniform mat4 uModel;
uniform mat4 uTransform;

void main() {
    vFragPosition = vec3(uModel * vec4(inPosition, 1.0));
    vNormal = mat3(transpose(inverse(uModel))) * inNormal;  

    gl_Position = uTransform * vec4(inPosition, 1.0);
}
