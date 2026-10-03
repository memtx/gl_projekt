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

    rootScene = new Scene();
}

DrawableObject *drawObj;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

    switch(key)
    {
        case 'A':
            drawObj->transform->pos.x -= 1;
            break;
        case 'D': 
            drawObj->transform->pos.x += 1;
            break;

        case 'W':
            drawObj->transform->scale *= 1.1;
            break;
        case 'S':
            drawObj->transform->scale /= 1.1;
            break;

    }
        

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}



void Application::RunLoop()
{
	Model *model_tree = new Model(tree, sizeof(tree));
 
	Shader *fragmentShader = new Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	Shader *vertexShader = new Shader(GL_VERTEX_SHADER, "resources/3_transformable.vert");

	ShaderProgram *sp = new ShaderProgram(2, fragmentShader, vertexShader); 
	Transform tr(glm::vec3(0));
        printf("%f\n",tr.scale.x);
    drawObj = new DrawableObject(model_tree, sp, &tr);

    glfwSetKeyCallback(window, key_callback);

    rootScene->AddObject(drawObj);


	while (!glfwWindowShouldClose(this->window)) 
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		if(drawObj->transform->rot.x > 360)
			drawObj->transform->rot.x = 0;
		else
			drawObj->transform->rot.x += 0.01f;


        rootScene->DrawAllChildren();


		// Display the rendered frame and process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
		 
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}