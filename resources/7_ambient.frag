#version 330 core

uniform float ambientStrength = 0.5f;
uniform vec3 objectColor = vec3(-1);

in vec3 vertexColor;

out vec4 FragColor;

void main()
{

    vec3 ambient = ambientStrength * vec3(1,1,1); //light color
    
    if(objectColor == vec3(-1))
        FragColor = vec4(ambient*vec3(0.5,0,0.5), 1);
    else if(objectColor == vec3(-2))
        FragColor = vec4(ambient*vertexColor, 1);    
    else
        FragColor = vec4(ambient*objectColor, 1);

}