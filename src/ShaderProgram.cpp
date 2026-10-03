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
{
    glUseProgram(id); 
}

void ShaderProgram::setTransform(Transform *t)
{
    glUseProgram(id);
    glm::vec3 asd = t->pos;

    //glUniform3fv(rotVecLoc, 1, &(t->rot[0]));
    glUniform3f(rotVecLoc, t->rot.x, t->rot.y, t->rot.z);
    glUniform3f(posVecLoc, t->pos.x, t->pos.y, t->pos.z);
    glUniform3f(scaleVecLoc, t->scale.x, t->scale.y, t->scale.z);
    glUseProgram(0);
}