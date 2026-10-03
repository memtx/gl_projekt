#pragma once

#include "Application.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Model.h"

class DrawableObject
{
private:


public:
    ShaderProgram *shaderProgram = nullptr;  
    Model *model = nullptr;
    Transform transform = Transform();
    
    DrawableObject(Model *model = nullptr, ShaderProgram *shaderProgram = nullptr, Transform transform = Transform());

    void Draw();
};
