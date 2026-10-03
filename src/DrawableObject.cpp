#include "DrawableObject.h"

DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, Transform *t)
{
    model = m;
    shaderProgram = sp;
    transform = t;
}

void DrawableObject::Draw()
{
    shaderProgram->setTransform(transform);

    glUseProgram(shaderProgram->id);
    model->bindVAO();
    glDrawArrays(model->gl_drawType,0, model->dataSize);
    model->unbindVAO();
    glUseProgram(0);
}