
#version 460 core

out vec4 FragColor;

in vec3 vFragPosition;  
in vec3 vNormal;  

uniform vec4 uColor;

void main() {
   FragColor = uColor;
}
