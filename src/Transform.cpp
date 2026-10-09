#include "Transform.h"
#include "ShaderProgram.h"

#define DEG2RADIAN 0.0174533f

Transform::Transform(vec3 t, vec3 r, vec3 s, mat4 m)
{
    /*
    this->rot = r;
    this->pos = t;
    this->scale = s;
    */
    this->rot = vec3(0);
    this->pos = vec3(0);
    this->scale = vec3(1);
    
    mat = mat4(1);

    this->Translate(t);
    this->Rotate(r);
    this->Scale(s);
    
    if(m != mat4(1))
        mat = m;

    children = std::vector<Transform*>();

}

void Transform::AddChild(Transform *child)
{
    children.push_back(child);
    child->parent = this;
}

void Transform::RemoveChild(Transform *child)
{
    for(auto i=children.begin(); i != children.end(); i++)
    {
        if(*i == child)
        {
            children.erase(i);
            child->parent = nullptr;
            return;
        }
    }
    Log.FatalError("DrawableObject child to be removed not found!");
}

void Transform::RecalculateMatrix(mat4 root)
{
    resultMat = root * mat;

    for(Transform* child : children)
        child->RecalculateMatrix(resultMat);
}

void Transform::ResetTransforms(vec3 t, vec3 r, vec3 s, mat4 m)
{
    this->rot = vec3(0);
    this->pos = vec3(0);
    this->scale = vec3(1);
    
    mat = mat4(1);

    this->Translate(t);
    this->Rotate(r);
    this->Scale(s);

    if(m != mat4(1))
        mat = m;
}

void Transform::ResetTransforms(Transform t)
{
    this->rot = vec3(0);
    this->pos = vec3(0);
    this->scale = vec3(1);
    
    mat = mat4(1);

    this->Translate(t.GetPos());
    this->Rotate(t.GetRot());
    this->Scale(t.GetScale());

    if(t.mat != mat4(1))
        mat = t.mat;
}

Transform& Transform::Rotate(vec3 r) //Ideálně rotovat po osách zvlášť. Pro transformace At -> S1 -> R1 -> T1 -> R2  zapíšeme matematicky jako An = R2 T1 R1 S1 At (nebo naopak ale transponované)
{
    this->rot += r;

    mat = glm::rotate(mat, r.x*DEG2RADIAN, glm::vec3(1.0f,0.0f,0.0f));
    mat = glm::rotate(mat, r.y*DEG2RADIAN, glm::vec3(0.0f,1.0f,0.0f));
    mat = glm::rotate(mat, r.z*DEG2RADIAN, glm::vec3(0.0f,0.0f,1.0f));
    return *this;
}

Transform& Transform::Scale(vec3 s)
{ 
    this->scale *= s; 
    mat = glm::scale(mat, s); 
    return *this;
}

Transform& Transform::Translate(vec3 t)
{ 
    this->pos += t; 
    mat = glm::translate(mat, t); 
    return *this;
}