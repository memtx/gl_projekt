#pragma once

#include "Application.h"
#include "Event.h"

typedef glm::mat4 mat4;
typedef glm::vec2 vec2;


template <typename T>
class Event;

class Camera
{
private:

    mat4 view;
    mat4 projection;
    
    vec2 rot;
    vec3 cameraPos;
    vec3 cameraFront; //aims opposite to the target
    vec3 cameraUp;

    float fov;
    vec2 aspectRatio;

    void UpdateViewAndCall();
    void UpdateProjectionAndCall();

public:

    Camera(vec3 pos = vec3(0), vec2 rot = vec2(0), vec2 aspectRatio = vec2(400,300), float fov = 60.0f);
    ~Camera();
    vec3 GetPos() {return cameraPos;}

    void SetPos(vec3 pos);
    void Move(vec3 pos);
    void SetRot(vec2 rot);
    void AddRot(vec2 rot);
    float GetFov() {return fov; }
    void SetFov(float fov);
    vec2 GetAspectRatio() {return aspectRatio; }
    void SetAspectRatio(int width, int height);

    mat4 getView() {return view;}
    mat4 getProjection() {return projection;}

    Event<Camera*> *viewUpdate;
    Event<Camera*> *projectionUpdate; 
};