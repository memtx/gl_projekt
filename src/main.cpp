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
#include "models/sphere.h" //models are 3xfloat (pos), 3xfloat (normal)
#include "models/tree.h"
#include "models/OpenGL.h"
#include "models/plain.h"
#include "../vsbLogin.h"

#include "Application.h"

typedef glm::vec3 vec3;

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
			globalOffset.Translate(vec3(-1,0,0));
			break;
		case 'D': 
			globalOffset.Translate(vec3(1,0,0));
			break;

		case 'W':
			globalOffset.Scale(vec3(0.1));
			break;
		case 'S':
			globalOffset.Scale(vec3(-0.1));
			break;

		case 'Q':
			globalOffset.Rotate(vec3(0,20,0));
			break;
		case 'E':
			globalOffset.Rotate(vec3(0,-20,0));
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
	Model model_plain = Model(plain, sizeof(plain));
 	Model model_sphere = Model(sphere, sizeof(sphere));
 
	Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	Shader fragmentShaderYellow = Shader(GL_FRAGMENT_SHADER, "resources/3_yellow.frag");
	Shader vertexShader = Shader(GL_VERTEX_SHADER, "resources/4_true_transformable.vert");
	ShaderProgram sp = ShaderProgram(2, &fragmentShader, &vertexShader); 
	ShaderProgram spYellow = ShaderProgram(2, &fragmentShaderYellow, &vertexShader);

	for(int i=0; i<4; i++) 
		scenes.push_back(Scene());

	globalOffset.Scale(vec3(0.1, 0.1, 0.1));
	scenes[0].AddObject(new DrawableObject(&model_login, &sp, &globalOffset));
	
	for(float i=-1; i<1; i+= 0.2)
		scenes[0].AddObject(new DrawableObject(&model_tree, &sp, Transform(vec3(i,0,0.5), vec3(0), vec3(0.1))));
	for(float i=-1+0.1; i<1-0.2; i+= 0.2)
		scenes[0].AddObject(new DrawableObject(&model_bushes, &sp, Transform(vec3(i,0,0.5), vec3(0), vec3(0.1))));


	scenes[0].AddObject(new DrawableObject(&model_sphere, &spYellow, Transform(vec3(0,0.8,1), vec3(0), vec3(0.1)))); 

	app.rootScene = &(scenes[0]);
	scenes[1].AddObject(new DrawableObject(&model_tree, &sp, Transform(vec3(0,0,0), vec3(0), vec3(0.1))));
	//scenes[2].AddObject(&obj_tree);
	//scenes[3].AddObject(&obj_login);


	app.callback_preDraw =  [](){
		app.rootScene = &scenes[sceneIndex];
	};

	app.RunLoop();


}