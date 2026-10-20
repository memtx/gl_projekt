#version 330 core

uniform float ambientStrength = 0.5f;

in vec3 vertexColor;

out vec4 FragColor;

void main()
{

    vec3 ambientColor = ambientStrength * vec3(1,1,1); //light color
    FragColor = vec4(ambientColor * vertexColor, 1);    
}