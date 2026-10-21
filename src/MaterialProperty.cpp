#include "MaterialProperty.h"

MaterialProperty::MaterialProperty(MatDatTypes type, Data data, GLint loc)
{
    this->sharedData = data;
    this->data_type = type;
    this->loc = loc;
}

MaterialProperty::MaterialProperty()
{
    this->sharedData = (MaterialProperty::Data)0;
    this->data_type = MatDatTypes::INVALID_PROP;
    this->loc = -2;
}