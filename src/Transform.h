#pragma once
#include "Application.h"

class Transform
{
private:

public:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
     

    Transform(glm::vec3 pos = glm::vec3(0,0,0), glm::vec3 rot = glm::vec3(0,0,0), glm::vec3 scale = glm::vec3(1,1,1));
};