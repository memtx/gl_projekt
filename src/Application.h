//opengl minimálně 3.3, ideálně 4.6
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>
#include <random>
#include <time.h>

//include glad
//#include <glad/include/glad/glad.h>
#include <glad/include/glad/gl.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
//Include GLM    
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Event.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "DynamicTransform.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "Log.h"
#include "Camera.h"

class Scene;
class Shader;
class ShaderProgram;
class Transform;
class DynamicTransform;
class Model;
class Camera;

enum AppModels
{
	MDL_TRIANGLE = 0,
    MDL_TREE = 1,
	MDL_LOGIN = 2,
	MDL_BUSHES = 3,
	MDL_PLAIN = 4,
	MDL_SPHERE = 5,
    MDL_EARTH = 6,
    MDL_SUN = 7,
    MDL_MOON = 8,
    MDL_CLOCK = 9,
    MDL_COUNT = 10
};

enum AppShaders
{
    S_BASE_FRAG = 0,
    S_MATS_VERTEX = 1,
    S_MATSNORMAL_VERTEX = 2,
    S_CLOCK_VERTEX = 3,
    S_CLOCK_FRAG = 4,
    S_COUNT = 5
};
 
enum AppShaderPrograms
{
    SP_FULLMATS = 0,
    SP_FULLMATSNORMAL = 1,
    SP_CLOCK = 2,
    SP_COUNT = 3
};

static class Application
{
private:
    std::vector<Model*> models = std::vector<Model*>(MDL_COUNT);
    std::vector<Shader*> shaders = std::vector<Shader*>(S_COUNT);
    std::vector<ShaderProgram*> shaderPrograms = std::vector<ShaderProgram*>(SP_COUNT);
    
public:
    // Pointer to the GLFW window
	GLFWwindow *window;
    Scene *rootScene;
    std::vector<Scene*> scenes = std::vector<Scene*>(); 
    Transform *controlledTransform;
    Camera *cam;

    double deltaTime;

    ~Application();

    //initialize openGL and its libraries. exits on failure.
    void Init(int width, int height, const char *windowName);
    void RunLoop();

    void LoadModels();
    void LoadShaders();
    void LoadObjects();

    void (*testCallback)();
    std::function<void()> callback_preDraw;
    std::function<void()> callback_postDraw;    
    void (*callback_keyPress)(GLFWwindow* window, int key, int scancode, int action, int mods); //has to be set before running app->init()!!!!!
    
} app;