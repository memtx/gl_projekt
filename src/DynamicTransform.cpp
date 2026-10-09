#include "DynamicTransform.h"

void DynamicTransform::UpdateDynamicTransforms(float deltaTime)
{
    for(DynamicTransform* t : DynamicTransform::transforms)
    {
        switch(t->trType)
        {
            case DT_LINEAR_ROTATE:
            {
                t->Rotate(t->trIncrement*deltaTime);
                t->trCurrentCount++;
                if(t->trCurrentCount > t->trCountToLoop)
                { 
                    t->ResetTransforms(*t->trStart);
                    t->trCurrentCount = 0;
                }
                break;
            }
        }
    }
}

std::vector<DynamicTransform*> DynamicTransform::transforms = std::vector<DynamicTransform*>();

DynamicTransform::DynamicTransform(DynTransformType DT_TYPE, Transform beginTransform, vec3 increment, int incrementCount)
{

    
    this->trType = DT_TYPE;
    this->trStart = new Transform(beginTransform);
    this->trIncrement = increment;

    this->trCountToLoop = incrementCount;
    this->trCurrentCount = 0;

    transforms.push_back(this);
}

DynamicTransform::~DynamicTransform()
{
    delete this->trStart;

    for(auto i=transforms.begin(); i!=transforms.end(); i++)
    {
        if(*i == this)
        {
            transforms.erase(i);
            return;
        }
    }
    Log.FatalError("Couldn't remove DynamicTransform from list!");
}