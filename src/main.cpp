#include <iostream>
#include <cstdlib>

#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "shader.h"
#include "bmp.h"


const GLchar *vertexShaderSource;
const GLchar *fragmentShaderSource;


static void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char *argv[])
{
    std::string FullPath (argv[0]);
    FullPath = FullPath.substr(0,FullPath.find_last_of("/"));
    std::string fragShStr = FullPath + "/../shaders/shader.frag";
    std::string vectShStr = FullPath + "/../shaders/shader.vert";
    std::string bmpStr = FullPath + "/../bmp/persona.bmp";
    loadShader(fragShStr,&fragmentShaderSource);
    loadShader(vectShStr,&vertexShaderSource);
    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "Failed to Initialise the GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(1600, 900, "Square", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to init GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    GLuint shaderProgram = makeShaderProgram(fragmentShaderSource,vertexShaderSource);

    unloadShader(&vertexShaderSource);
    unloadShader(&fragmentShaderSource);
    
    static const GLfloat vertices[] = {
               -1.0f,-1.0f,-1.0f, // triangle 1 : begin
               -1.0f,-1.0f, 1.0f,
               -1.0f, 1.0f, 1.0f, // triangle 1 : end
               1.0f, 1.0f,-1.0f, // triangle 2 : begin
               -1.0f,-1.0f,-1.0f,
               -1.0f, 1.0f,-1.0f, // triangle 2 : end
               1.0f,-1.0f, 1.0f,
               -1.0f,-1.0f,-1.0f,
               1.0f,-1.0f,-1.0f,
               1.0f, 1.0f,-1.0f,
               1.0f,-1.0f,-1.0f,
               -1.0f,-1.0f,-1.0f,
               -1.0f,-1.0f,-1.0f,
               -1.0f, 1.0f, 1.0f,
               -1.0f, 1.0f,-1.0f,
               1.0f,-1.0f, 1.0f,
               -1.0f,-1.0f, 1.0f,
               -1.0f,-1.0f,-1.0f,
               -1.0f, 1.0f, 1.0f,
               -1.0f,-1.0f, 1.0f,
               1.0f,-1.0f, 1.0f,
               1.0f, 1.0f, 1.0f,
               1.0f,-1.0f,-1.0f,
               1.0f, 1.0f,-1.0f,
               1.0f,-1.0f,-1.0f,
               1.0f, 1.0f, 1.0f,
               1.0f,-1.0f, 1.0f,
               1.0f, 1.0f, 1.0f,
               1.0f, 1.0f,-1.0f,
               -1.0f, 1.0f,-1.0f,
               1.0f, 1.0f, 1.0f,
               -1.0f, 1.0f,-1.0f,
               -1.0f, 1.0f, 1.0f,
               1.0f, 1.0f, 1.0f,
               -1.0f, 1.0f, 1.0f,
               1.0f,-1.0f, 1.0f
    };

    static const GLfloat g_color_buffer_data[] = {
               0.583f,  0.771f,  0.014f,
               0.609f,  0.115f,  0.436f,
               0.327f,  0.483f,  0.844f,
               0.822f,  0.569f,  0.201f,
               0.435f,  0.602f,  0.223f,
               0.310f,  0.747f,  0.185f,
               0.597f,  0.770f,  0.761f,
               0.559f,  0.436f,  0.730f,
               0.359f,  0.583f,  0.152f,
               0.483f,  0.596f,  0.789f,
               0.559f,  0.861f,  0.639f,
               0.195f,  0.548f,  0.859f,
               0.014f,  0.184f,  0.576f,
               0.771f,  0.328f,  0.970f,
               0.406f,  0.615f,  0.116f,
               0.676f,  0.977f,  0.133f,
               0.971f,  0.572f,  0.833f,
               0.140f,  0.616f,  0.489f,
               0.997f,  0.513f,  0.064f,
               0.945f,  0.719f,  0.592f,
               0.543f,  0.021f,  0.978f,
               0.279f,  0.317f,  0.505f,
               0.167f,  0.620f,  0.077f,
               0.347f,  0.857f,  0.137f,
               0.055f,  0.953f,  0.042f,
               0.714f,  0.505f,  0.345f,
               0.783f,  0.290f,  0.734f,
               0.722f,  0.645f,  0.174f,
               0.302f,  0.455f,  0.848f,
               0.225f,  0.587f,  0.040f,
               0.517f,  0.713f,  0.338f,
               0.053f,  0.959f,  0.120f,
               0.393f,  0.621f,  0.362f,
               0.673f,  0.211f,  0.457f,
               0.820f,  0.883f,  0.371f,
               0.982f,  0.099f,  0.879f
    };

    static const GLfloat g_uv_buffer_data[] = {
               0.000059f, 1.0f-0.000004f,
               0.000103f, 1.0f-0.336048f,
               0.335973f, 1.0f-0.335903f,
               1.000023f, 1.0f-0.000013f,
               0.667979f, 1.0f-0.335851f,
               0.999958f, 1.0f-0.336064f,
               0.667979f, 1.0f-0.335851f,
               0.336024f, 1.0f-0.671877f,
               0.667969f, 1.0f-0.671889f,
               1.000023f, 1.0f-0.000013f,
               0.668104f, 1.0f-0.000013f,
               0.667979f, 1.0f-0.335851f,
               0.000059f, 1.0f-0.000004f,
               0.335973f, 1.0f-0.335903f,
               0.336098f, 1.0f-0.000071f,
               0.667979f, 1.0f-0.335851f,
               0.335973f, 1.0f-0.335903f,
               0.336024f, 1.0f-0.671877f,
               1.000004f, 1.0f-0.671847f,
               0.999958f, 1.0f-0.336064f,
               0.667979f, 1.0f-0.335851f,
               0.668104f, 1.0f-0.000013f,
               0.335973f, 1.0f-0.335903f,
               0.667979f, 1.0f-0.335851f,
               0.335973f, 1.0f-0.335903f,
               0.668104f, 1.0f-0.000013f,
               0.336098f, 1.0f-0.000071f,
               0.000103f, 1.0f-0.336048f,
               0.000004f, 1.0f-0.671870f,
               0.336024f, 1.0f-0.671877f,
               0.000103f, 1.0f-0.336048f,
               0.336024f, 1.0f-0.671877f,
               0.335973f, 1.0f-0.335903f,
               0.667969f, 1.0f-0.671889f,
               1.000004f, 1.0f-0.671847f,
               0.667979f, 1.0f-0.335851f
    };
    
    //Matrices stuff

    ////glm::mat4 MVPmatrix = projection * view * model;
    ////glm::mat4 myIdentityMatrix = glm::mat4(1.0f);
    ////glm::mat4 ViewMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f ,0.0f));
    
    //Model Matrix (Simple Identity Matrix)
    glm::mat4 ModelMatrix = glm::mat4(1.0f);
    //ModelMatrix[0].x = 2.0f; //Scaling x
    //ModelMatrix[1].y = 2.0f; //Scaling y
    //ModelMatrix[2].z = 2.0f; //Scaling z
    
    //Camera Matrix
    glm::mat4 ViewMatrix = glm::lookAt(
        glm::vec3(4,3,-3),   // the position of your camera, in world space
        glm::vec3(0,0,0),   // where you want to look at, in world space
        glm::vec3(0,1,0)    // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
     );
    //Projection Matrix
    glm::mat4 ProjectionMatrix = glm::perspective(
          glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
          16.0f / 9.0f,    // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
          0.1f,            // Near clipping plane. Keep as big as possible, or you'll get precision issues.
          100.0f          // Far clipping plane. Keep as little as possible.
    );
    glm::mat4 mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
    //Setting it up
    GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
    
    
    GLuint VBO, VAO, colorBuffer;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &colorBuffer);
    
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);//color
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);//tex uv coords
    

    GLuint Texture = loadBMP_custom(bmpStr);
    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID = glGetUniformLocation(shaderProgram, "myTextureSampler");

    
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
	glfwSetKeyCallback(window,keycallback);
    
	while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        ModelMatrix = glm::rotate(ModelMatrix, 0.01f, glm::vec3(0, 1, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
        mvp = ProjectionMatrix * ViewMatrix * ModelMatrix;
        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        // Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, Texture);
        // Set our "myTextureSampler" sampler to use Texture Unit 0
        glUniform1i(TextureID, 0);
        
        //Attributes
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(
           0,
           3,
           GL_FLOAT,
           GL_FALSE,
           3 * sizeof(GLfloat),
           (GLvoid *)0
        );
        
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(
           1,                                // attribute no.1
           //3,                                // size for color
           2,                                // size of U,V
           GL_FLOAT,                         // type
           GL_FALSE,                         // normalized?
           0,                                // stride
           (GLvoid*)0                        // array buffer offset
        );
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &colorBuffer);
    glfwTerminate();
    return EXIT_SUCCESS;
}
