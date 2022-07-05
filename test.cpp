#include "headers/mainengine.h"
#include <iostream>
#include <fstream>
#include <string>
int main(){
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    std::list<object> objects;
    texture need("/bliss.jpg",0,0,0);
    object real(vertices, "/root/AOPENGLENGINE/shaders/vshader.v","/root/AOPENGLENGINE/shaders/fshader.f",indices,need.data);
    objects.push_back(real);
    mainLoop("Nexus Engine Test v0.0.1",600,800,objects);
}
