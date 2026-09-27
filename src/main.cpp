/*
 * Copyright (c) 2026 Martin Němec
 *
 * File: main.cpp
 * Description:  Fixed Function Pipeline.
 */


//opengl minimálně 3.3, ideálně 4.6


//include glad
//#include <glad/include/glad/glad.h>
#define GLAD_GL_IMPLEMENTATION
#include <glad/include/glad/gl.h>

//Include GLFW  
#include <GLFW/glfw3.h>  
//Include GLM    
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//#include "./glutils.h"

#include "models/sphere.h"
#include "models/tree.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>


static void error_callback(int error, const char* description){ fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

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

//GLM test

// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);


GLuint createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
	// Creates an empty shader
	GLuint shaderID = glCreateShader(shaderType);

	if (shaderID == 0)
	{
		std::cout << "Unable to create shader" << std::endl;
		exit(EXIT_FAILURE);
	}

	//Loading the contents of a file into a variable
	std::ifstream file(shaderFile);
	if (!file.is_open())
	{
		std::cout << "Unable to open file " << shaderFile << std::endl;
		glDeleteShader(shaderID);
		exit(-1);
	}
	std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Set the shader source code
	const char* source = shaderCode.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);

	// Compile the shader source code
	glCompileShader(shaderID);

	// Check specialization/compilation status
	GLint success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
		std::cout
			<< "Shader failed:\n"
			<< infoLog << std::endl;
		glDeleteShader(shaderID);
		exit(1);
	}
	return shaderID;
}


