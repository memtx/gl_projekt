/*
 * Copyright (c) 2026 Martin Němec
 *
 * File: main.cpp
 * Description:  Fixed Function Pipeline.
 */

 #define GLAD_GL_IMPLEMENTATION

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "Application.h"

#include "models/sphere.h"
#include "models/tree.h"


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

/*
//==== cv 1 ======
// Projection matrix : 45degree Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);
*/


int main(void)
{
	Application *app = new Application(); 
	app->Init();

	// Sets the key callback
	glfwSetKeyCallback(app->window, key_callback);
	//glfwSetCursorPosCallback(window, cursor_callback);
	glfwSetMouseButtonCallback(app->window, button_callback);
	glfwSetWindowFocusCallback(app->window, window_focus_callback);
	glfwSetWindowIconifyCallback(app->window, window_iconify_callback);
	glfwSetWindowSizeCallback(app->window, window_size_callback);

	const float points[] = { //pozice (x,y,z, procentuální), barva (procentální) 
	0.0f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	}; 
 
	GLuint VBO_points = 0; //vpodstatě pointer/index na paměť ke které nemáme přístup
	glGenBuffers(1, &VBO_points); //vygeneruje v kontextu místo na ten odkaz, a předá nám ho
	glBindBuffer(GL_ARRAY_BUFFER, VBO_points); //nataví GL_ARRAY_BUFFER v kontextu na odkaz z VBO_points
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); //nastaví do GL_ARRAY_BUFFER (nyní objekt z VBO_points) data a řekne jak se mají používat

	//vertex buffer object (VBO)
	GLuint VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);

	GLuint VBO_2 = 0;
	glGenBuffers(1, &VBO_2); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tree), tree, GL_STATIC_DRAW);

	//============================

	GLuint VAO_points = 0;
	glGenVertexArrays(1, &VAO_points); //vygeneruje odkaz na VAO a napíše ho do VAO_points
	glBindVertexArray(VAO_points);  //nastaví vertex array v kontextu na objekt odkázaný z VAO_points
	glEnableVertexAttribArray(0); // zapne čtení dat. VAO bude mít 2 prvky (nebo listy prvků)
	glEnableVertexAttribArray(1); //druhý atribut je normal vector
	glBindBuffer(GL_ARRAY_BUFFER, VBO_points); //nastaví GL_ARRAY_BUFFER na objekt z VBO_points (je třeba kvůli dřívějším objektům co to nastavily na svoje VBO)
	// index, number of components, data type, normalized, vertex stride (velikost jedné skupiny, např zde 6x float na jeden prvek, takže stride==24), offset od začátku prvku
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (GLvoid*)(3*sizeof(float)));


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
	GLuint vertexShader = app->createShaderFromFile(GL_VERTEX_SHADER, "resources/basic.vert");
	GLuint fragmentShader = app->createShaderFromFile(GL_FRAGMENT_SHADER, "resources/basic.frag");

	GLuint vertexShader_2 = app->createShaderFromFile(GL_VERTEX_SHADER, "resources/green.vert");

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
	while (!glfwWindowShouldClose(app->window))
	{
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO_points);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(points)); //mode, first count
		
 
		/*glUseProgram(shaderProgram);
		glBindVertexArray(VAO_2);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(tree)); //mode,first,count

		glUseProgram(shaderProgram_2);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(sphere));
		*/

		// Display the rendered frame and process events
		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}
	glfwDestroyWindow(app->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

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