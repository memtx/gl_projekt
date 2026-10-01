#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

void main()
{
    vec3 newColor = vec3(0);
    newColor[0] = color[0] + color[1];
    newColor[1] = color[1] + color[2]; 
    newColor[2] = color[2] + color[0];
    newColor *= 0.5;

    vertexColor = newColor;

    vec3 newPos = position;
    newPos[1] = newPos[1] - 1.5;
    gl_Position = vec4(newPos * 0.3, 1);
}
