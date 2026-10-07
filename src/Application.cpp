#include "Application.h"

#include "models/bushes.h" //models are 3xfloat (pos), 3xfloat (normal)
#include "models/triangle.h"
#include "models/sphere.h" 
#include "models/tree.h"
#include "models/OpenGL.h"
#include "models/plain.h"
#include "../vsbLogin.h"

Application::~Application()
{
	for(auto o : models)
		delete o;

	for(auto o : shaders)
		delete o;

	for(auto o : shaderPrograms)
		delete o;	

	for(auto o : scenes)
		delete o;
}

void Application::Init(int width, int height, const char *windowName)
{
	//==== GL INIT ====

    // Initialize GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Initialization of a specific version
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, 
	GLFW_OPENGL_CORE_PROFILE);  //*/


	this->window = glfwCreateWindow(width, height, windowName, NULL, NULL);
	if (!this->window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE); 
	}

    glfwMakeContextCurrent(this->window);
	glfwSwapInterval(0); //1 for vsync, 0 for none (or to fix lag)

    // Initialize GLAD and load OpenGL function pointers
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		//return -1;
        exit(EXIT_FAILURE);
	}

	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
 
    glEnable(GL_DEPTH_TEST);

	//==== APP INIT ====

	deltaTime = glfwGetTime();
    rootScene = nullptr;
    glfwSetKeyCallback(this->window, this->callback_keyPress); //funkce se volá pouze na destinaci. i kdybych dal jen pointer, změnou callback nezměním 
	
}


void Application::LoadModels() 
{
	models[M_TRIANGLE] = new Model(triangle, sizeof(triangle));
	models[M_TREE] = new Model(tree, sizeof(tree));	
	models[M_LOGIN] = new Model(vsbLogin, sizeof(vsbLogin));
	models[M_BUSHES] = new Model(bushes, sizeof(bushes));
	models[M_PLAIN] = new Model(plain, sizeof(plain));
	models[M_SPHERE] = new Model(sphere, sizeof(sphere));

}

void Application::LoadShaders()
{
	shaders[S_BASE_FRAG] =  new Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	shaders[S_BASE_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/4_true_transformable.vert");
	shaders[S_YELLOW_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/3_yellow.frag");

	shaderPrograms[SP_BASIC] = new ShaderProgram(2, shaders[S_BASE_FRAG], shaders[S_BASE_VERTEX]); 
	shaderPrograms[SP_YELLOW] = new ShaderProgram(2, shaders[S_YELLOW_FRAG], shaders[S_BASE_VERTEX]);
}

void Application::LoadObjects()
{
	controlledTransform = new Transform(vec3(0), vec3(0), vec3(1));

	for(int i=0; i<4; i++) 
		scenes.push_back(new Scene());

	controlledTransform->Scale(vec3(0.1, 0.1, 0.1));
	scenes[0]->AddObject(new DrawableObject(models[M_LOGIN], shaderPrograms[SP_BASIC], controlledTransform));
	
	for(float i=-1; i<1; i+= 0.2)
		scenes[0]->AddObject(new DrawableObject(models[M_TREE], shaderPrograms[SP_BASIC], Transform(vec3(i,0,0.5), vec3(0), vec3(0.1))));
	for(float i=-1+0.1; i<1-0.2; i+= 0.2)
		scenes[0]->AddObject(new DrawableObject(models[M_BUSHES], shaderPrograms[SP_BASIC], Transform(vec3(i,0,0.5), vec3(0), vec3(0.1))));


	scenes[0]->AddObject(new DrawableObject(models[M_SPHERE], shaderPrograms[SP_YELLOW], Transform(vec3(0,0.8,1), vec3(0), vec3(0.1)))); 

	this->rootScene = scenes[0];
	scenes[1]->AddObject(new DrawableObject(models[M_TREE], shaderPrograms[SP_BASIC], Transform(vec3(0), vec3(0), vec3(0.1))));

}

void Application::RunLoop()
{
	deltaTime = glfwGetTime();
	int frameCount = 0;

	while (!glfwWindowShouldClose(this->window)) 
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        if(callback_preDraw)
            callback_preDraw();

        if(rootScene)
            rootScene->DrawAll(); //recursive
        
        if(callback_postDraw)
            callback_postDraw();

		// Display the rendered frame and process events
		glfwSwapBuffers(this->window);

		glfwPollEvents();

        // FPS counter
        frameCount++;
        double now = glfwGetTime();
        if (now - deltaTime >= 1.0)
        {
            printf("FPS: %d\n", frameCount);
            frameCount = 0;
            deltaTime = now;
        }

	}
		 
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}