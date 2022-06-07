
#version 460 core

out vec4 outFragColor;

in vec3 vFragPosition;  
in vec3 vNormal;  

uniform vec4 uMeshColor;
uniform vec3 uLightColor;
uniform vec3 uLightPosition;
uniform vec3 uCameraPosition;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * uLightColor;
  	
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(uLightPosition - vFragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * uLightColor;
    
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uCameraPosition - vFragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * uLightColor;  
        
    vec3 result = (ambient + diffuse + specular) * vec3(uMeshColor);
    outFragColor = vec4(result, 1.0);
}
