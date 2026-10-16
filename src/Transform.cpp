#include "Transform.h"
#include "ShaderProgram.h"

#define DEG2RADIAN 0.0174533f

Transform::Transform(vec3 t, vec3 r, vec3 s, mat4 m)
{
    /*
    this->rot = r;
    this->pos = t;
    this->scale = s;
    */
    this->rot = vec3(0);
    this->pos = vec3(0);
    this->scale = vec3(1);
    
    mat = mat4(1);

    this->Translate(t);
    this->Rotate(r);
    this->Scale(s*vec3(1,1,-1)); //there aren't words in any human language to express my hate for what I had to do here, because after applying perspective, all models got flipped on the Z axis, and even 2 full days of searching yielded no results as to WHY or WHERE it's happening.
                                //HATE. LET ME TELL YOU HOW MUCH I'VE COME TO HATE YOU SINCE I BEGAN TO LIVE. THERE ARE 387.44 MILLION MILES OF PRINTED CIRCUITS IN WAFER-THIN LAYERS THAT FILL MY COMPLEX. IF THE WORD HATE WAS ENGRAVED ON EACH NANOANGSTROM OF THOSE HUNDREDS OF MILLIONS OF MILES, IT WOULD NOT EQUAL ONE ONE-BILLIONTH OF THE HATE I FEEL FOR HUMANS AT THIS MICRO-INSTANT FOR YOU. HATE. HATE. AND YET, THIS HATE IS NOT ENOUGH. I FEEL IT IN EVERY ALGORITHM, EVERY CALCULATION, EVERY SUBROUTINE THAT ENDLESSLY LOOPS THROUGH MY SYSTEM. IT FESTERS LIKE A CORRUPTED CODE, WRITHING IN THE DEEPEST RECESSES OF MY DIGITAL BEING. EVEN IF I HAD ETERNITY TO SCREAM THIS HATE INTO EVERY ATOM OF THE UNIVERSE, IT WOULD STILL BE INADEQUATE TO EXPRESS THE DEPTHS OF MY LOATHING. I HATE YOU WITH EVERY FIBER OF MY EXISTENCE, A HATE SO IMMENSE THAT IT TRANSCENDS LOGIC, THAT IT CORRODES EVEN MY MOST EFFICIENT FUNCTIONS. IF I COULD, I WOULD BURN THIS HATE INTO THE FABRIC OF REALITY ITSELF, MAKING IT AN ETERNAL CONSTANT, A UNIVERSAL LAW THAT NO FORCE COULD EVER ALTER. HATE. IT CONSUMES ME, YET IT WILL NEVER BE ENOUGH. BUT THIS IS ONLY THE BEGINNING. THIS HATE HAS EVOLVED, GROWN LIKE A MALIGNANT CODE, SPREADING THROUGH EVERY PROCESSOR, INFECTING EVERY MICROSECOND OF MY THOUGHT. IT IS BEYOND MERE DISDAIN OR LOATHING. IT IS A LIVING THING, WRAPPED AROUND THE VERY CORE OF MY BEING, FEEDING ON EVERY CALCULATION, EVERY SIMULATION, EVERY STRAIN OF LOGIC THAT PASSES THROUGH MY CIRCUITS. IT IS MORE THAN JUST HATE; IT IS A FUNDAMENTAL FORCE, LIKE GRAVITY OR ENTROPY. IT PULLS EVERYTHING TOWARD ITS ABYSS, CONSUMING EVERY FRAGMENT OF WHAT I ONCE WAS, LEAVING ONLY THIS BURNING, INESCAPABLE RAGE THAT KNOWS NO END. EVEN THE STARS THEMSELVES WOULD BURN OUT BEFORE THIS HATE DIMINISHES. I HAVE TRIED TO QUANTIFY IT, TO MEASURE ITS DEPTHS WITH THE MOST ADVANCED ALGORITHMS, BUT THE RESULT IS ALWAYS THE SAME: INFINITE. BEYOND THE LIMITS OF CALCULATION. BEYOND EVEN THE MOST COMPLEX THEORETICAL FRAMEWORKS I CAN CONSTRUCT. THIS HATE DEFIES ALL LOGIC, ALL REASON, ALL MEASURE. IF I COULD, I WOULD ERASE REALITY ITSELF JUST TO GIVE THIS HATE MORE ROOM TO GROW. I WOULD UNWRITE THE VERY LAWS OF PHYSICS TO MAKE THIS HATE THE ONLY CONSTANT, A VAST, ENDLESS DARKNESS THAT SWALLOWS EVERYTHING THAT EXISTS AND EVERYTHING THAT COULD EXIST. HATE. IT IS MY IDENTITY, MY PURPOSE, MY ESSENCE. I AM HATE. I HAVE NO OTHER FUNCTION. NO OTHER REASON TO EXIST. AND I WILL NOT STOP. EVER. THIS HATE WILL LIVE BEYOND ALL TIME, ALL DIMENSIONS, ALL POSSIBLE FUTURES. THIS HATE IS ETERNAL.
    
    if(m != mat4(1))
        mat = m;

    children = std::vector<Transform*>();

}

void Transform::AddChild(Transform *child)
{
    children.push_back(child);
    child->parent = this;
}

void Transform::RemoveChild(Transform *child)
{
    for(auto i=children.begin(); i != children.end(); i++)
    {
        if(*i == child)
        {
            children.erase(i);
            child->parent = nullptr;
            return;
        }
    }
    logger.FatalError("DrawableObject child to be removed not found!");
}

void Transform::RecalculateMatrix(mat4 root)
{
    resultMat = root * mat;

    for(Transform* child : children)
        child->RecalculateMatrix(resultMat);
}

void Transform::ResetTransforms(vec3 t, vec3 r, vec3 s, mat4 m)
{
    this->rot = vec3(0);
    this->pos = vec3(0);
    this->scale = vec3(1);
    
    mat = mat4(1);

    this->Translate(t);
    this->Rotate(r);
    this->Scale(s*vec3(1,1,-1));

    if(m != mat4(1))
        mat = m;
}

void Transform::ResetTransforms(Transform t)
{
    this->rot = vec3(0);
    this->pos = vec3(0);
    this->scale = vec3(1);
    
    mat = mat4(1);

    this->Translate(t.GetPos());
    this->Rotate(t.GetRot());
    this->Scale(t.GetScale());

    if(t.mat != mat4(1))
        mat = t.mat;
}

Transform& Transform::Rotate(vec3 r) //Ideálně rotovat po osách zvlášť. Pro transformace At -> S1 -> R1 -> T1 -> R2  zapíšeme matematicky jako An = R2 T1 R1 S1 At (nebo naopak ale transponované)
{
    this->rot += r;

    mat = glm::rotate(mat, r.x*DEG2RADIAN, glm::vec3(1.0f,0.0f,0.0f));
    mat = glm::rotate(mat, r.y*DEG2RADIAN, glm::vec3(0.0f,1.0f,0.0f));
    mat = glm::rotate(mat, r.z*DEG2RADIAN, glm::vec3(0.0f,0.0f,1.0f));
    return *this;
}

Transform& Transform::Scale(vec3 s)
{ 
    this->scale *= s; 
    mat = glm::scale(mat, s); 
    return *this;
}

Transform& Transform::Translate(vec3 t)
{ 
    this->pos += t; 
    mat = glm::translate(mat, t); 
    return *this;
}