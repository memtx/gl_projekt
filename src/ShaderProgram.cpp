#include "ShaderProgram.h"

ShaderProgram *ShaderProgram::lastUsedShaderProgram = nullptr;

GLint ShaderProgram::GetVarLocation(const char* name)
{
	GLuint location = glGetUniformLocation(id, name);
    return location;
}

void ShaderProgram::SetFloat(GLint location, float value)
{
    this->Use();
	glUniform1f(location, value);
	//glUseProgram(0);
    logger.countOptionalUniforms++;
}

float ShaderProgram::GetFloat(GLint location)
{
    float result;
	glGetUniformfv(id, location, &result);
    return result;
}


void ShaderProgram::SetInt(GLint location, int value)
{
    this->Use();
	glUniform1i(location, value);
	//glUseProgram(0);
    logger.countOptionalUniforms++;
}

int ShaderProgram::GetInt(GLint location)
{
    int result;
	glad_glGetUniformiv(id, location, &result);
    return result;
}


void ShaderProgram::SetVec3(GLint location, vec3 value)
{
    vec3 val = value;
    this->Use();
	glUniform3fv(location,1, glm::value_ptr(val));
	//glUseProgram(0);
    logger.countOptionalUniforms++;
}

vec3 ShaderProgram::GetVec3(GLint location)
{
    float result[3];
	glad_glGetnUniformfv(id, location, sizeof(result), result);
    return vec3(result[0], result[1], result[2]);
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
        logger.countUniforms++;
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
    cameraPosLoc = GetVarLocation("cameraPos");


    this->camera = nullptr;
    UseCamera(cam);
}

void ShaderProgram::Use()
{
    if(ShaderProgram::lastUsedShaderProgram != this)
    {
        ShaderProgram::lastUsedShaderProgram = this;
        glUseProgram(this->id); 
        logger.countShaderUses++; 
    }
}

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

void ShaderProgram::SetTransform(Transform *t)
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

    //this->Disuse();
}

void ShaderProgram::SetUnixTime(int t)
{
    if(this->unixSecsLoc != -1)
    { 
        static int t;
        t = t % (3600*24);  
        glad_glUniform1i(unixSecsLoc, t);
        logger.countUniforms++;
    }

}

MaterialProperty ShaderProgram::GetMaterialProperty(std::string name, MatDatTypes matType)
{
    GLint loc = GetVarLocation(name.c_str());
    MaterialProperty::Data dat = (MaterialProperty::Data)0;
    switch(matType)
    {
        case MatDatTypes::FLOAT_PROP:
            dat.float_data = this->GetFloat(loc);
            break;

        case MatDatTypes::INT_PROP:
            dat.int_data = this->GetInt(loc);
            break;

        case MatDatTypes::VEC3_PROP:
            dat.vec3_data = this->GetVec3(loc);
            break;
        
        default:
            logger.FatalError("invalid material data type in shader program");
    }

    return MaterialProperty(matType, dat, loc);
}

void ShaderProgram::ApplyMaterial(Material *mat)
{
    if(this->lastUsedMaterial != mat && mat != nullptr)
    {
        this->lastUsedMaterial = mat;
        
        if(this != mat->currentShaderProgram)
        {
            mat->currentShaderProgram = this;
            this->Use();
            mat->FindValues(this);
        }

        for(auto val : mat->GetPropertyMap())
        {
            //TODO: check if shaderProgram has values, 

            MaterialProperty prop = val.second;
            if(prop.loc < 0)
            {
                if(prop.loc == -1)
                    logger.Warn("Property not found (-1)");
                if(prop.loc == -2)
                    logger.FatalError("Property never set (-2)");

                continue;
            }

            switch(prop.data_type)
            {
                case MatDatTypes::INT_PROP:
                    SetInt(prop.loc, prop.sharedData.int_data);
                    break;

                case MatDatTypes::FLOAT_PROP:
                    SetFloat(prop.loc, prop.sharedData.float_data);
                    break;

                case MatDatTypes::VEC3_PROP:
                    SetVec3(prop.loc, prop.sharedData.vec3_data);
                    break;
                
                default:
                    logger.FatalError("MaterialProperty has invalid data type");
                    break;
        
            }
            
        }
    }
}

void ShaderProgram::SetGlobalLightPos(vec3 globalLightPos)
{
    if(globalLightPosLoc != -1)
    {
        this->Use();
        //vec3 lp = globalLightPos;
        SetVec3(globalLightPosLoc, globalLightPos);
        //glad_glUniform3fv(globalLightPosLoc, 1, glm::value_ptr(lp));
    }

}