#pragma once

#include "Application.h"

class ShaderProgram;
class Model;
class Transform;

class DrawableObject
{
private:


public:
    ShaderProgram *shaderProgram = nullptr;  
    Model *model = nullptr;
    Transform *transform = nullptr;
    
    DrawableObject(Model *model = nullptr, ShaderProgram *shaderProgram = nullptr, Transform *transform = nullptr);

    void Draw();
};
