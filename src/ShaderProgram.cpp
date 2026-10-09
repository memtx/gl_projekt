#include "ShaderProgram.h"


GLint ShaderProgram::GetVarLocation(const char* name)
{
    glUseProgram(id);
	GLuint location = glGetUniformLocation(id, name);
	//glUseProgram(0);
    return location;
}

void ShaderProgram::SetFloat(GLint location, float value)
{
    glUseProgram(id);
	glUniform1f(location, value);
	//glUseProgram(0);
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
    va_end(args);
    glLinkProgram(id);
    
    trMatLoc = GetVarLocation("trMat");
}

void ShaderProgram::Use()
{ glUseProgram(id); }

void ShaderProgram::Disuse()
{ glUseProgram(0); }

bool ShaderProgram::HasTransform()
{ return this->trMatLoc != -1; }

void ShaderProgram::setTransform(Transform *t)
{
    if(!HasTransform())
    {
        Log.FatalError("Transform not set!");
        return;
    }
    
    if(t->GetParent() == nullptr)
        t->RecalculateMatrix(); //děti se přepočítají několikrát, TODO!

    //this->Use();
    glad_glUniformMatrix4fv(trMatLoc, 1, GL_FALSE,  glm::value_ptr((t->resultMat)));

    //this->Disuse();
}