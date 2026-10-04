#define GLAD_GL_IMPLEMENTATION

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "models/bushes.h"
#include "models/triangle.h"
//#include "./glutils.h"
#include "models/sphere.h" //modely jsou 3xfloat (pos), 3xfloat (normal)
#include "models/tree.h"
//#include "models/OpenGL.h"
#include "../vsbLogin.h"

#include "Application.h"

Application app = Application(); 


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



Transform globalOffset = Transform();
std::vector<Scene> scenes = std::vector<Scene>();
int sceneIndex = 0;

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
			sceneIndex--;
			printf("scene changed to first\n");
			break;

		case '2':
			sceneIndex++;
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


	Model model_tree = Model(tree, sizeof(tree));
	Model model_bushes = Model(bushes, sizeof(bushes));
	Model model_triangle = Model(triangle, sizeof(triangle));
	Model model_login = Model(vsbLogin, sizeof(vsbLogin));
 
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	Shader vertexShader = Shader(GL_VERTEX_SHADER, "resources/3_transformable.vert");
	
	ShaderProgram sp = ShaderProgram(2, &fragmentShader, &vertexShader); 

	for(int i=0; i<4; i++)
		scenes.push_back(Scene());

	DrawableObject obj_triangle = DrawableObject(&model_triangle, &sp, &globalOffset);
	DrawableObject obj_tree = DrawableObject(&model_tree, &sp, &globalOffset);
	DrawableObject obj_bushes = DrawableObject(&model_bushes, &sp, &globalOffset);
	DrawableObject obj_login = DrawableObject(&model_login, &sp, &globalOffset);
	scenes[0].AddObject(&obj_triangle);
	scenes[1].AddObject(&obj_tree);
	scenes[2].AddObject(&obj_bushes);
	scenes[3].AddObject(&obj_login);


	app.rootScene = &scenes[0];
	
	app.callback_preDraw = [obj_tree]()
	{
		app.rootScene = &scenes[sceneIndex];

		if(obj_tree.transform->rot.x > 360)
			obj_tree.transform->rot.x = 0;
		else
			obj_tree.transform->rot.x += 0.01f;
	};

	app.RunLoop();


}