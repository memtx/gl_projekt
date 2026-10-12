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


void ShaderProgram::OnUpdateView(mat4 view)
{
    Log.Warn("onUpdateView");
}

void ShaderProgram::OnUpdateProjection(mat4 proj)
{
    Log.Warn("onUpdateProjection");
}

ShaderProgram::ShaderProgram(Camera *cam, int shaderCount, ...) 
 : id(glCreateProgram())
{
    this->camera = nullptr;
    UseCamera(cam);

    va_list args;
    va_start(args, shaderCount);
    for(int i=0; i<shaderCount; i++)
    {
        glAttachShader(id, va_arg(args, Shader*)->id);
	}
    va_end(args);
    glLinkProgram(id);
    
    modelMatLoc = GetVarLocation("modelMatrix");
    viewMatLoc = GetVarLocation("viewMatrix");
    projMatLoc = GetVarLocation("projectionMatrix");
}

void ShaderProgram::Use()
{ glUseProgram(id); }

void ShaderProgram::Disuse()
{ glUseProgram(0); }

bool ShaderProgram::HasTransform()
{ return this->modelMatLoc != -1; }

void ShaderProgram::UseCamera(Camera *c)
{
    if(this->camera == nullptr)
    {

        Event<int> test = Event<int>();
        //test.Subscribe(std::bind(&ShaderProgram::OnUpdateView,this, _1));
        
        c->projectionUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateView, this, _1));
        c->projectionUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateProjection, this, _1));
        //c->viewUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateView, this, _1));

        this->camera = c;
    }
    else
    {

        /*
        this->camera->projectionUpdate->Unsubscribe(this->OnUpdateProjection);
        this->camera->viewUpdate->Unsubscribe(this->OnUpdateView);

        c->projectionUpdate->Subscribe(this->OnUpdateProjection);
        c->viewUpdate->Subscribe(this->OnUpdateView);
        */
        this->camera = c;
    }
}


void ShaderProgram::SetMatrices(Transform *t)
{
    if(!HasTransform())
    {
        Log.FatalError("Transform not set!");
        return;
    }
    
    if(t->GetParent() == nullptr)
        t->RecalculateMatrix(); //děti se přepočítají několikrát, TODO!

    //this->Use();
    mat4 test = t->resultMat;
    glad_glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE,  glm::value_ptr((test)));

    //this->Disuse();
}
