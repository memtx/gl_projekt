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

        using namespace std::placeholders;
class ShaderProgram
{
private:
    std::vector<Shader*> shaders = std::vector<Shader*>();
    GLint GetVarLocation(const char* name);
    void SetFloat(GLint location, float value);
    void OnUpdateProjection(mat4 proj);
    void OnUpdateView(mat4 viewMat);
    
    static void testFunc(mat4 t) {Log.Warn("Test");}

    GLint modelMatLoc;
    GLint viewMatLoc;
    GLint projMatLoc;

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

    void UseCamera(Camera *c);

};