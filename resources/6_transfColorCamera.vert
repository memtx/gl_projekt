#version 330 core

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
out vec3 vertexColor;
 
void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1);
    
    vertexColor = color; //pass normals as color (may use abs() for color on all sides)
}