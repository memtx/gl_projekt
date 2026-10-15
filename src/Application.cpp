#include "Application.h"

#include "models/bushes.h" //models are 3xfloat (pos), 3xfloat (normal)
#include "models/triangle.h"
#include "models/sphere.h" 
#include "models/tree.h"
#include "models/OpenGL.h"
#include "models/plain.h"
#include "models/vsbLogin.h"
#include "models/earth.h"
#include "models/sun.h"
#include "models/moon.h"
#include "models/clock.h"
 
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

	srand(time(NULL));
	deltaTime = glfwGetTime();
    rootScene = nullptr;
	glfwSetKeyCallback(this->window, this->callback_keyPress); //funkce se volá pouze na destinaci. i kdybych dal jen pointer, změnou callback nezměním 

	this->cam = new Camera();
}


void Application::LoadModels() 
{
	models[MDL_TRIANGLE] = new Model(triangle, sizeof(triangle));
	models[MDL_TREE] = new Model(tree, sizeof(tree));	
	models[MDL_LOGIN] = new Model(vsbLogin, sizeof(vsbLogin));
	models[MDL_BUSHES] = new Model(bushes, sizeof(bushes));
	models[MDL_PLAIN] = new Model(plain, sizeof(plain));
	models[MDL_SPHERE] = new Model(sphere, sizeof(sphere));
	models[MDL_EARTH] = new Model(earth, sizeof(earth), L_3COORD3NORMAL3VERTCOLOR);
	models[MDL_SUN] = new Model(sun, sizeof(sun), L_3COORD3NORMAL3VERTCOLOR);
	models[MDL_MOON] = new Model(moon, sizeof(moon), L_3COORD3NORMAL3VERTCOLOR);
	models[MDL_CLOCK] = new Model(clockModel, sizeof(clockModel), L_3COORD3NORMAL3VERTCOLOR);

}

void Application::LoadShaders()
{
	shaders[S_BASE_FRAG] =  new Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	shaders[S_BASE_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/4_true_transformable.vert");
	shaders[S_YELLOW_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/3_yellow.frag");
	shaders[S_COLOR_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/5_transformableColorable.vert");
	shaders[S_MATS_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/6_transfColorProject.vert");
	shaders[S_CLOCK_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/6_clockColorMovementNOVIEW.vert");
	shaders[S_CLOCK_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/6_clockRecolor.frag");

	shaderPrograms[SP_BASIC] = new ShaderProgram(cam,2, shaders[S_BASE_FRAG], shaders[S_BASE_VERTEX]); 
	shaderPrograms[SP_YELLOW] = new ShaderProgram(cam,2, shaders[S_YELLOW_FRAG], shaders[S_BASE_VERTEX]);
	shaderPrograms[SP_VERTCOLOR] = new ShaderProgram(cam,2, shaders[S_BASE_FRAG], shaders[S_COLOR_VERTEX]);
	shaderPrograms[SP_FULLMATS] = new ShaderProgram(cam, 2, shaders[S_BASE_FRAG], shaders[S_MATS_VERTEX]);
	shaderPrograms[SP_CLOCK] = new ShaderProgram(cam, 2, shaders[S_CLOCK_FRAG], shaders[S_CLOCK_VERTEX]);
} 

void Application::LoadObjects()  
{
	controlledTransform = new Transform(vec3(0), vec3(0), vec3(1));
	controlledTransform->Scale(vec3(0.1, 0.1, 0.1))
	;//.Rotate(vec3(-45,0,0));  
  
	for(int i=0; i<4; i++) 
		scenes.push_back(new Scene());

	scenes[0]->AddObject(new DrawableObject(models[MDL_LOGIN], shaderPrograms[SP_BASIC], controlledTransform));
	 
	for(float i=0; i<10; i++)
		scenes[0]->AddObject(new DrawableObject(models[MDL_TREE], shaderPrograms[SP_BASIC], Transform(vec3(rand()%20/10.0f-1,rand()%20/10.0f-1,0.5), vec3(0,rand()%360,0), vec3(0.1))));
	for(float i=0; i<10; i++)
		scenes[0]->AddObject(new DrawableObject(models[MDL_BUSHES], shaderPrograms[SP_BASIC], Transform(vec3(rand()%20/10.0f-1,rand()%20/10.0f-1,0.5), vec3(0,rand()%360, 0), vec3(0.1))));
	scenes[0]->AddObject(new DrawableObject(models[MDL_SPHERE], shaderPrograms[SP_YELLOW], Transform(vec3(0,0.8,1), vec3(0), vec3(0.1))));
	this->rootScene = scenes[0];
 
	DrawableObject *planets = new DrawableObject(models[MDL_SUN], shaderPrograms[SP_VERTCOLOR], DynamicTransform(DT_LINEAR_ROTATE,Transform(vec3(0), vec3(-45,0,0), vec3(0.1)), vec3(0,0.01,0), 36000), std::vector<DrawableObject*> 
	{ 
		new DrawableObject(models[MDL_EARTH], shaderPrograms[SP_VERTCOLOR], DynamicTransform(DT_LINEAR_ROTATE,Transform(vec3(7,0,0), vec3(0), vec3(0.3)), vec3(0,0.02,0), 36000/2), std::vector<DrawableObject*> 
		{
			new DrawableObject(models[MDL_MOON], shaderPrograms[SP_VERTCOLOR], DynamicTransform(DT_LINEAR_ROTATE,Transform(vec3(7,0,0), vec3(0), vec3(0.3)), vec3(0,0.01,0), 36000))
		}),
		new DrawableObject(nullptr,shaderPrograms[SP_BASIC],DynamicTransform(DT_LINEAR_ROTATE,Transform(),vec3(0.2,0,0),360*10), std::vector<DrawableObject*>
		{
			new DrawableObject(models[MDL_LOGIN], shaderPrograms[SP_BASIC], DynamicTransform(DT_LINEAR_ROTATE,Transform(vec3(0,3,0)),vec3(0,0.5,0.5),360*2))
		})
	});
	 
	  
	scenes[1]->AddObject(planets);

	scenes[2]->AddObject(new DrawableObject(models[MDL_TRIANGLE], shaderPrograms[SP_BASIC], Transform().Rotate(vec3(0,0,90)).Translate(vec3(0.5,0,0))));
	scenes[2]->AddObject(new DrawableObject(models[MDL_TRIANGLE], shaderPrograms[SP_BASIC], Transform().Translate(vec3(0.5,0,0)).Rotate(vec3(0,0,90))));
    
	scenes[3]->AddObject(new DrawableObject(models[MDL_CLOCK], shaderPrograms[SP_CLOCK], controlledTransform)); //new DynamicTransform(DT_LINEAR_ROTATE, Transform(vec3(0.5),vec3(0), vec3(0.1)), vec3(0,0,0.01), 360*100)
 
} 

void Application::RunLoop()
{ 
	deltaTime = glfwGetTime(); //todo: fix deltatime 
	int frameCount = 0;

	while (!glfwWindowShouldClose(this->window)) 
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DynamicTransform::UpdateDynamicTransforms(deltaTime);

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