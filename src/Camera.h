#pragma once

#include "Application.h"
#include "Event.h"

typedef glm::mat4 mat4;

template <typename T>
class Event;

class Camera
{
private:
    mat4 view;
    mat4 projection;

public:
    float lookX = 0;
    float lookY = 0;

    Camera();
    ~Camera();

    void TestCall(){
        viewUpdate->Call(view);
        projectionUpdate->Call(projection);
    }

    Event<mat4> *viewUpdate;
    Event<mat4> *projectionUpdate; 
};