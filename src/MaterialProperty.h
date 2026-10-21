#pragma once

#include "Material.h"

enum MatDatTypes : unsigned int 
{ INVALID_PROP, INT_PROP, FLOAT_PROP, VEC3_PROP };

struct MaterialProperty //https://stackoverflow.com/questions/3559412/how-to-store-different-data-types-in-one-list-c
{
    union Data{
        int int_data;
        float float_data;
        vec3 vec3_data;
    } sharedData;
    MatDatTypes data_type;
    GLint loc;

    MaterialProperty(MatDatTypes type, Data data, GLint loc = -2);
    MaterialProperty();
};