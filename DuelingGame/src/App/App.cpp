#include "App.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model/Box.h"
#include "Model/Texture.h"
#include "Helper/AppTools.h"
#include "Helper/Logger.h"
#include "Controller/InputController.h"
#include "Shader/Shader.h"
#include "Renderer/Renderer.h"

#include "Model/VertexArray.h"

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

    Shader shader;
    Status err = STATUS_OK;
    err = shader.generateShader("res/Shaders/Vertex.shader", "res/Shaders/Fragment.shader");
    if (err == STATUS_BAD)
    {
        glfwTerminate();
        return STATUS_BAD;
    }
    shader.useShader();

    Renderer renderer;

    double xpos = 0;
    double ypos = 0;

    Box box = Box(200, 200, 50, 50);
    InputController inputController = InputController(2);
    //renderer.addShape(&box);

    Box box2 = Box((WINDOW_WIDTH / 2) - 150, (WINDOW_HEIGHT / 2) - 150, 300, 300);
    //renderer.addShape(&box2);

    float r = 0;
    float i = 0.005;

    std::vector<float> positions
    {
        -0.5f, 0.5f,
        0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f
    };
    std::vector<unsigned int> indices
    {
        0, 1, 2,
        1, 2, 3
    };
    VertexArray va(positions, 2, indices);
    std::vector<float> color
    {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    va.addBuffer(color, 4);



    glfwSwapInterval(1);

    ///* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        //shader.useShader();
        //inputController.move2D(window, &xpos, &ypos);
        //box.setPosition(xpos, ypos);

        /*box.setColor(AppTools::normalizeX(xpos),
            0.5f,
            AppTools::normalizeY(ypos),
            1.0f);*/

        //box2.setColor(r, 1.0-r, 1.0, 1.0);
        std::cout << r << std::endl;
        r += i;
        if (r >= 1 || r <= 0) i *= -1;
  

        std::cout << AppTools::normalizeX(xpos) << " "
                  << AppTools::normalizeY(ypos)
                  << " " << xpos << " " << ypos << std::endl;

        std::vector<float> color
        {
            r, 0.0f, 0.0f, 1.0f,
            r, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f
        };
        va.updateBuffer(1, color);

        renderer.clear();

        //renderer.drawShapes(shader);
        va.draw();
        box.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.deleteShader();
    glfwTerminate();
    return err;
}