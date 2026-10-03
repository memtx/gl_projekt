#pragma once
#include "Application.h"

enum ModelDataLayout
{
    L_3COORD3NORMAL
};

class Model
{
private:
     

     GLuint VBO; //vertex buffer object, vpodstatě pointer/index na paměť ke které nemáme přístup
     GLuint VAO; //vertex array object, na parsování dat v bufferu
public:
    const ModelDataLayout modelLayout;
    const size_t dataSize;
    const std::string path;

    Model(const float *data, int sizeOfData, ModelDataLayout modelDataType = ModelDataLayout::L_3COORD3NORMAL);
    void bindVAO();
    static void unbindVAO();
};