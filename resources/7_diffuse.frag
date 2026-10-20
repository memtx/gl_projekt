#version 330 core

uniform float ambientStrength = 0.5f;
uniform vec3 globalLightPos = vec3(0);

in vec3 vertexColor;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 FragColor;

void main()
{
    vec3 ambientColor = ambientStrength * vec3(1,1,1); //ambient light color

    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(globalLightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * vec3(1, 1, 1); //diffuse light color

    FragColor = vec4((ambientColor+diffuse)*vertexColor, 1);    
}