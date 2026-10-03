#define GLAD_GL_IMPLEMENTATION

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Application.h"

#include "models/bushes.h"
#include "models/triangle.h"

Application *app = new Application(); 


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



Scene first = Scene();
Scene second = Scene();
Transform globalOffset = Transform();

static void keypress_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	switch(key)
	{
		case 'A':
			globalOffset.pos.x -= 1;
			break;
		case 'D': 
			globalOffset.pos.x += 1;
			break;

		case 'W':
			globalOffset.scale *= 1.1;
			break;
		case 'S':
			globalOffset.scale /= 1.1;
			break;

		case '1':
			app->rootScene = &first;
			printf("scene changed to first\n");
			break;

		case '2':
			app->rootScene = &second;
			printf("scene changed to second\n");
			break;

		case '3':
			app->rootScene = nullptr;
			printf("scene changed to empty\n");
			break;
	}
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

int main(void)
{
	app->callback_keyPress = keypress_callback;	
	
	//glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(app->window, button_callback);
	//glfwSetWindowFocusCallback(app->window, window_focus_callback);
	//glfwSetWindowIconifyCallback(app->window, window_iconify_callback);
	glfwSetWindowSizeCallback(app->window, window_size_callback);

	app->Init(800, 600, "ZPG Projekt");


	Model *model_tree = new Model(tree, sizeof(tree));
	Model *model_bushes = new Model(bushes, sizeof(bushes));
 
	Shader *fragmentShader = new Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	Shader *vertexShader = new Shader(GL_VERTEX_SHADER, "resources/3_transformable.vert");

	ShaderProgram *sp = new ShaderProgram(2, fragmentShader, vertexShader); 
    DrawableObject *obj_tree = new DrawableObject(model_tree, sp, &globalOffset);
	DrawableObject *obj_bushes = new DrawableObject(model_bushes, sp, &globalOffset);

	
	first.AddObject(obj_tree);
	
	second.AddObject(obj_bushes);

	app->rootScene = &first;
	
	app->callback_preDraw = [obj_tree]()
	{
		if(obj_tree->transform->rot.x > 360)
			obj_tree->transform->rot.x = 0;
		else
			obj_tree->transform->rot.x += 0.01f;
	};

	app->RunLoop();


}