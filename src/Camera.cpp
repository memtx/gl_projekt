#include "Camera.h"

Camera::Camera()
{
    //  (look vector, target, up)
    vec3 cameraPos = vec3(0.5,0,0.5);
    vec3 cameraTarget = vec3(0,0,0);

    vec3 cameraDir = glm::normalize(cameraPos - cameraTarget); //aims opposite to the target
    
    vec3 cameraRight = glm::normalize(glm::cross(vec3(0,1,0), cameraDir)); //inbetween step to get the camera up position
    vec3 cameraUp = glm::cross(cameraDir, cameraRight);
    //view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::lookAt(cameraPos, cameraDir, cameraUp);
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

    if(false)
    {

    }

    viewUpdate->Call(view);
    projectionUpdate->Call(projection);
}