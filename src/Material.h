#pragma once

#include "map"
#include "string"

#include "Application.h"
#include "MaterialProperty.h"
#include "ShaderProgram.h"

class ShaderProgram;

class Material
{
private:
    std::map<std::string, MaterialProperty> values;
    Material* AddProperty(std::string name, MaterialProperty prop);

public:
    ShaderProgram *currentShaderProgram;

    Material();
    Material* AddProperty(std::string name, int value);
    Material* AddProperty(std::string name, float value);
    Material* AddProperty(std::string name, vec3 value);

    Material* SetProperty(std::string name, int value);
    Material* SetProperty(std::string name, float value);
    Material* SetProperty(std::string name, vec3 value);
    
    Material* RemoveProperty(std::string name);
    std::map<std::string, MaterialProperty> GetPropertyMap() {return values;}
    void FindValues(ShaderProgram *sp);

    static Material *defaultMat;
};