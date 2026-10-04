#include "DrawableObject.h"

//not using pointers is fine, the transform gets deleted by the destructor (scene must be non-ptr though)
DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, Transform t)
{
    model = m;
    shaderProgram = sp;
    transform = new Transform(t.pos, t.rot, t.scale);
    
    nonHeapTransformShouldDelete = true;
}

DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, Transform* t)
{
    model = m;
    shaderProgram = sp;
    transform = t;
}

DrawableObject::~DrawableObject()
{
    if(nonHeapTransformShouldDelete)
        delete this->transform;
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