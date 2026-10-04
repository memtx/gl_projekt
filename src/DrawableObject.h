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

public:
    ShaderProgram *shaderProgram;  
    Model *model;
    Transform *transform;
    
    DrawableObject(Model *model = nullptr, ShaderProgram *shaderProgram = nullptr, Transform *transform = nullptr);
    DrawableObject(Model *model = nullptr, ShaderProgram *shaderProgram = nullptr, Transform transform = Transform());
    ~DrawableObject();
    void Draw();
};
