#include "ShaderProgram.h"


GLint ShaderProgram::GetVarLocation(const char* name)
{
    glUseProgram(id);
	GLuint location = glGetUniformLocation(id, name);
	glUseProgram(0);
    return location;
}

void ShaderProgram::SetFloat(GLint location, float value)
{
    glUseProgram(id);
	glUniform1f(location, value);
	glUseProgram(0);
}

ShaderProgram::ShaderProgram(int shaderCount, ...) 
 : id(glCreateProgram())
{
    va_list args;
    va_start(args, shaderCount);
    for(int i=0; i<shaderCount; i++)
    {
        glAttachShader(id, va_arg(args, Shader*)->id);
	}
    glLinkProgram(id);
    
    rotVecLoc = GetVarLocation("rotVec");
    posVecLoc = GetVarLocation("posVec");
    scaleVecLoc = GetVarLocation("scaleVec");
}

void ShaderProgram::Use()
{ glUseProgram(id); }

void ShaderProgram::Disuse()
{ glUseProgram(0); }

bool ShaderProgram::HasAllTransforms()
{ return this->posVecLoc != -1 && this->rotVecLoc != -1 && this-> scaleVecLoc != -1; }

void ShaderProgram::setTransform(GLfloat pX, GLfloat pY, GLfloat pZ, GLfloat rX, GLfloat rY, GLfloat rZ, GLfloat sX, GLfloat sY, GLfloat sZ)
{
    if(!HasAllTransforms())
        return;

    this->Use();
    glUniform3f(rotVecLoc, rX, rY, rZ);
    glUniform3f(posVecLoc, pX, pY, pZ);
    glUniform3f(scaleVecLoc, sX, sY, sZ);
    this->Disuse();
}

void ShaderProgram::setTransform(Transform *t)
{
    if(!HasAllTransforms())
        return;

    this->Use();
    glUniform3fv(rotVecLoc, 1, &(t->rot[0]));
    glUniform3fv(posVecLoc, 1, &(t->pos[0]));
    glUniform3fv(scaleVecLoc, 1, &(t->scale[0]));
    this->Disuse();
}