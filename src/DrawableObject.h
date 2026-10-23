#pragma once

#include "Model.h"
#include "Transform.h"
#include "ShaderProgram.h"
#include "Material.h"

class ShaderProgram;
class Model;
class Transform;
class Material;

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
    Material *material;

    DrawableObject(Model *model, ShaderProgram *shaderProgram, DynamicTransform dynTransform, Material *material = nullptr, std::vector<DrawableObject*> children = std::vector<DrawableObject*>());
    DrawableObject(Model *model, ShaderProgram *shaderProgram, DynamicTransform* dynTransform, Material *material = nullptr, std::vector<DrawableObject*> children = std::vector<DrawableObject*>());
    DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform *transform = nullptr, Material *material = nullptr, std::vector<DrawableObject*> children = std::vector<DrawableObject*>());
    DrawableObject(Model *model, ShaderProgram *shaderProgram, Transform transform = Transform(), Material *material = nullptr, std::vector<DrawableObject*> children = std::vector<DrawableObject*>());

    void AddChild(DrawableObject *child);
    void RemoveChild(DrawableObject *child);
    int GetChildrenCount() { return children.size(); };

    static void ClearActiveShader();

    ~DrawableObject();
    void Draw();
};