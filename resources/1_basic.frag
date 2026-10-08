#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
    FragColor = 
    //vec4(1,1,1,1); 
    vec4(vertexColor, 1.0);
}