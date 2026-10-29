#version 330 core

uniform float ambientStrength = 0.2f;
uniform float specularStrength = 0.5f;
uniform int specularPower = 32;
uniform vec3 objectColor = vec3(-1);
uniform vec3 attenuationFactors = vec3(1.0, 0.09, 0.032);

uniform vec3 globalLightPos = vec3(0);
uniform vec3 cameraPos = vec3(0);

in vec3 vertexColor;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 FragColor;

float attenuation(float d, float c, float l, float q)
{
    // d = distance from the light to the fragment
    // c = constant attenuation factor
    // l = linear attenuation factor
    // q = quadratic attenuation factor
    float att=1.0/ (c + l*d + q*d*d);
    return clamp(att , 0.0 , 1.0);
}



void main()
{
    vec3 ambient = ambientStrength * vec3(1,1,1); //ambient light color

    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(globalLightPos - fragPos);
    
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * vec3(1, 1, 1)*0.6; //diffuse light color

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 halfwayDir = normalize(lightDir+viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), specularPower);
    vec3 specular = specularStrength * spec * vec3(1,1,1); //specular light color

    vec3 I = normalize(fragPos - cameraPos);
    float refl = dot(reflect(I, norm), lightDir);

    float att = attenuation(distance(globalLightPos,fragPos), attenuationFactors.x, attenuationFactors.y, attenuationFactors.z);

    if(objectColor == vec3(-1))
        FragColor = vec4((ambient+diffuse+specular)*vec3(0.5,0.5,0.5)*att, 1);
    else if(objectColor == vec3(-2))
        FragColor = vec4((ambient+diffuse+specular)*vertexColor*att, 1);    
    else
        FragColor = vec4((ambient+diffuse+specular)*objectColor*att, 1);

}