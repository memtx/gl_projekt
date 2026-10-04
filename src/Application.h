//opengl minimálně 3.3, ideálně 4.6
#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <functional>

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

#include "Shader.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Scene.h"

class Scene;

class Application
{
private:

public:
    // Pointer to the GLFW window
	GLFWwindow *window;
    Scene *rootScene;

    //initialize openGL and its libraries. exits on failure.
    void Init(int width, int height, const char *windowName);
    void RunLoop();

    std::function<void()> callback_preDraw;
    std::function<void()> callback_postDraw;    
    void (*callback_keyPress)(GLFWwindow* window, int key, int scancode, int action, int mods); //has to be set before running app->init()!!!!!
    
};
