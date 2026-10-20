#pragma once

#include "Application.h"

class Application;

typedef glm::vec2 vec2;

extern class Input
{
private:
    static vec2 prevCursor;

public:
    static float sensitivity;

    static void processKeyInputs();
    static bool IsKeyPressed(int GLFWKEY);

    static void keypress_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void button_callback(GLFWwindow* window, int button, int action, int mode);
    static void cursor_callback(GLFWwindow* window, double x, double y);
    static void scroll_callback(GLFWwindow* window, double offsetx, double offsety);
    static void resize_callback(GLFWwindow* window, int width, int height);

} input; 