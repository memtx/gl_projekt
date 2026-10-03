#pragma once

#include "Application.h"

#include "stdarg.h"

class Shader;
class Transform;

class ShaderProgram
{
private:
    std::vector<Shader*> shaders = std::vector<Shader*>();
    GLint GetVarLocation(const char* name);
    void SetFloat(GLint location, float value);

    GLint posVecLoc;
    GLint rotVecLoc;
    GLint scaleVecLoc;
public:
    

    const GLuint id;
    ShaderProgram(int shaderCount, ...); //Create and link the shader program 
    void Use();
    void AddShader();
    void RemoveShader();
    void setTransform(Transform *t);
};