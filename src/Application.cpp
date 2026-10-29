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
#include "../../dino.h"
//#include "models/dino.h"

#include "models/suzi_flat.h"
#include "models/suzi_smooth.h"

 
Application::~Application() 
{
	for(auto o : models)
		delete o;
		
	for(auto o : shaders)
		delete o;

	for(auto o : shaderPrograms)
		delete o;	

	for(auto o : materials)
		delete o;

	for(auto o : scenes)
		delete o;

	delete controlledTransform;
	delete Material::defaultMat;
}

void Application::Init(int width, int height, float fov, const char *windowName)
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
	this->cam = new Camera(vec3(0,5,0), vec3(0), vec2(width, height), 60.0f);

	this->window = glfwCreateWindow(cam->GetAspectRatio().x, cam->GetAspectRatio().y, windowName, NULL, NULL);
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
    rootScene = nullptr;

	glfwSetCursorPosCallback(this->window, input.cursor_callback);
	glfwSetKeyCallback(this->window, input.keypress_callback); //callback is set so I can't change it later, even with a pointer
	glfwSetMouseButtonCallback(this->window, input.button_callback);
	glfwSetWindowSizeCallback(this->window, input.resize_callback);
	glfwSetScrollCallback(this->window, input.scroll_callback);
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
	models[MDL_DINO] = new Model(dino, sizeof(dino), L_3COORD3NORMAL3VERTCOLOR);
	models[MDL_SUZY_FLAT] = new Model(suziFlat, sizeof(suziFlat), L_3COORD3NORMAL);
	models[MDL_SUZY_SMOOTH] = new Model(suziSmooth, sizeof(suziSmooth), L_3COORD3NORMAL);
}

