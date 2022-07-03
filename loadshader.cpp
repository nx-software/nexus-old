#include "loadshader.h"
#include <iostream>
#include <fstream>
#include <string>
#include "glad/include/glad/glad.h"

void loadShaders(std::string vertPath, std::string fragPath) {
	// load vertex shader from file
	std::ifstream vert;
	vert.open(vertPath);
	if (!vert.is_open()) {
		std::cout << "Error opening vertex shader\n";
		return;
	}
	std::string vString;
	std::ostringstream str;
	str << vert.rdbuf();
	vString = str.str();
	// set up vertex shader
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &(vString.c_str()), NULL);
	glCompileShader(vertexShader);

	// load fragment shader from file
	std::ifstream frag;
	frag.open(vertPath);
	if (!frag.is_open()) {
		std::cout << "Error opening fragment shader\n";
		return;
	}
	std::string fString;
	std::ostringstream fstr;
	fstr << vert.rdbuf();
	vString = fstr.str();
	// set up vertex shader
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &(fString.c_str()), NULL);
	glCompileShader(fragmentShader);
}
