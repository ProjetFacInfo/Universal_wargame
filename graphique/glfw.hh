#pragma once

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>


GLFWwindow* glfw_init(int major_ver, int minor_ver, int width, int height, bool is_full_screen, const char* title);
void debugCallback
(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userparam);
