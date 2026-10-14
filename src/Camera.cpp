#include "Camera.h"

Camera::Camera()
{
    //  (look vector, target, up)
    vec3 lookVec = vec3(1,0,0);
    vec3 target = vec3(0,0,0);


    glm::vec3 cameraPos = glm::vec3(0.0f, 2.0f, 0.0f); //todo: figure out how to make rotations not nullify (these params are good, just has to be 90deg always)
    //view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(lookVec, target, vec3(0,1,0));
    projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
 
    projectionUpdate = new Event<mat4>();
    viewUpdate = new Event<mat4>();

    auto test = Event<int>();
}

Camera::~Camera()
{
    delete projectionUpdate;
    delete viewUpdate;
}

void Camera::Rotate(vec3 rot)
{
    view = glm::rotate(view, rot.x, vec3(1,0,0));
    view = glm::rotate(view, rot.y, vec3(0,1,0));
    view = glm::rotate(view, rot.z, vec3(0,0,1));

    viewUpdate->Call(view);
}