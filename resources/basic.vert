#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

void main()
{
    /*vec3 newColour = color;
    newColour[0] = newColour[0] + 0.4;
    newColour[1] = newColour[1] - 0.4;
    newColour[2] = newColour[2] - 0.4;
    vertexColor = newColour;
    */
    vertexColor = color;
    
    //vec3 newPos = position;
    //newPos[1] = newPos[1] - 0.7;
    //gl_Position = vec4(newPos * 0.25, 1);
    gl_Position = vec4(position, 1.0f);
}