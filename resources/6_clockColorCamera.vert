#version 330 core

#define DEG2RADIAN 0.0174533f

uniform mat4 modelMatrix = mat4(1.0f);
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);
uniform int unixSecs = 12345;


layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 vertexColor;
out vec3 fragNormal;
out vec3 fragPos;

mat4 rotationZ(float angle) {
  float s = sin(angle);
  float c = cos(angle);

  return mat4(
    c, s, 0.0, 0.0, 
    -s, c, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0,0.0,0.0, 1.0
  );
}

mat4 rotationX(float angle) {
  float s = sin(angle);
  float c = cos(angle);

  return mat4(
    1.0, 0.0, 0.0, 0.0, 
    0.0, c, -s, 0.0,
    0.0, s, c, 0.0,
    0.0,0.0,0.0, 1.0
  );
}

mat4 rotationY(float angle)
{
  float s = sin(angle);
  float c = cos(angle);

    return mat4(
        c,0,s,0,
        0,1,0,0,
        -s,0,c,0,
        0,0,0,1
    );
}

void main()
{
  
    int secs = -unixSecs;
    int mins = -(unixSecs / 60);
    int hrs = -(unixSecs / (3600));

    vec4 timedPos = vec4(1);

    timedPos = vec4(position,1);
    if(color == vec3(1,0,0))
        timedPos = rotationZ(secs*DEG2RADIAN*360/60) * vec4(position,1);
    
    if(color == vec3(0,1,0))
        timedPos = rotationZ(mins*DEG2RADIAN*360/60) * vec4(position, 1);
    
    if(color == vec3(0,0,1))
        timedPos = rotationZ(hrs*DEG2RADIAN*360/12) * vec4(position,1);
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * timedPos;// vec4(position, 1);

    vertexColor = color;
    
    if(color == vec3(0))
    { vertexColor = vec3(0.2);}

    if( color == vec3(0,1,0) ||
        color == vec3(0,0,1))
    { vertexColor = vec3(0); }

    if( color == vec3(1,1,0))
    { vertexColor = vec3(5.0/255.0, 195.0/255.0, 222.0/255.0); }


  //can also pass normals as color (may use abs() for color on all sides)

    fragPos = vec3((modelMatrix*timedPos));


    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    fragNormal = normalize(normalMatrix * normal);
} 