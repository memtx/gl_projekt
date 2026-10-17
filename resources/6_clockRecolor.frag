#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{

    FragColor = vec4(vertexColor, 1);

    if(vertexColor == vec3(0))
        { FragColor = vec4(vec3(0.2), 1);}


    if( vertexColor == vec3(0,1,0) ||
        vertexColor == vec3(0,0,1))
        { FragColor = vec4(vec3(0),1); }


    if(vertexColor == vec3(1,1,0))
        { FragColor = vec4(vec3(5.0/255.0, 195.0/255.0, 222.0/255.0), 1); }
    
}