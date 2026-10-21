#include "Material.h"

Material::Material()
{
    this->values = std::map<std::string, MaterialProperty>();
    currentShaderProgram = nullptr;
}


void Material::AddProperty(std::string name, MaterialProperty prop)
{
    values.insert_or_assign(name, prop );
};

//=========

void Material::AddProperty(std::string name, int val)
{ AddProperty(name, MaterialProperty(MatDatTypes::INT_PROP, (MaterialProperty::Data)val)); }

void Material::AddProperty(std::string name, float val)
{ AddProperty(name, MaterialProperty(MatDatTypes::FLOAT_PROP, (MaterialProperty::Data)val)); }

void Material::AddProperty(std::string name, vec3 val)
{ 
    MaterialProperty::Data dt = MaterialProperty::Data(); 
    dt.vec3_data = val;

    AddProperty(name, MaterialProperty(MatDatTypes::VEC3_PROP, dt)); 
}


void Material::RemoveProperty(std::string name)
{
    values.erase(name);
};

void Material::FindValues(ShaderProgram *sp)
{
    std::vector<std::string> keys = std::vector<std::string>();
    for(auto val : values)
        keys.push_back(val.first);

    for(auto key : keys)
    {
        MaterialProperty prop = sp->GetMaterialProperty(key, values[key].data_type);
        values[key] = prop;
    }
};

void Material::ApplyValues(ShaderProgram *sp)
{
    if(sp == nullptr)
    { logger.FatalError("Shader passed to material is null!"); }

    if(sp != currentShaderProgram)
    {
        sp = currentShaderProgram;
        FindValues(currentShaderProgram);
    }

    for(auto val : values)
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
                glad_glUniform1i(prop.loc, prop.sharedData.int_data);
                break;

            case MatDatTypes::FLOAT_PROP:
                glad_glUniform1f(prop.loc, prop.sharedData.float_data);
                break;
            case MatDatTypes::VEC3_PROP:
            {
                vec3 val = prop.sharedData.vec3_data;
                glad_glUniform3fv(prop.loc, 1, glm::value_ptr(val));
                break;
            }
            default:
            {
                logger.FatalError("MaterialProperty has invalid data type");
            }
        }
        
    }
}