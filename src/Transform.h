#pragma once

#include <glm/vec3.hpp> 
#include <glm/mat4x4.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec3 vec3;
typedef glm::mat4 mat4;

class Transform
{
private:
    vec3 pos; //only for tracking the current value 
    vec3 rot; //only for tracking the current value
    vec3 scale; //only for tracking the current value
    
public:
    mat4 mat; 

    vec3 GetPos(){ return pos; }
    vec3 GetRot(){ return rot; }
    vec3 GetScale(){ return scale; }

    bool IsEqualTo(Transform t)
    {
        return this->pos == t.pos && this->rot == t.rot && this->scale == t.scale;
    }

    Transform(glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f));

    
    vec3 Rotate(vec3 r);
    vec3 Scale(vec3 s);
    vec3 Translate(vec3 t);

};