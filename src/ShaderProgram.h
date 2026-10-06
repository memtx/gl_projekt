#pragma once

#include <stdarg.h>
#include <vector>

#include "Shader.h"
#include "Transform.h"

class Shader;
class Transform;

class ShaderProgram
{
private:
    std::vector<Shader*> shaders = std::vector<Shader*>();
    GLint GetVarLocation(const char* name);
    void SetFloat(GLint location, float value);

    GLint trMatLoc;
    GLuint id;
public:
    ShaderProgram(int shaderCount, ...); //Create and link the shader program 
    void Use();
    static void Disuse();
    void AddShader();
    void RemoveShader();
    bool HasTransform();
    void setTransform(Transform *t);

};