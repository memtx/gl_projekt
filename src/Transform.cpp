#include "Transform.h"

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
    this->pos = pos;
    this->rot = rot;
    this->scale = scale;
}