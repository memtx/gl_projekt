#pragma once
#include "Application.h"

class Transform
{
private:

public:
    GLdouble x = 0;
    GLdouble y = 0;
    GLdouble z = 0;

    GLdouble roll = 0.0f;
    GLdouble pitch = 0.0f;
    GLdouble yaw = 0.0f;

    Transform(GLdouble x = 0.0f, GLdouble y = 0.0f, GLdouble z = 0.0f, GLdouble roll = 0.0f, GLdouble pitch = 0.0f, GLdouble yaw = 0.0f);
};