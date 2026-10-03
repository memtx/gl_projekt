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