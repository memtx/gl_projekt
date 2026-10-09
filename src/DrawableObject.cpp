#include "DrawableObject.h"

DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, DynamicTransform t, std::vector<DrawableObject*> childrenVec)
{
    model = m;
    shaderProgram = sp;
    
    //t.RecalculateMatrix();
    transform = new DynamicTransform(t);
    ((DynamicTransform*)transform)->PostCopyInit();

    children = std::vector<DrawableObject*>();
    for(DrawableObject *child :childrenVec)
        AddChild(child);

    nonHeapTransformShouldDelete = true;
}

DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, DynamicTransform* t, std::vector<DrawableObject*> childrenVec)
{
    model = m;
    shaderProgram = sp;
    transform = t;

    children = std::vector<DrawableObject*>();
    for(DrawableObject *child :childrenVec)
        AddChild(child);
}


//not using pointers is fine, the transform gets deleted by the destructor (scene must be non-ptr though)
DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, Transform t, std::vector<DrawableObject*> childrenVec)
{
    model = m;
    shaderProgram = sp;
    
    t.RecalculateMatrix();
    transform = new Transform(t);

    children = std::vector<DrawableObject*>();
    for(DrawableObject *child :childrenVec)
        AddChild(child);

    nonHeapTransformShouldDelete = true;
}

DrawableObject::DrawableObject(Model *m, ShaderProgram *sp, Transform* t, std::vector<DrawableObject*> childrenVec)
{
    model = m;
    shaderProgram = sp;
    transform = t;

    children = std::vector<DrawableObject*>();
    for(DrawableObject *child :childrenVec)
        AddChild(child);
}

DrawableObject::~DrawableObject()
{
    if(nonHeapTransformShouldDelete)
        delete this->transform;
}

void DrawableObject::AddChild(DrawableObject *child)
{
    this->transform->AddChild(child->transform);
    children.push_back(child);
}

void DrawableObject::RemoveChild(DrawableObject *child)
{
    for(auto i=children.begin(); i != children.end(); i++)
    {
        if(*i == child)
        {
            this->transform->RemoveChild(child->transform);
            children.erase(i);
            return;
        }
    }
    Log.FatalError("DrawableObject child to be removed not found!");
}

void DrawableObject::Draw() //first draw parent, then children. I guess openGL handles the triangle draw order?
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
    
    for(DrawableObject *child : children)
        child->Draw();
    //model->unbindVAO();
    //glUseProgram(0);
}

ShaderProgram* DrawableObject::activeShaderProgram = nullptr;
Model* DrawableObject::activeModel = nullptr; 