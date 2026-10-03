#include "ShaderProgram.h"


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
}

void ShaderProgram::Use()
{
    glUseProgram(id);
}

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