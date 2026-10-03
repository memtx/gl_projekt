#pragma once
#include "Application.h"

class DrawableObject;

class Scene
{
private:
    std::vector<Scene*> children;
    std::vector<DrawableObject*> objects;
    
    std::vector<Scene*>::iterator GetIterator(Scene* child);
    std::vector<DrawableObject*>::iterator GetIterator(DrawableObject* obj);
public:
    Scene();
    void AddObject(DrawableObject *obj);
    void RemoveObject(DrawableObject *obj);
    void AddChild(Scene *child);
    void DeleteChild(Scene *child);
    std::vector<Scene*>* GetChildren();
    void DrawAllChildren();

};