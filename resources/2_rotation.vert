#version 330 core

uniform float alfa = 0;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;



void main()
{
    vec3 newPos = vec3(0);

    newPos[0] = cos(alfa)*position[0] + sin(alfa)*position[2];
    newPos[1] = position[1];
    newPos[2] = -sin(alfa)*position[0] + cos(alfa)*position[2];

    gl_Position = vec4(newPos*0.3, 1);

    vertexColor = color;
}