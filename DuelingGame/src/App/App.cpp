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
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 
                              "DuelingGame", NULL, NULL);
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

    // Enables transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    Shader shader;
    Status err = STATUS_OK;
    err = shader.generateShader("res/Shaders/Vertex.shader",
                                "res/Shaders/Fragment.shader");
    if (err == STATUS_BAD)
    {
        glfwTerminate();
        return STATUS_BAD;
    }
    shader.useShader();

    Renderer renderer;

    float xpos = 0.0f;
    float ypos = 0.0f;

    Box box = Box(200, 200, 50, 50);
    renderer.addShape(&box);
    InputController inputController = InputController(2);

    Box box2 = Box((WINDOW_WIDTH / 2) - 150, (WINDOW_HEIGHT / 2) - 150, 300, 300);
    renderer.addShape(&box2);

    GLint location = glGetUniformLocation(shader.getProgram(), "u_Texture");
    Texture texture("res/Images/him.PNG");
    texture.bind(0);
    glUniform1i(location, 0);

    float r = 0;
    float i = 0.005f;

    glfwSwapInterval(1);

    ///* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        inputController.move2D(window, &xpos, &ypos);
        box.setPosition(xpos, ypos);

        box.setColor(AppTools::normalizeX(xpos),
            0.5f,
            AppTools::normalizeY(ypos),
            1.0f);

        box2.setColor(r, 1.0f-r, 1.0f, 0.5f);
        std::cout << r << std::endl;
        r += i;
        if (r >= 1 || r <= 0) i *= -1;
  
        std::cout << AppTools::normalizeX(xpos) << " "
                  << AppTools::normalizeY(ypos)
                  << " " << xpos << " " << ypos << std::endl;

        renderer.clear();

        renderer.drawShapes();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.deleteShader();
    glfwTerminate();
    return err;
}