void Application::LoadShaders()
{
	shaders[S_BASE_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/1_basic.frag");
	shaders[S_MATS_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/6_transfColorCamera.vert");
	shaders[S_MATSNORMAL_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/6_transfNormalCamera.vert");
	shaders[S_CLOCK_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/6_clockColorCamera.vert");
	shaders[S_TREE_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/6_transfTreeSplit.vert");
	shaders[S_LIGHTABLE_VERTEX] = new Shader(GL_VERTEX_SHADER, "resources/7_lightable.vert");
	shaders[S_AMBIENT_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/7_ambient.frag");
	shaders[S_DIFFUSE_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/7_diffuse.frag");
	shaders[S_PHONG_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/7_phong.frag");
	shaders[S_BLINNPHONG_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/7_blinnPhong.frag");
	shaders[S_REFLECTOR_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/7_reflector.frag");
	shaders[S_BPDISTANCE_FRAG] = new Shader(GL_FRAGMENT_SHADER, "resources/8_BPAttenuation.frag");

	shaderPrograms[SP_FULLMATS] = new ShaderProgram(cam, 2, shaders[S_BASE_FRAG], shaders[S_MATS_VERTEX]);
	shaderPrograms[SP_FULLMATSNORMAL] = new ShaderProgram(cam, 2, shaders[S_BASE_FRAG], shaders[S_MATSNORMAL_VERTEX]);
	shaderPrograms[SP_CLOCK] = new ShaderProgram(cam, 2, shaders[S_BPDISTANCE_FRAG], shaders[S_CLOCK_VERTEX]);
	shaderPrograms[SP_TREESPLIT] = new ShaderProgram(cam, 2, shaders[S_BASE_FRAG], shaders[S_TREE_VERTEX]);
	shaderPrograms[SP_AMBIENT] = new ShaderProgram(cam, 2, shaders[S_AMBIENT_FRAG], shaders[S_LIGHTABLE_VERTEX]);
	shaderPrograms[SP_DIFFUSE] = new ShaderProgram(cam, 2, shaders[S_DIFFUSE_FRAG], shaders[S_LIGHTABLE_VERTEX]);
	shaderPrograms[SP_PHONG] = new ShaderProgram(cam, 2, shaders[S_PHONG_FRAG], shaders[S_LIGHTABLE_VERTEX]);
	shaderPrograms[SP_BLINNPHONG] = new ShaderProgram(cam, 2, shaders[S_BLINNPHONG_FRAG], shaders[S_LIGHTABLE_VERTEX]);
	shaderPrograms[SP_REFLECTOR] = new ShaderProgram(cam, 2, shaders[S_REFLECTOR_FRAG], shaders[S_LIGHTABLE_VERTEX]);
	shaderPrograms[SP_BPDISTANCE] = new ShaderProgram(cam, 2, shaders[S_BPDISTANCE_FRAG], shaders[S_LIGHTABLE_VERTEX]);
	shaderPrograms[SP_BPTREE] =  new ShaderProgram(cam, 2, shaders[S_BPDISTANCE_FRAG], shaders[S_TREE_VERTEX]);
} 


void Application::LoadMaterials()
{
	materials[MAT_FULLBRIGHT_TEXTURED] = (new Material())
		->AddProperty("ambientStrength", 1.0f)
		->AddProperty("objectColor", vec3(-2));

	materials[MAT_FULLBRIGHT_COLORED] = (new Material())
		->AddProperty("ambientStrength", 1.0f)
		->AddProperty("objectColor", vec3(0.3));
	
	materials[MAT_PHONG] = (new Material())
		->AddProperty("ambientStrength", 0.3f)
		->AddProperty("objectColor", vec3(0.3f))
		->AddProperty("specularStrength", 1.0f)
		->AddProperty("specularPower", 8);

	materials[MAT_BLINNPHONG] = (new Material())
		->AddProperty("ambientStrength", 0.3f)
		->AddProperty("objectColor", vec3(0.3f))
		->AddProperty("specularStrength", 1.0f)
		->AddProperty("specularPower", 1);

	materials[MAT_REFLECTOR] = (new Material()) 	//cool effect, see .frag for details
		->AddProperty("ambientStrength", 0.3f)
		->AddProperty("objectColor", vec3(0.3f))
		->AddProperty("specularStrength", 0.5f)
		->AddProperty("specularPower", 32);

	materials[MAT_DIFFUSE] = (new Material())
		->AddProperty("ambientStrength", 0.3f)
		->AddProperty("objectColor", vec3(0.3f));

	materials[MAT_BPATTENUATION] = (new Material())
		->AddProperty("ambientStrength", 0.3f)
		->AddProperty("objectColor", vec3(-2))
		->AddProperty("specularStrength", 0.5f)
		->AddProperty("specularPower", 16)
		->AddProperty("attenuationFactors", vec3(1,0.09, 0.332));

	materials[MAT_BPATTENUATION_GREEN] = (new Material())
		->AddProperty("ambientStrength", 0.3f)
		->AddProperty("objectColor", vec3(0.1,0.9,0.1))
		->AddProperty("specularStrength", 0.5f)
		->AddProperty("specularPower", 8)
		->AddProperty("attenuationFactors", vec3(1,0.09, 0.332));

	materials[MAT_BPATTENUATION_NORM] = (new Material())
		->AddProperty("ambientStrength", 0.3f)
		->AddProperty("objectColor", vec3(-3))
		->AddProperty("specularStrength", 0.5f)
		->AddProperty("specularPower", 16)
		->AddProperty("attenuationFactors", vec3(1,0.09, 0.332));

	//Material::defaultMat->AddProperty("ambientStrength", 1.0f);
	//Material::defaultMat->AddProperty("objectColor", vec3(0.3f)); //-1 for default, aka purple (1,0,1)

}


void Application::LoadObjects()  
{
	
	//======== special transforms ===========

	controlledTransform = new Transform(vec3(0,0,0), vec3(0), vec3(1));
	controlledTransform->Scale(vec3(0.1));
	//.Rotate(vec3(-45,0,0));  
	
	controlledTransform->onChange = [](Transform* t)
	{ 
		for(auto sp : app.shaderPrograms)
			sp->SetGlobalLightPos(t->GetPos()); 
	};
	controlledTransform->onChange(controlledTransform);

	//========== objects =============


	for(int i=0; i<4; i++) 
		scenes.push_back(new Scene());
	this->rootScene = scenes[0];

	scenes[0]->AddObject(new DrawableObject(models[MDL_LOGIN], shaderPrograms[SP_BPDISTANCE], DynamicTransform(DT_LINEAR_ROTATE, Transform(vec3(4,1,0)),vec3(0,0,0),72), materials[MAT_BPATTENUATION_GREEN]));

	for(float i=0; i<30; i++) 
		scenes[0]->AddObject(new DrawableObject(models[MDL_TREE], shaderPrograms[SP_BPTREE], Transform(vec3(rand()%200/10.0f-10, 0 ,rand()%200/10.0f-10), vec3(0,rand()%360,0), vec3(2)), materials[MAT_BPATTENUATION]));
	for(float i=0; i<70; i++)
		scenes[0]->AddObject(new DrawableObject(models[MDL_BUSHES], shaderPrograms[SP_BPDISTANCE], Transform(vec3(rand()%200/10.0f-10, 0  ,rand()%200/10.0f-10), vec3(0,rand()%360, 0), vec3(3)), materials[MAT_BPATTENUATION_GREEN]));

	scenes[0]->AddObject(new DrawableObject(models[MDL_PLAIN], shaderPrograms[SP_BPDISTANCE], Transform(vec3(0), vec3(0), vec3(100,1,100)), materials[MAT_BPATTENUATION_GREEN]));

	scenes[0]->AddObject(new DrawableObject(models[MDL_CLOCK], shaderPrograms[SP_CLOCK], Transform(vec3(1,1,1), vec3(45,45,45), vec3(0.5)), materials[MAT_BPATTENUATION]));
	scenes[0]->AddObject(new DrawableObject(models[MDL_SUN], shaderPrograms[SP_AMBIENT], controlledTransform, materials[MAT_FULLBRIGHT_TEXTURED]));
	//scenes[0]->AddObject(new DrawableObject(models[MDL_SPHERE], shaderPrograms[SP_FULLMATSNORMAL], Transform(vec3(10,0,0))));
	//scenes[0]->AddObject(new DrawableObject(models[MDL_SPHERE], shaderPrograms[SP_FULLMATSNORMAL], Transform(vec3(0,10,0))));
	//scenes[0]->AddObject(new DrawableObject(models[MDL_SPHERE], shaderPrograms[SP_FULLMATSNORMAL], Transform(vec3(0,0,10))));

	scenes[0]->AddObject(new DrawableObject(models[MDL_DINO], shaderPrograms[SP_BPDISTANCE], Transform(vec3(6,-3,5),vec3(0,80,0), vec3(1,8,1)),materials[MAT_BPATTENUATION_NORM] ));

	scenes[1]->AddObject(new DrawableObject(models[MDL_SUN], shaderPrograms[SP_AMBIENT], controlledTransform, materials[MAT_FULLBRIGHT_TEXTURED]));
	scenes[1]->AddObject(new DrawableObject(models[MDL_SUZY_FLAT], shaderPrograms[SP_PHONG], Transform(vec3(2,0,0), vec3(0,180,0)), materials[MAT_PHONG])); //right
	scenes[1]->AddObject(new DrawableObject(models[MDL_SUZY_FLAT], shaderPrograms[SP_BPDISTANCE], Transform(vec3(-2,0,0), vec3(0,180,0)), materials[MAT_BLINNPHONG])); //left
	scenes[1]->AddObject(new DrawableObject(models[MDL_SUZY_FLAT], shaderPrograms[SP_BLINNPHONG], Transform(vec3(0,2,0), vec3(0,90,0)), materials[MAT_BLINNPHONG])); //up
	scenes[1]->AddObject(new DrawableObject(models[MDL_SUZY_FLAT], shaderPrograms[SP_DIFFUSE], Transform(vec3(0,-2,0), vec3(0,180,0)), materials[MAT_DIFFUSE])); //down

	scenes[1]->AddObject(new DrawableObject(models[MDL_SPHERE], shaderPrograms[SP_BLINNPHONG], Transform(vec3(0,0,2), vec3(0,180,0)), materials[MAT_BLINNPHONG]));

	DrawableObject *planets = new DrawableObject(models[MDL_SUN], shaderPrograms[SP_AMBIENT], DynamicTransform(DT_LINEAR_ROTATE,Transform(vec3(0,0,0), vec3(-45,0,0), vec3(0.5)), vec3(0,0.1,0), 3600), materials[MAT_FULLBRIGHT_TEXTURED], std::vector<DrawableObject*> 
	{ 
		new DrawableObject(models[MDL_EARTH], shaderPrograms[SP_BLINNPHONG], DynamicTransform(DT_LINEAR_ROTATE,Transform(vec3(7,0,0), vec3(0), vec3(0.3)), vec3(0,0.2,0), 3600/2), materials[MAT_BLINNPHONG], std::vector<DrawableObject*> 
		{
			new DrawableObject(models[MDL_MOON], shaderPrograms[SP_BLINNPHONG], DynamicTransform(DT_LINEAR_ROTATE,Transform(vec3(7,0,0), vec3(0), vec3(0.3)), vec3(0,0.1,0), 3600),  materials[MAT_BLINNPHONG])
		}),
		new DrawableObject(nullptr, shaderPrograms[SP_BLINNPHONG], DynamicTransform(DT_LINEAR_ROTATE, Transform(vec3(3,0,0)),vec3(0.1,0,0),3600), materials[MAT_BLINNPHONG],
		{
			new DrawableObject(models[MDL_DINO], shaderPrograms[SP_BLINNPHONG], DynamicTransform(DT_LINEAR_ROTATE,Transform(), vec3(0,1,0), 360), materials[MAT_BPATTENUATION])
		})
	}); 
	scenes[2]->AddObject(planets);
} 

void Application::RunLoop()
{ 
	int frameCount = 0;
	float lastFrame = glfwGetTime();
	float fpsCounterTimer = 0;

	while (!glfwWindowShouldClose(this->window)) 
	{
		logger.ResetPerFrameCounters();
 
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;  

		
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DynamicTransform::UpdateDynamicTransforms(deltaTime);

		DrawableObject::ClearActiveShader();

		input.processKeyInputs();

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
        
		//once per second
        if ((fpsCounterTimer += deltaTime) >= 1 )
        {
			fpsCounterTimer = 0;
            printf("FPS: %d\n", frameCount);
			logger.PrintCounters();
			frameCount = 0;
        }


	}
		 
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}