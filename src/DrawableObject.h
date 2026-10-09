#pragma once

#include "Model.h"
#include "Transform.h"
#include "ShaderProgram.h"

class ShaderProgram;
class Model;
class Transform;

class DrawableObject
{
private:
    bool nonHeapTransformShouldDelete = false;
    static Model* activeModel;
    static ShaderProgram* activeShaderProgram;

    std::vector<DrawableObject*> children;
public:
    ShaderProgram *shaderProgram;  
    Model *model;
    Transform *transform;

    DrawableObject(Model *model, ShaderProgram *shaderProgram, DynamicTransform dynTransform, std::vector<DrawableObject*> children = std::vector<DrawableObject*>());
    DrawableObject(Model *model, ShaderProgram *shaderProgram, DynamicTransform* dynTransform, std::vector<DrawableObject*> children = std::vector<DrawableObject*>());
    DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform *transform = nullptr, std::vector<DrawableObject*> children = std::vector<DrawableObject*>());
    DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform transform = Transform(), std::vector<DrawableObject*> children = std::vector<DrawableObject*>());

    void AddChild(DrawableObject *child);
    void RemoveChild(DrawableObject *child);
    int GetChildrenCount() { return children.size(); };

    ~DrawableObject();
    void Draw();
};