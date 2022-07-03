#include "mainengine.h"
#include "object.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
//template<class obj>
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
    glViewport(0,0,800,600);
    int i;
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    std::list<object>::iterator it = objects.begin();
    for(i=0;i<objects.size();i++){
        std::cout<<"Loop"<<std::endl;
        
        object based = *it;
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &based.vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        //frag shader
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &based.fragShaderSource, NULL);
        glCompileShader(fragmentShader);
        //shader program
       
        glAttachShader(shaderProgram,vertexShader);
        glAttachShader(shaderProgram,fragmentShader);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        //link vertex attribuites
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
        glEnableVertexAttribArray(0);
        glBufferData(GL_ARRAY_BUFFER, sizeof(based.vertices),based.vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
        advance(it, 1);

    }
    while(!glfwWindowShouldClose(window)){
            processInput(window);

            glClearColor(0.1f, 0.4f, 0.9f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(shaderProgram);
            glBindVertexArray(VAO); 
            glDrawArrays(GL_TRIANGLES, 0, 3);

            glfwSwapBuffers(window);
            glfwPollEvents();
	    }
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
int main();