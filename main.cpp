/*
3D Engine v0.0.1
By:
Chinmay Tiwari
(add other contribuiters here)
*/
#include <iostream>
#include "glad/src/glad.c"
#include "glad/include/glad/glad.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//testing models and inputs
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
}; 
const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in ve3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
int main(){
	std::cout<<"3D Engine\n";
	/*
	Initilize
	*/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Create window
	GLFWwindow* window = glfwCreateWindow(800,600,"3D Engine Test",NULL,NULL);
	if(window == NULL){
		std::cout<<"Fatal: Engine failed to create GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fatal: Engine failed to initialize GLAD" << std::endl;
		return -1;
	}  
	//OpenGL viewport
	glViewport(0,0,800,600);
	//render buffer stuff
	unsigned int VBO;
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices, GL_STATIC_DRAW);
	//shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//main loop
	while(!glfwWindowShouldClose(window)){
		processInput(window);
		//Renderr
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glfwStuff
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0,width,height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
}
void processInput(GLFWwindow *window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
}