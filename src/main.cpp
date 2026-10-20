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

int main(void)
{
	app.Init(800, 600, 60.0f, "ZPG Projekt");

	app.LoadModels();
	app.LoadShaders();
	app.LoadObjects();

	app.RunLoop();
}