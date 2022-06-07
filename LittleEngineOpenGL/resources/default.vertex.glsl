
#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 uTransform;

void main() {
   gl_Position = uTransform * vec4(aPos, 1.0);
}
