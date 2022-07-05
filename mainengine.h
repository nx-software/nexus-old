#include "glad/include/glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "object.h"
#include <list>
#ifndef MAINENGINE_H
#define MAINENGINE_H
void mainLoop(const char* name,int width,int height,std::list<object> objects);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
#endif
