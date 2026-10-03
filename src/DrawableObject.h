#pragma once

#include "Application.h"
#include "ShaderProgram.h"
#include "Transform.h"

class DrawableObject
{
private:


public:
    ShaderProgram *shaderProgram = nullptr;  
    Transform transform();
    
    DrawableObject();
    

    

};
