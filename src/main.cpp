#define GLAD_GL_IMPLEMENTATION

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Application.h"

static void error_callback(int error, const char* description){ fputs(description, stderr); }

/*
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}
*/
static void window_focus_callback(GLFWwindow* window, int focused){ printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified){ printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height){
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow *window, double x, double y){ printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode){
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
} 

//GLM test

/*
//==== cv 1 ======
// Projection matrix : 45degree Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);
*/


int main(void)
{
	Application *app = new Application(); 
	app->Init(800, 600, "ZPG Projekt");

	// Sets the key callback
	//glfwSetKeyCallback(app->window, key_callback);
	//glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(app->window, button_callback);
	glfwSetWindowFocusCallback(app->window, window_focus_callback);
	glfwSetWindowIconifyCallback(app->window, window_iconify_callback);
	glfwSetWindowSizeCallback(app->window, window_size_callback);

	glEnable(GL_DEPTH_TEST);
	
	app->RunLoop();


}