int main(void)
{
	// Pointer to the GLFW window
	GLFWwindow* window;

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


	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Initialize GLAD and load OpenGL function pointers
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		printf("GLAD initialization failed\n");
		return -1;
	}

	// Get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);


	/*float points[] = {
	0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};*/

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);

	GLuint VBO_2 = 0;
	glGenBuffers(1, &VBO_2); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	GLuint VAO_2 = 0;
	glGenVertexArrays(1, &VAO_2); //generate the VAO
	glBindVertexArray(VAO_2); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
	// index, number of components, data type, normalized, vertex stride, offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

	// Create and compile the vertex and fragment shaders
	GLuint vertexShader = createShaderFromFile(GL_VERTEX_SHADER, "resources/basic.vert");
	GLuint fragmentShader = createShaderFromFile(GL_FRAGMENT_SHADER, "resources/basic.frag");

	GLuint vertexShader_2 = createShaderFromFile(GL_VERTEX_SHADER, "resources/green.vert");

	//Create and link the shader program 
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	GLuint shaderProgram_2 = glCreateProgram();
	glAttachShader(shaderProgram_2, fragmentShader);
	glAttachShader(shaderProgram_2, vertexShader_2);
	glLinkProgram(shaderProgram_2);

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO_2);

		// Draw
		glDrawArrays(GL_TRIANGLES, 0, sizeof(tree)); //mode,first,count

		glUseProgram(shaderProgram_2);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(sphere));

		// Display the rendered frame and process events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	/* ================= druhy ===========================
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwWindowHint( GLFW_SAMPLES, 8 );
	glfwWindowHint( GLFW_RESIZABLE, GL_TRUE );
	glfwWindowHint( GLFW_DOUBLEBUFFER, GL_TRUE );
	
		window = glfwCreateWindow(640, 480, "ZPG", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	// Sets the key callback
	glfwSetKeyCallback(window, key_callback);
	//glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(window, button_callback);
	glfwSetWindowFocusCallback(window, window_focus_callback);
	glfwSetWindowIconifyCallback(window, window_iconify_callback);
	glfwSetWindowSizeCallback(window, window_size_callback);

	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	
	//=============
		if ( !gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress ) )
	{
		if ( !gladLoadGL() )
		{
			return EXIT_FAILURE;
		}
	}

	glEnable( GL_DEBUG_OUTPUT );
	glDebugMessageCallback( gl_callback, nullptr );

	printf( "OpenGL %s, ", glGetString( GL_VERSION ) );
	printf( "%s", glGetString( GL_RENDERER ) );
	printf( " (%s)\n", glGetString( GL_VENDOR ) );
	printf( "GLSL %s\n", glGetString( GL_SHADING_LANGUAGE_VERSION ) );

	glEnable( GL_MULTISAMPLE );

	// map from the range of NDC coordinates <-1.0, 1.0>^2 to <0, width> x <0, height>
	glViewport( 0, 0, width, height );
	// GL_LOWER_LEFT (OpenGL) or GL_UPPER_LEFT (DirectX, Windows) and GL_NEGATIVE_ONE_TO_ONE or GL_ZERO_TO_ONE
	glClipControl( GL_UPPER_LEFT, GL_NEGATIVE_ONE_TO_ONE );

	// setup vertex buffer as AoS (array of structures)
	GLfloat vertices[] =
	{
		-0.9f, 0.9f, 0.0f,  0.0f, 1.0f, // vertex 0 : p0.x, p0.y, p0.z, t0.u, t0.v
		0.9f, 0.9f, 0.0f,   1.0f, 1.0f, // vertex 1 : p1.x, p1.y, p1.z, t1.u, t1.v
		0.0f, -0.9f, 0.0f,  0.5f, 0.0f  // vertex 2 : p2.x, p2.y, p2.z, t2.u, t2.v
	};
	const int no_vertices = 3;
	const int vertex_stride = sizeof( vertices ) / no_vertices;
	// optional index array
	unsigned int indices[] =
	{
		0, 1, 2
	};

	GLuint vao = 0;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	GLuint vbo = 0;
	glGenBuffers( 1, &vbo ); // generate vertex buffer object (one of OpenGL objects) and get the unique ID corresponding to that buffer
	glBindBuffer( GL_ARRAY_BUFFER, vbo ); // bind the newly created buffer to the GL_ARRAY_BUFFER target
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW ); // copies the previously defined vertex data into the buffer's memory
	// vertex position
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, vertex_stride, 0 );
	glEnableVertexAttribArray( 0 );
	// vertex texture coordinates
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, vertex_stride, ( void * )( sizeof( float ) * 3 ) );
	glEnableVertexAttribArray( 1 );
	GLuint ebo = 0; // optional buffer of indices
	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

	GLuint vertex_shader = glCreateShader( GL_VERTEX_SHADER );
	std::vector<char> shader_source;
	
	char cwd[PATH_MAX];
   if (getcwd(cwd, sizeof(cwd)) != NULL)
       printf("Current working dir: %s\n", cwd);
	
	if ( LoadShader( "resources/basic_shader.vert", shader_source ) == S_OK )
	{
		const char * tmp = static_cast< const char * >( &shader_source[0] );
		glShaderSource( vertex_shader, 1, &tmp, nullptr );
		glCompileShader( vertex_shader );
	}
	CheckShader( vertex_shader );

	GLuint fragment_shader = glCreateShader( GL_FRAGMENT_SHADER );
	if ( LoadShader( "resources/basic_shader.frag", shader_source ) == S_OK )
	{
		const char * tmp = static_cast< const char * >( &shader_source[0] );
		glShaderSource( fragment_shader, 1, &tmp, nullptr );
		glCompileShader( fragment_shader );
	}
	CheckShader( fragment_shader );

	GLuint shader_program = glCreateProgram();
	glAttachShader( shader_program, vertex_shader );
	glAttachShader( shader_program, fragment_shader );
	glLinkProgram( shader_program );
	
	// TODO check linking
	glUseProgram( shader_program );

	glPointSize( 10.0f );
	glLineWidth( 1.0f );
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	// main loop
	while ( !glfwWindowShouldClose( window ) )
	{
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f ); // state setting function
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT ); // state using function

		GLint viewport[4];
		glGetIntegerv( GL_VIEWPORT, viewport );		
		glm::mat4 P = glm::mat4( 1.0f );

		//P.set( 0, 0, float( std::min( viewport[2], viewport[3] ) ) / viewport[2] );
		//P.set( 1, 1, float( std::min( viewport[2], viewport[3] ) ) / viewport[3] );		
		P[0][0] = 100 * 2.0f / viewport[2];		
		P[1][1] = 100 * 2.0f / viewport[3];
		SetMatrix4x4( shader_program, glm::value_ptr( P ), "P" );

		glBindVertexArray( vao );

		glDrawArrays( GL_POINTS, 0, 3 );
		glDrawArrays( GL_LINE_LOOP, 0, 3 );
		glDrawArrays( GL_TRIANGLES, 0, 3 );
		//glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 ); // optional - render from an index buffer

		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	glDeleteShader( vertex_shader );
	glDeleteShader( fragment_shader );
	glDeleteProgram( shader_program );

	glDeleteBuffers( 1, &vbo );
	glDeleteVertexArrays( 1, &vao );

	glfwTerminate();

	return EXIT_SUCCESS;
	*/
	/*
	===================== první ============================
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, -0.0f, 0.f, -1.0f);
		
		glBegin(GL_TRIANGLES);
			glColor3f(1.f, 1.f, 0.f);
			glVertex3f(-0.6f, -0.4f, 0.f);

			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, 0.4f, 0.f);

			//===============
			glColor3f(1.f, 0.f, 1.f);
			glVertex3f(0.6f, 0.4f, 0.f);

			glColor3f(0.f, 1.f, 0.f);
			glVertex3f(0.6f, -0.4f, 0.f);

			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(-0.6f, 0.4f, 0.f);



		glEnd();
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	*/
}