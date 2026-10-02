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
}

GLuint Application::createShaderFromFile(GLenum shaderType, const char* shaderFile)
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
