#include "Shader.h"


Shader::Shader(GLenum GL_TYPEOF_SHADER, const char* shaderFile) 
 : GL_TYPEOF_SHADER(GL_TYPEOF_SHADER), id(glCreateShader(GL_TYPEOF_SHADER))
{
    // Creates an empty shader
    //id = glCreateShader(GL_TYPEOF_SHADER);

    if (id <= 0)
    {
        std::cout << "Unable to create shader" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Loading the contents of a file into a variable
    std::ifstream file(shaderFile);
    if (!file.is_open())
    {
        std::cout << "Unable to open file " << shaderFile << std::endl;
        glDeleteShader(id);
        exit(-1);
    }
    std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Set the shader source code
    const char* source = shaderCode.c_str();
    glShaderSource(id, 1, &source, nullptr);

    // Compile the shader source code
    glCompileShader(id);

    // Check specialization/compilation status
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[1024];
        glGetShaderInfoLog(id, sizeof(infoLog), nullptr, infoLog);
        std::cout
            << "Shader failed:\n"
            << infoLog << std::endl;
        glDeleteShader(id);
        exit(1);
    }

}
/*
GLuint Shader::GetRef()
{
    if(ref <= 0)
    { printf("ERROR: tried to use invalid shader (%d)\n", ref);}

    return ref;
}
    */