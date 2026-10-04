#pragma once

#include <stdarg.h>
#include <vector>

#include "Application.h"

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
    static void Disuse();
    void AddShader();
    void RemoveShader();
    bool HasAllTransforms();
    void setTransform(GLfloat posX = 0.0f, GLfloat posY = 0.0f, GLfloat posZ = 0.0f, GLfloat rotX = 0.0f, GLfloat rotY = 0.0f, GLfloat rotZ = 0.0f, GLfloat scaleX = 1.0f, GLfloat scaleY = 1.0f, GLfloat scaleZ = 1.0f);
    void setTransform(Transform *t);

};