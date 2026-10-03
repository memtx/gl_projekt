#pragma once

#include "Application.h"
#include "Shader.h"

#include "stdarg.h"


class ShaderProgram
{
private:

public:
    const GLuint id;
    ShaderProgram(int shaderCount, ...); //Create and link the shader program 
};