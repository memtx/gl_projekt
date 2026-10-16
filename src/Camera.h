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

    void UpdateViewAndCall();
    void UpdateProjectionAndCall();

public:

    Camera();
    ~Camera();
    vec3 GetPos();
    vec3 GetRot();

    void SetPos(vec3 pos);
    void Move(vec3 pos);
    void SetRot(vec2 rot);
    void AddRot(vec2 rot);


    mat4 getView() {return view;}
    mat4 getProjection() {return projection;}

    Event<mat4> *viewUpdate;
    Event<mat4> *projectionUpdate; 
};