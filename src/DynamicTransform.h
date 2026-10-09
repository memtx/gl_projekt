#pragma once
#include "Transform.h"
#include "Log.h"

enum DynTransformType
{
    DT_LINEAR_ROTATE,
    DT_LINEAR_SCALE,
    DT_LINEAR_TRANSLATE,
};

class DynamicTransform :public Transform
{
private:
    static std::vector<DynamicTransform*> transforms; //used for updating
    int trCurrentCount;
public:
    DynTransformType trType;
    Transform *trStart;
    vec3 trIncrement;
    int trCountToLoop;

    DynamicTransform(DynTransformType DT_TYPE, Transform trStart, vec3 trIncrement, int trCountToLoop);
    void PostCopyInit(); //copy constructor doesn't work for my use case
    ~DynamicTransform();
    static void UpdateDynamicTransforms(float deltaTime);
    
};