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
    void AddProperty(std::string name, MaterialProperty prop);
    ShaderProgram *currentShaderProgram;
    void FindValues(ShaderProgram *sp);

public:
    Material();
    void AddProperty(std::string name, int value);
    void AddProperty(std::string name, float value);
    void AddProperty(std::string name, vec3 value);

    void SetProperty(std::string name, int value);
    void SetProperty(std::string name, float value);
    void SetProperty(std::string name, vec3 value);
    
    void RemoveProperty(std::string name);
    void ApplyValues(ShaderProgram *sp);
};