#pragma once

#include "Application.h"

#include "stdarg.h"

class Shader;

class ShaderProgram
{
private:
    std::vector<Shader*> shaders = std::vector<Shader*>();

public:
    const GLuint id;
    ShaderProgram(int shaderCount, ...); //Create and link the shader program 
    void Use();
    void AddShader();
    void RemoveShader();
    GLint GetVarLocation(const char* name);
    void SetFloat(GLint location, float value);
};