#include "Application.h"

void Application::Init(int width, int height, const char *windowName)
{
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
	glfwSwapInterval(1);

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

    rootScene = nullptr;
    glfwSetKeyCallback(this->window, this->callback_keyPress); //funkce se volá pouze na destinaci. i kdybych dal jen pointer, změnou callback nezměním 
}

void Application::RunLoop()
{

	while (!glfwWindowShouldClose(this->window)) 
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        if(callback_preDraw)
            callback_preDraw();

        if(rootScene)
            rootScene->DrawAllChildren(); //recursive
        
        if(callback_postDraw)
            callback_postDraw();

		// Display the rendered frame and process events
		glfwSwapBuffers(window);

		glfwPollEvents();
	}
		 
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}