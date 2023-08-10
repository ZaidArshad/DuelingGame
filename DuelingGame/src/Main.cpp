#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Model/Box.hpp"
#include "Helper/AppTools.hpp"
#include "Controller/InputController.hpp"
#include "Shader/Shader.hpp"
#include<iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
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
        std::cout << "Error initializing GLEW" << std::endl;
        return -1;
    }

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