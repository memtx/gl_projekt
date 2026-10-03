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

float localTransform = 0;
float localScale = 1;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

    switch(key)
    {
        case 'A':
            localTransform -= 1;
            break;
        case 'D': 
            localTransform += 1;
            break;

        case 'W':
            localScale *= 1.1;
            break;
        case 'S':
            localScale /= 1.1;
            break;

    }
        

	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}



void Application::RunLoop()
{
	DrawableObject *Do = new DrawableObject();
	Model *model_tree = new Model(tree, sizeof(tree));

	Shader *fragmentShader = new Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	Shader *vertexShader = new Shader(GL_VERTEX_SHADER, "resources/3_transformable.vert");

	ShaderProgram *sp = new ShaderProgram(2, fragmentShader, vertexShader); 
	DrawableObject *drawObj = new DrawableObject(model_tree, sp);

    glfwSetKeyCallback(window, key_callback);

    rootScene->AddObject(drawObj);

    float localRotation = 0;
	GLint rotLocation = sp->GetVarLocation("rotAngle");
    sp->SetFloat(rotLocation, localRotation);


	GLint transLocation = sp->GetVarLocation("transAmount");
    sp->SetFloat(transLocation, localTransform);

	GLint scaleLocation = sp->GetVarLocation("scaleAmount");
    sp->SetFloat(scaleLocation, localScale);


	while (!glfwWindowShouldClose(this->window)) 
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		if(localRotation > 360)
			localRotation = 0;
		else
			localRotation += 0.01f;


		sp->SetFloat(rotLocation, localRotation);
        sp->SetFloat(scaleLocation, localScale);
        sp->SetFloat(transLocation, localTransform);
        
        rootScene->DrawAllChildren();


		// Display the rendered frame and process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
		 
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}