//opengl minimálně 3.3, ideálně 4.6

#ifndef APPLICATION_H
#define APPLICATION_H


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>


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

//#include "./glutils.h"

class Application
{
public:
    // Pointer to the GLFW window
	GLFWwindow* window;

    //initialize openGL and its libraries. exits on failure.
    void Init();
    
    GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile);

};

#endif