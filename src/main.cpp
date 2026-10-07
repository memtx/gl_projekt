#define GLAD_GL_IMPLEMENTATION

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Application.h"


typedef glm::vec3 vec3;


static void error_callback(int error, const char* description){ fputs(description, stderr); }

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

static void keypress_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action != GLFW_PRESS)
		return;

	switch(key)
	{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;

		case 'A':
			app.controlledTransform->Translate(vec3(-1,0,0));
			break;
		case 'D': 
			app.controlledTransform->Translate(vec3(1,0,0));
			break;

		case 'W':
			app.controlledTransform->Scale(vec3(1/1.1));
			break;
		case 'S':
			app.controlledTransform->Scale(vec3(1.1));
			break;

		case 'Q':
			app.controlledTransform->Rotate(vec3(0,20,0));
			break;
		case 'E':
			app.controlledTransform->Rotate(vec3(0,-20,0));
			break;


		case '1':
			app.rootScene = app.scenes[0];
			printf("scene changed to first\n");
			break;

		case '2':
			app.rootScene = app.scenes[1];
			printf("scene changed to second\n");
			break;
	}
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}


int main(void)
{
	app.callback_keyPress = keypress_callback;	
	
	//glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(app.window, button_callback);
	//glfwSetWindowFocusCallback(app->window, window_focus_callback);
	//glfwSetWindowIconifyCallback(app->window, window_iconify_callback);
	glfwSetWindowSizeCallback(app.window, window_size_callback);

	app.Init(800, 600, "ZPG Projekt");

	app.LoadModels();
	app.LoadShaders();
	app.LoadObjects();

	app.callback_preDraw = [](){
		//app.rootScene = app.scenes[];
	};

	app.RunLoop();


}