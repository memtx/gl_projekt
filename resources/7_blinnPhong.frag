#version 330 core

uniform float ambientStrength = 0.2f;
uniform float specularStrength = 0.5f;
uniform int specularPower = 32;

uniform vec3 globalLightPos = vec3(0);
uniform vec3 cameraPos = vec3(0);

in vec3 vertexColor;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 FragColor;

void main()
{
    vec3 ambient = ambientStrength * vec3(1,1,1); //ambient light color

    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(globalLightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * vec3(1, 1, 1)*0.6; //diffuse light color

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 halfwayDir = normalize(lightDir+viewDir);
    float spec = pow(max(dot(viewDir, halfwayDir), 0.0), specularPower);
    vec3 specular = specularStrength * spec * vec3(1,1,1); //specular light color

    FragColor = vec4((ambient+diffuse+specular)*vec3(0,1,1), 1);
}