#include "Camera.h"

Camera::Camera()
{
    //  (look vector, target, up)
    vec3 lookVec = vec3(0,0,1);
    vec3 target = vec3(0);

    view = glm::lookAt(lookVec, lookVec + target, vec3(0,1,0));
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
