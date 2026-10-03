#pragma once
#include "Application.h"

class Shader
{
private:


public:
    const int GL_TYPEOF_SHADER; 
    const GLuint ref;

    Shader(GLenum GL_TYPEOF_SHADER, const char* path);
};