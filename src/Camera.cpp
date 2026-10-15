#include "Camera.h"

Camera::Camera()
{
    projectionUpdate = new Event<mat4>();
    viewUpdate = new Event<mat4>();
    //  (look vector, target, up)
    cameraPos   = vec3(0,0,3);
    cameraFront = vec3(0,0,-1);
    cameraUp    = vec3(0,1,0);

    rot = vec2(-90.0f,0.0f);

    //view = glm::lookAt(cameraPos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
 
    UpdateViewAndCall();
}

Camera::~Camera()
{
    delete projectionUpdate;
    delete viewUpdate;
} 

void Camera::UpdateViewAndCall()
{
    view = glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
    viewUpdate->Call(view);
}

void Camera::SetPos(vec3 p) //absolute coordinates
{
    this->cameraPos = p;
    UpdateViewAndCall();
}

void Camera::Move(vec3 p) //relative coordinates, horizontal and vertical separated
{
    const float speed = 0.1;

    //X
    cameraPos += speed * p.x * glm::normalize(glm::cross(vec3(cameraFront.x, 0, cameraFront.z), cameraUp))
    //Y
    + speed * p.y * vec3(0,1,0)
    //Z
    + speed * p.z * vec3(cameraFront.x, 0, cameraFront.z);

    UpdateViewAndCall();
}

void Camera::AddRot(glm::vec2 r)
{
    const float sensitivity = 5.0f;

    float xoffset = r.x * sensitivity;
    float yoffset = r.y * sensitivity;

    rot.x += xoffset;
    rot.y += yoffset;

    if(rot.y >= 90.0f)
    rot.y = 90.0f;
    if(rot.y <= -90.0f)
    rot.y = -90.0f;

    cameraFront.x = cos(glm::radians(rot.x))*cos(glm::radians(rot.y));
    cameraFront.y = sin(glm::radians(rot.y));
    cameraFront.z = sin(glm::radians(rot.x))*cos(glm::radians(rot.y));
    
    cameraFront = glm::normalize(cameraFront);

    UpdateViewAndCall();
}