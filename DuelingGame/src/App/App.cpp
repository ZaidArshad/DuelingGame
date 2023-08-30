#include "App.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Box.hpp"
#include "AppTools.hpp"
#include "Logger.hpp"
#include "InputController.hpp"
#include "Shader.hpp"

#include <iostream>
#include <fstream>

App::App()
{
    window = nullptr;
}

Status App::run()
{
    /* Initialize the library */
    if (!glfwInit())
    {
        Logger::log("Error initializing GLFW\n");
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DuelingGame", NULL, NULL);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

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

    Box box2 = Box((WINDOW_WIDTH / 2) - 150, (WINDOW_HEIGHT / 2) - 150, 300, 300);

    Shader shader;
    Status err = STATUS_OK;
    err = shader.generateShader("res/Shaders/Vertex.shader", "res/Shaders/Fragment.shader");
    if (err == STATUS_BAD)
    {
        glfwTerminate();
        return STATUS_BAD;
    }
    shader.useShader();

    ///* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        inputController.move2D(window, &xpos, &ypos);
        box.setPosition(xpos, ypos);

        shader.setFragmentColor(AppTools::normalizeX(xpos),
            0.5f, -AppTools::normalizeY(ypos), 1.0f);

        std::cout << AppTools::normalizeX(xpos) << " "
            << AppTools::normalizeY(ypos)
            << " " << xpos << " " << ypos << std::endl;

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
}