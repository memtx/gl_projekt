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

    std::vector<Transform*> children;
    Transform* parent = nullptr;
    mat4 mat; //holding current object's transforms
public:
    mat4 resultMat; //holding the transforms after processing with root

    const vec3 GetPos(){ return pos; }
    const vec3 GetRot(){ return rot; }
    const vec3 GetScale(){ return scale; }
    //void SetPos(vec3 p) { pos=p; }; //currently don't know how, and don't have enough time to dilly-dally with QOL features
    //void SetRot(vec3 r) { rot=r; };
    //void SetScale(vec3 s){scale=s;};
    void ResetTransforms(vec3 pos = vec3(0.0f,0.0f,0.0f), vec3 rot = vec3(0.0f,0.0f,0.0f), vec3 scale = vec3(1.0f,1.0f,1.0f), mat4 mat = mat4(1));
    void ResetTransforms(Transform t);
    Transform& Rotate(vec3 r);
    Transform& Scale(vec3 s);
    Transform& Translate(vec3 t);

    void AddChild(Transform* child);
    void RemoveChild(Transform* child);
    int GetChildrenCount() { return children.size(); }
    Transform* GetParent() { return parent; }

    bool IsEqualTo(Transform t)
    {
        return this->pos == t.pos && this->rot == t.rot && this->scale == t.scale;
    }

    Transform(glm::vec3 pos = vec3(0.0f,0.0f,0.0f), vec3 rot = vec3(0.0f,0.0f,0.0f), vec3 scale = vec3(1.0f,1.0f,1.0f), mat4 mat = mat4(1));

    void RecalculateMatrix(mat4 root = mat4(1.0f));
};