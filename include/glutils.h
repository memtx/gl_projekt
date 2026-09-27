#ifndef GL_UTILS_H_
#define GL_UTILS_H_
#endif

#define S_FALSE 0
#define S_OK 1

#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define GLM_ENABLE_EXPERIMENTAL
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <filesystem>
//#include <winerror.h> // just for S_OK and S_FALSE

// Glad 2 - multi-language Vulkan/GL/GLES/EGL/GLX/WGL loader-generator
//#include <glad/include/glad/glad.h>
#include <glad/include/glad/gl.h>
 

// GLFW 3.4 - simple API for creating windows, receiving input and events
#include <GLFW/glfw3.h>

// EnTT v3.15.0 - entity-component system
#include <entt/entt.hpp> 
/*
#include "color.h"
#include "texture.h"
#include "meshloader.h"*/

//bool check_gl( const GLenum error = glGetError() );

void glfw_callback( const int error, const char * description );
void GLAPIENTRY gl_callback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * user_param );
void framebuffer_resize_callback( GLFWwindow * window, int width, int height );
int LoadShader( const std::string & file_name, std::vector<char> & shader );
std::string LoadAsciiFile( const std::string & file_name );
GLint CheckShader( const GLenum shader );

void SetInt( const GLuint program, GLint value, const char * int_name );
void SetSampler( const GLuint program, GLenum texture_unit, const char * sampler_name );
void SetMatrix4x4( const GLuint program, const GLfloat * data, const char * matrix_name );
void SetVector3( const GLuint program, const GLfloat * data, const char * vector_name );
void SetVector2( const GLuint program, const GLfloat * data, const char * vector_name );
