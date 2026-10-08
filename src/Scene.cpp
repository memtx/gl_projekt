#include "Scene.h"

Scene::Scene()
{
    objects = std::vector<DrawableObject*>();
}

Scene::~Scene()
{
    for(DrawableObject *obj : objects)
        delete obj;
}

std::vector<DrawableObject*>::iterator Scene::GetIterator(DrawableObject* obj)
{
    for(auto it = objects.begin(); it != objects.end(); it++)
    {
        if(*it == obj)
            return it;
    }
    return this->objects.end();
}

//objects pointers are deleted with the scene!
void Scene::AddObject(DrawableObject *obj)
{
    objects.push_back(obj);
}

void Scene::RemoveObject(DrawableObject *obj)
{
    objects.erase(GetIterator(obj));
}

void Scene::DrawAll()
{ 
    for(DrawableObject *obj: objects)
    { obj->Draw(); }
} 