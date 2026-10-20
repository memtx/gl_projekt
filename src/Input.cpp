#include "Input.h"

Application app;


vec2 Input::prevCursor = vec2(-1);
float Input::sensitivity = 0.05;



bool Input::IsKeyPressed(int GLFWKEY)
{
	return glfwGetKey(app.window, GLFWKEY);
}

void Input::processKeyInputs()
{
	if(IsKeyPressed(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(app.window, GL_TRUE);

	if(IsKeyPressed(GLFW_KEY_A))
		app.cam->Move(vec3(-1,0,0));
	
	if(IsKeyPressed(GLFW_KEY_D))
		app.cam->Move(vec3(1,0,0));

	if(IsKeyPressed(GLFW_KEY_W))
		app.cam->Move(vec3(0,0,1));

	if(IsKeyPressed(GLFW_KEY_S))
		app.cam->Move(vec3(0,0,-1));
		
	if(IsKeyPressed(GLFW_KEY_LEFT_SHIFT))
		app.cam->Move(vec3(0,-1,0));

	if(IsKeyPressed(GLFW_KEY_SPACE))
		app.cam->Move(vec3(0,1,0));
		//==============================
	if(IsKeyPressed(GLFW_KEY_I))
		app.controlledTransform->Translate(vec3(0,0,1));
	
	if(IsKeyPressed(GLFW_KEY_K))
		app.controlledTransform->Translate(vec3(0,0,-1));
	
	if(IsKeyPressed(GLFW_KEY_J))
		app.controlledTransform->Translate(vec3(-1,0,0));
	
	if(IsKeyPressed(GLFW_KEY_L))
		app.controlledTransform->Translate(vec3(1,0,0));

	if(IsKeyPressed(GLFW_KEY_Y))
		app.controlledTransform->Translate(vec3(0,1,0));
	
	if(IsKeyPressed(GLFW_KEY_H))
		app.controlledTransform->Translate(vec3(0,-1,0));

	if(IsKeyPressed(GLFW_KEY_U))
		app.controlledTransform->Rotate(vec3(0,20,0));
		
	if(IsKeyPressed(GLFW_KEY_O))
		app.controlledTransform->Rotate(vec3(0,-20,0));
		
	if(IsKeyPressed(GLFW_KEY_N))
		app.controlledTransform->Scale(vec3(1.1));
		
	if(IsKeyPressed(GLFW_KEY_M))
		app.controlledTransform->Scale(vec3(1/1.1));

		//==========================

	if(IsKeyPressed(GLFW_KEY_1))
	{
		app.rootScene = app.scenes[0];
		printf("scene changed to first\n");
	}

	if(IsKeyPressed(GLFW_KEY_2))
	{
		app.rootScene = app.scenes[1];
		printf("scene changed to second\n");
	}

	if(IsKeyPressed(GLFW_KEY_3))
	{
		app.rootScene = app.scenes[2];
		printf("scene changed to third\n");
	}

	if(IsKeyPressed(GLFW_KEY_4))
	{
		app.rootScene = app.scenes[3];
		printf("scene changed to fourth\n");
	}


}

void Input::keypress_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

	printf("key_callback [%c (%d),%d,%d,%d] \n", key, key, scancode, action, mods);
}

void Input::button_callback(GLFWwindow *window, int button, int action, int mode){
	if (action == GLFW_PRESS)
	{
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
	}
	else
	{

	}
}  

void Input::scroll_callback(GLFWwindow *window, double offsetx, double offsety)
{
	app.cam->SetFov(app.cam->GetFov()+offsety);
}

void Input::resize_callback(GLFWwindow *window, int width, int height)
{
	app.cam->SetAspectRatio(width, height);
	glViewport(0,0,width, height);
}

void Input::cursor_callback(GLFWwindow *window, double x, double y)
{
	if(prevCursor == vec2(-1))
		prevCursor = vec2(x,-y);

	if(glfwGetMouseButton(app.window, GLFW_MOUSE_BUTTON_2))
		app.cam->AddRot((vec2(x,-y) - prevCursor)*sensitivity);
	
	prevCursor = vec2(x,-y);
}
