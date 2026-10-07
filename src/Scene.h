#pragma once
#include "vector"

#include "DrawableObject.h"

class DrawableObject;


class Scene
{
private:
    std::vector<DrawableObject*> objects;
    
    std::vector<Scene*>::iterator GetIterator(Scene* child);
    std::vector<DrawableObject*>::iterator GetIterator(DrawableObject* obj);
public:
    Scene();
    ~Scene();
    void AddObject(DrawableObject *obj);
    void RemoveObject(DrawableObject *obj);
    void DrawAll();

};