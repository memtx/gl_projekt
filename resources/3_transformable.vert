#version 330 core

uniform vec3 posVec = vec3(0.0f, 0.0f, 0.0f);
uniform vec3 rotVec = vec3(0.0f, 0.0f, 0.0f);
uniform vec3 scaleVec = vec3(1.0f, 1.0f, 1.0f);

/*
uniform float[3] posVec = {0,0,0};
uniform float[3] rotVec = {0,0,0};
uniform float[3] scaleVec = {1,1,1};
*/

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;

void main()
{
    vec3 newPos = vec3(0);

    //1-axis rotation
    newPos[0] = cos(rotVec[0])*position[0] + sin(rotVec[0])*position[2];
    newPos[1] = position[1];
    newPos[2] = -sin(rotVec[0])*position[0] + cos(rotVec[0])*position[2];

    //scale
    newPos *= scaleVec;

    //translation
    newPos += posVec;

    gl_Position = vec4(newPos, 1);
    vertexColor = color; //pass normals as color (may use abs() for color on all sides)
}