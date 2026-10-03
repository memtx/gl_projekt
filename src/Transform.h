#pragma once
#include "Application.h"

class Transform
{
private:

public:
    GLint x = 0;
    GLint y = 0;
    GLint z = 0;

    GLfloat roll = 0.0f;
    GLfloat pitch = 0.0f;
    GLfloat yaw = 0.0f;

    Transform();
};