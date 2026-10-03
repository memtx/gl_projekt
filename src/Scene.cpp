#include "Scene.h"

Scene::Scene()
{
    children = std::vector<Scene*>();
    objects = std::vector<DrawableObject*>();
}

std::vector<Scene*>::iterator Scene::GetIterator(Scene* child)
{
    for(auto it = children.begin(); it != children.end(); it++)
    {
        if(*it == child)
            return it;
    }
    return this->children.end();
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

void Scene::AddChild(Scene *child)
{ children.push_back(child); }

void Scene::DeleteChild(Scene *child)
{ 
    children.erase(GetIterator(child));
    delete child;
}

void Scene::AddObject(DrawableObject *obj)
{
    objects.push_back(obj);
}

void Scene::RemoveObject(DrawableObject *obj)
{
    objects.erase(GetIterator(obj));
}

std::vector<Scene*>* Scene::GetChildren()
{
    return &children;
}

void Scene::DrawAllChildren()
{
    for(Scene *child : children)
    { child->DrawAllChildren(); }   

    for(DrawableObject *obj: objects)
    { obj->Draw(); }
}