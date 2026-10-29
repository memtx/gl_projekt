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
#include "Material.h"
#include "MaterialProperty.h"

#include "Input.h"

class Scene;
class Shader;
class ShaderProgram;
class Transform;
class DynamicTransform;
class Model;
class Camera;

enum AppModels
{
	MDL_TRIANGLE,
    MDL_TREE,
	MDL_LOGIN,
	MDL_BUSHES,
	MDL_PLAIN,
	MDL_SPHERE,
    MDL_EARTH,
    MDL_SUN,
    MDL_MOON,
    MDL_CLOCK,
    MDL_DINO,
    MDL_SUZY_FLAT,
    MDL_SUZY_SMOOTH,
    MDL_COUNT 
};

enum AppShaders
{
    S_BASE_FRAG,
    S_MATS_VERTEX,
    S_MATSNORMAL_VERTEX,
    S_CLOCK_VERTEX,
    S_TREE_VERTEX,
    S_LIGHTABLE_VERTEX,
    S_AMBIENT_FRAG,
    S_DIFFUSE_FRAG,
    S_PHONG_FRAG,
    S_BLINNPHONG_FRAG,
    S_REFLECTOR_FRAG,
    S_BPDISTANCE_FRAG,
    S_COUNT 
};
 
enum AppShaderPrograms
{
    SP_FULLMATS,
    SP_FULLMATSNORMAL,
    SP_TREESPLIT,
    SP_CLOCK,
    SP_AMBIENT,
    SP_DIFFUSE,
    SP_PHONG,
    SP_BLINNPHONG,
    SP_REFLECTOR,
    SP_BPDISTANCE,
    SP_BPTREE,
    SP_COUNT
};

enum Materials
{
    MAT_EMPTY,
    MAT_FULLBRIGHT_TEXTURED,
    MAT_FULLBRIGHT_COLORED,
    MAT_DIFFUSE,
    MAT_PHONG,
    MAT_BLINNPHONG,
    MAT_REFLECTOR,
    MAT_BPATTENUATION,
    MAT_BPATTENUATION_GREEN,
    MAT_BPATTENUATION_NORM,
    MAT_COUNT
};

extern class Application
{
private:
    std::vector<Model*> models = std::vector<Model*>(MDL_COUNT);
    std::vector<Shader*> shaders = std::vector<Shader*>(S_COUNT);
    std::vector<ShaderProgram*> shaderPrograms = std::vector<ShaderProgram*>(SP_COUNT);
    std::vector<Material*> materials = std::vector<Material*>(MAT_COUNT);
    
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
    void Init(int width, int height, float fov, const char *windowName);
    void RunLoop();

    void LoadModels();
    void LoadShaders();
    void LoadObjects();
    void LoadMaterials();

    void (*testCallback)();
    std::function<void()> callback_preDraw;
    std::function<void()> callback_postDraw;    
    void (*callback_keyPress)(GLFWwindow* window, int key, int scancode, int action, int mods); //has to be set before running app->init()!!!!!
    
} app;
