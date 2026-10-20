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


void ShaderProgram::OnUpdateView(Camera *cam)
{
    cameraView = cam->getView();
    this->Use();
    if(this->viewMatLoc != -1)
    {
        glad_glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE,  glm::value_ptr((cameraView)));
        logger.countUniforms++;
    }

    if(this->cameraPosLoc != -1)
    {
        vec3 cpos = cam->GetPos();
        glad_glUniform3fv(cameraPosLoc, 1, glm::value_ptr(cpos));
    
        logger.Warn("camPos");
    }
    

}

void ShaderProgram::OnUpdateProjection(Camera *cam)
{
    cameraProj = cam->getProjection();
    this->Use();
    if(this->projMatLoc != -1)
    {

        glad_glUniformMatrix4fv(projMatLoc, 1, GL_FALSE,  glm::value_ptr((cameraProj)));
        logger.countUniforms++;
    }
    
    logger.Warn("proj");

}

ShaderProgram::ShaderProgram(Camera *cam, int shaderCount, ...) 
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
    
    modelMatLoc = GetVarLocation("modelMatrix");
    viewMatLoc = GetVarLocation("viewMatrix");
    projMatLoc = GetVarLocation("projectionMatrix");    
    unixSecsLoc = GetVarLocation("unixSecs");    

    globalLightPosLoc = GetVarLocation("globalLightPos");
    ambientStrengthLoc = GetVarLocation("ambientStrength");
    cameraPosLoc = GetVarLocation("cameraPos");


    this->camera = nullptr;
    UseCamera(cam);
}

void ShaderProgram::Use()
{ glUseProgram(id); }

void ShaderProgram::Disuse()
{ glUseProgram(0); }

bool ShaderProgram::HasTransform()
{ return this->modelMatLoc != -1; }

void ShaderProgram::UseCamera(Camera *c)
{
    logger.Warn("Camera used");
    if(this->camera == nullptr)
    {
        c->viewUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateView, this, _1));
        c->projectionUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateProjection, this, _1));
        //c->viewUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateView, this, _1));

        this->camera = c;
    }
    else
    {
        this->camera->viewUpdate->Unsubscribe(std::bind(&ShaderProgram::OnUpdateView, this, _1));
        this->camera->projectionUpdate->Unsubscribe(std::bind(&ShaderProgram::OnUpdateProjection, this, _1));

        c->viewUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateView, this, _1));
        c->projectionUpdate->Subscribe(std::bind(&ShaderProgram::OnUpdateProjection, this, _1));
        
        this->camera = c;
    }

    OnUpdateProjection(this->camera);
    OnUpdateView(this->camera);

}

void ShaderProgram::SetMatrices(Transform *t)
{
    if(!HasTransform())
    {
        logger.FatalError("Transform not set!");
        return;
    }
    
    if(t->GetParent() == nullptr)
        t->RecalculateMatrix();

    //OnUpdateProjection(cameraProj);
    //OnUpdateView(cameraView);

    mat4 test = t->resultMat;
    glad_glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE,  glm::value_ptr((test)));
    logger.countUniforms++;

    if(this->unixSecsLoc != -1)
    { 
        static int t;
        t = time(NULL) % (3600*24);  
        glad_glUniform1i(unixSecsLoc, t);
        logger.countUniforms++;
    }

    //this->Disuse();
}

void ShaderProgram::SetAmbientStrength(float ambStrength)
{
    if(ambientStrengthLoc != -1)
    {
        glad_glUniform1f(ambientStrengthLoc, ambStrength);
        logger.countUniforms++;
    }
    else
        logger.FatalError("Tried to set ambient strength in shader without it.");
}

void ShaderProgram::SetGlobalLightPos(vec3 globalLightPos)
{
    if(globalLightPosLoc != -1)
    {
        vec3 lp = globalLightPos;
        glad_glUniform3fv(globalLightPosLoc, 1, glm::value_ptr(lp));
    }

}