#pragma once

#include <stdarg.h>
#include <vector>
#include <functional>


#include "Shader.h"
#include "Transform.h"
#include "Camera.h"
#include "Event.h"

class Shader;
class Transform;
class Camera;
template <typename T>
class Event;
class logger;

        using namespace std::placeholders;
class ShaderProgram
{
private:
    std::vector<Shader*> shaders = std::vector<Shader*>(); //todo
    GLint GetVarLocation(const char* name);
    void SetFloat(GLint location, float value);
    void OnUpdateProjection(Camera *c);
    void OnUpdateView(Camera *c);

    GLint modelMatLoc;
    GLint viewMatLoc;
    GLint projMatLoc;
    GLint unixSecsLoc;

    GLint ambientStrengthLoc;
    GLint globalLightPosLoc;
    GLint cameraPosLoc;

    Camera *camera;

    mat4 cameraView;
    mat4 cameraProj;

    GLuint id;

public:
    ShaderProgram(Camera *camera = nullptr, int shaderCount = 0, ...); //Create and link the shader program 
    void Use();
    static void Disuse();
    void AddShader();
    void RemoveShader();
    bool HasTransform();
    void SetMatrices(Transform *t);

    void SetAmbientStrength(float normalizedStrength);
    void SetGlobalLightPos(vec3 globalLightPos);

    void UseCamera(Camera *c);

};