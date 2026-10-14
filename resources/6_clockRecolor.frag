#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    if(vertexColor == vec3(0,0,0))
        FragColor = vec4(0.1,0.1,0.1,1);
    else
        FragColor = vec4(vertexColor, 1);
}