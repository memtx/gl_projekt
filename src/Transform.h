#pragma once
#include "Application.h"

class Transform
{
private:

public:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
     

    Transform(glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f));
};