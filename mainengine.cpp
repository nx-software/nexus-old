#include "headers/mainengine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "headers/stb_image.h"
#include "headers/shader.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//template<class obj>
int basedwidth, basedheight, nrChannels;
unsigned char *data = stbi_load("wall.jpg", &basedwidth, &basedheight, &nrChannels, 0); 
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
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
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
        // unsigned int vertexShader;
        // vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // glShaderSource(vertexShader, 1, &based.vertexShaderSource, NULL);
        // glCompileShader(vertexShader);
        // //frag shader
        // unsigned int fragmentShader;
        // fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // glShaderSource(fragmentShader, 1, &based.fragShaderSource, NULL);
        // glCompileShader(fragmentShader);
        // //shader program
       
        // glAttachShader(shaderProgram,vertexShader);
        // glAttachShader(shaderProgram,fragmentShader);
        // glLinkProgram(shaderProgram);
        // glUseProgram(shaderProgram);
        // glDeleteShad er(vertexShader);
        // glDeleteShader(fragmentShader);
        Shader shadereal(based.vertexShaderPath, based.fragShaderPath);
        shaders.push_back(shadereal);
        //link vertex attribuites
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(based.vertices), based.vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(based.indices), based.indices, GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);  
        //glBindBuffer(GL_ARRAY_BUFFER, 0); 
        //glBindVertexArray(0); 

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
    while(!glfwWindowShouldClose(window)){
            processInput(window);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glClearColor(0.1f, 0.4f, 0.9f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);  
            // bind Texture.
            glBindTexture(GL_TEXTURE_2D, texture);
            int i;
            std::list<Shader>::iterator shadersit = shaders.begin();
            for(i = 0; i<100; i++){
                Shader realshade = *shadersit;
                realshade.use();
                advance(shadersit, 1);
            }
            // render container
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            glfwSwapBuffers(window);
            glfwPollEvents();
	}
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
}
