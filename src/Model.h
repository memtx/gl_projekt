#pragma once

#include <string>

#include "Application.h"

enum ModelDataLayout
{
    L_3COORD3NORMAL,
    L_3COORD3NORMAL3VERTCOLOR
};

class Model
{
private:
     

     GLuint VBO; //vertex buffer object, vpodstatě pointer/index na paměť ke které nemáme přístup
     GLuint VAO; //vertex array object, na parsování dat v bufferu
public:
    const GLenum gl_drawType;
    const ModelDataLayout modelLayout;
    const size_t dataSize;

    Model(const float *data, int sizeOfData, ModelDataLayout modelDataLayout = ModelDataLayout::L_3COORD3NORMAL, GLenum gl_drawType = GL_TRIANGLES);
    void bindVAO();
    static void unbindVAO();
};