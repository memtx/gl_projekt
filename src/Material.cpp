#include "Material.h"

Material::Material()
{
    this->values = std::map<std::string, MaterialProperty>();
    currentShaderProgram = nullptr;
}

Material *Material::defaultMat = new Material();

Material* Material::AddProperty(std::string name, MaterialProperty prop)
{
    values.insert_or_assign(name, prop );
    return this;
};

//=========

Material* Material::AddProperty(std::string name, int val)
{ 
    MaterialProperty::Data dt = MaterialProperty::Data();
    dt.int_data = val; 
    AddProperty(name, MaterialProperty(MatDatTypes::INT_PROP, dt)); 
    return this;
}

Material* Material::AddProperty(std::string name, float val)
{
    MaterialProperty::Data dt = MaterialProperty::Data();
    dt.float_data = val; 
    AddProperty(name, MaterialProperty(MatDatTypes::FLOAT_PROP, dt)); 
    return this;
}

Material* Material::AddProperty(std::string name, vec3 val)
{ 
    MaterialProperty::Data dt = MaterialProperty::Data(); 
    dt.vec3_data = val;

    AddProperty(name, MaterialProperty(MatDatTypes::VEC3_PROP, dt)); 
    return this;
}


Material* Material::RemoveProperty(std::string name)
{
    values.erase(name);
    return this;
};

void Material::FindValues(ShaderProgram *sp)
{
    std::vector<std::string> keys = std::vector<std::string>();
    for(auto val : values)
        keys.push_back(val.first);

    for(auto key : keys)
    {
        MaterialProperty oldProp = values[key];
        MaterialProperty prop = sp->GetMaterialProperty(key, oldProp.data_type);
        prop.sharedData = oldProp.sharedData;
        values[key] = prop;
    }
};
