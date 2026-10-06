#include "DrawableObject.h"

//not using pointers is fine, the transform gets deleted by the destructor (scene must be non-ptr though)
DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, Transform t)
{
    model = m;
    shaderProgram = sp;
    transform = new Transform(t.GetPos(), t.GetRot(), t.GetScale());

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

    if(activeShaderProgram != shaderProgram)
    {
        activeShaderProgram = shaderProgram;
        activeShaderProgram->Use();  
    }

    shaderProgram->setTransform(transform);


    if(activeModel != model)
    {
        activeModel = model;
        activeModel->bindVAO();
    }

    glDrawArrays(activeModel->gl_drawType,0, activeModel->dataSize);
    //model->unbindVAO();
    //glUseProgram(0);
}

ShaderProgram* DrawableObject::activeShaderProgram = nullptr;
Model* DrawableObject::activeModel = nullptr; 