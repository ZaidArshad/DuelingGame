#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Model/Box.hpp"
#include "Helper/AppTools.hpp"
#include "Helper/Logger.hpp"
#include "Helper/GLError.hpp"
#include "Controller/InputController.hpp"
#include "Shader/Shader.hpp"

#include <iostream>
#include <fstream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        Logger::log("Error initializing GLFW\n");
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DuelingGame", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        Logger::log("Error initializing GLEW\n");
        return -1;
    }

    Logger::log((const char*)glGetString(GL_VERSION));
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    double xpos = 0;
    double ypos = 0;

    Box box = Box(200, 200, 50, 50);
    InputController inputController = InputController(2);

    Box box2 = Box(200, 200, 100, 100);

    Shader shader;
    shader.generateShader("res/Shaders/Vertex.shader", "res/Shaders/Fragment.shader");
    shader.useShader();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        inputController.move2D(window, &xpos, &ypos);
        box.setPosition(xpos, ypos);
    
        ///* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        box.drawBox();
        box2.drawBox();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.deleteShader();

    glfwTerminate();
    return 0;
}