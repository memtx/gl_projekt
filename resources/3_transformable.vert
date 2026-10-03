#version 330 core

uniform float rotAngle = 0;
uniform float transAmount = 0;
uniform float scaleAmount = 1;


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 vertexColor;


void main()
{
    vec3 newPos = vec3(0);

    //1-axis rotation
    newPos[0] = cos(rotAngle)*position[0] + sin(rotAngle)*position[2];
    newPos[1] = position[1];
    newPos[2] = -sin(rotAngle)*position[0] + cos(rotAngle)*position[2];

    //1-axis translation
    newPos[0] += transAmount;

    //1-axis scale
    newPos *= scaleAmount;

    gl_Position = vec4(newPos, 1);
    vertexColor = color; //pass normals as color (may use abs() for color on all sides)
}