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

		case '3':
			app.rootScene = app.scenes[2];
			printf("scene changed to third\n");
			break;

		case '4':
			app.rootScene = app.scenes[3];
			printf("scene changed to fourth\n");
			break;
	}
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}


int main(void)
{
	app.callback_keyPress = keypress_callback;	
	glfwSetMouseButtonCallback(app.window, button_callback);

	app.Init(800, 600, "ZPG Projekt");

	app.LoadModels();
	app.LoadShaders();
	app.LoadObjects();

	app.RunLoop();


}