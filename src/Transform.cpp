#include "Transform.h"

#define DEG2RADIAN 0.0174533f

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{

    //this->pos = pos;
    //this->rot = rot;
    //this->scale = scale;
    this->mat = glm::mat4(1.0f); // construct identity matrix

    //this->Scale(scale);
    this->Rotate(rot);
    //this->Translate(pos);
}

vec3 Transform::Rotate(vec3 r) //pro transformace At -> S1 -> R1 -> T1 -> R2  zapíšeme matematicky jako An = R2 T1 R1 S1 At (nebo naopak ale transponované)
{
    rot += r;

    mat = glm::rotate(mat, r.x*DEG2RADIAN, glm::vec3(1.0f,0.0f,0.0f));
    mat = glm::rotate(mat, r.y*DEG2RADIAN, glm::vec3(0.0f,1.0f,0.0f));
    mat = glm::rotate(mat, r.z*DEG2RADIAN, glm::vec3(0.0f,0.0f,1.0f));

    return rot;
}

vec3 Transform::Scale(vec3 s)
{
    scale *= s;
    mat = glm::scale(mat, s);
    return scale;
}

vec3 Transform::Translate(vec3 t)
{
    pos += t;
    mat = glm::translate(mat, t);
    return pos;
}