#include "headers/mainengine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "headers/stb_image.h"
#include "headers/camera.h"
#include "headers/shader.h"
// #include "../glm/glm.hpp"
// #include "../glm/gtc/matrix_transform.hpp"
// #include "../glm/gtc/type_ptr.hpp"
#include "headers/transform.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//template<class obj>
int basedwidth, basedheight, nrChannels;
unsigned char *data = stbi_load("wall.jpg", &basedwidth, &basedheight, &nrChannels, 0); 

Camera cam(glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f,0.0f,3.0f),glm::vec3(0.0f, 1.0f,  0.0f),glm::vec3(0.0f, 0.0f, -1.0f));

void mainLoop(const char* name,int width,int height,std::list<object> objects){
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(height,width,name,NULL,NULL);
	if(window == NULL){
		std::cout<<"Fatal: Engine failed to create GLFW" << std::endl;
		glfwTerminate();	
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fatal: Engine failed to initialize GLAD" << std::endl;
	}  
    glViewport(0,0,height,width);
    int i;
    unsigned int VBO, VAO;//, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    //texture
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    std::list<object>::iterator it = objects.begin();
    std::list<Shader> shaders;
    for(i=0;i<objects.size();i++){
        std::cout<<"Loop"<<std::endl;
        object based = *it;
        Shader shadereal(based.vertexShaderPath, based.fragShaderPath);
        shaders.push_back(shadereal);
        //link vertex attribuites
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(based.vertices), based.vertices, GL_STATIC_DRAW);
        
        // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(based.indices), based.indices, GL_STATIC_DRAW);



        //pos
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        //colors
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        //glEnableVertexAttribArray(1);
        //tex
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //texure
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
  
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, basedwidth, basedheight, 0, GL_RGB, GL_UNSIGNED_BYTE, based.data);
            std::cout << "Texture Loaded." << std::endl;
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        
        advance(it, 1);

    }
     std::cout<<"Readying Engine..."<<std::endl;
    //glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::rotate(trans, glm::radians(90.f),glm::vec3(0.0,0.0,1.0));
    //trans = glm::scale(trans,glm::vec3(0.5,0.5,0.5));
    //glm::mat4 trans = scale(0.5,0.5,0.5);
    

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f,0.0f,-0.3f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)height / (float)width, 0.1f, 100.0f);
    

    glm::mat4 model;
    //model = rotate(-55.0f,1.0f,0.0f,0.0f);

    glEnable(GL_DEPTH_TEST);
    std::cout<<"Started."<<std::endl;
    while(!glfwWindowShouldClose(window)){
            processInput(window);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glClearColor(0.1f, 0.4f, 0.9f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
            // bind Texture.
            glBindTexture(GL_TEXTURE_2D, texture);
            int i;
            std::list<Shader>::iterator shadersit = shaders.begin();
            view = glm::lookAt(cam.pos, cam.pos + cam.front, cam.up);
            glBindVertexArray(VAO);
            for(i = 0; i<shaders.size(); i++){
                
                glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                //model = glm::translate(model, glm::vec3(0.0f,0.0f,0.0f));
                //model = rotate((float)glfwGetTime(),0.0,1.0,1.0);
                Shader realshade = *shadersit;
                realshade.setMat4("projection", projection);
                //unsigned int transformLoc = glGetUniformLocation(realshade.ID,"transform");
                //glUniformMatrix4fv(transformLoc,1,GL_FALSE,glm::value_ptr(trans));
                int modelloc = glGetUniformLocation(realshade.ID,"model");
                glUniformMatrix4fv(modelloc,1,GL_FALSE,glm::value_ptr(model));
                int viewb = glGetUniformLocation(realshade.ID,"view");
                glUniformMatrix4fv(viewb,1,GL_FALSE,glm::value_ptr(view));
                realshade.setMat4("projection", projection);
                realshade.use();
                glDrawArrays(GL_TRIANGLES, 0, 36);
                advance(shadersit, 1);
                
            }
            // render container
            
            
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
           
            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
	}
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
	glfwTerminate();

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0,width,height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
}
void processInput(GLFWwindow *window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window,true);
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.pos += cameraSpeed * cam.front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.pos -= cameraSpeed * cam.front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.pos -= glm::normalize(glm::cross(cam.front, cam.up)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.pos += glm::normalize(glm::cross(cam.front, cam.up)) * cameraSpeed;
}
