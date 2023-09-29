#include "App.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Model/Box.h"
#include "Model/Texture.h"
#include "Helper/AppTools.h"
#include "Helper/Logger.h"
#include "Controller/InputController.h"
#include "Shader/Shader.h"
#include "Renderer/Renderer.h"
#include "Model/VertexArray.h"
#include "Model/Pyramid.h"


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
    glEnable(GL_DEPTH_TEST);
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

    double mouseX = WINDOW_WIDTH/2;
    double mouseY = WINDOW_HEIGHT/2;

    Box box = Box(1.0, 0.5);
    box.translate(-0.5, -0.5, 0);
    box.setTexture("res/Images/him.PNG");

    renderer.addShape(&box);
    InputController inputController = InputController(2);

    Box box2 = Box(0.3, 0.3);
    box2.setTexture("res/Images/bb-sun.png");
    renderer.addShape(&box2);

    Box box3 = Box(0.25, 0.25);
    box3.translate(0.5, 0.5, 0);
    renderer.addShape(&box3);

    Pyramid pyramid = Pyramid(0.2f);
    pyramid.translate(0, 0, -1);
    pyramid.setTexture("res/Images/cobble.png");
    renderer.addShape(&pyramid, true);


    float r = 0;
    float i = 0.005f;

    glfwSwapInterval(1);

    ///* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        inputController.move2D(window, &xpos, &ypos);
        //box.translate(AppTools::normalizeX(xpos)/10, AppTools::normalizeY(ypos)/10, 0);
        inputController.mouseDrag2D(window, &mouseX, &mouseY);
        box2.rotateModelX(0.01);
        pyramid.rotateModelX(0.01);

        box3.setColor(r, 1.0f-r, 1.0f, 1.0f);
        // std::cout << r << std::endl;
        r += i;
        if (r >= 1 || r <= 0) i *= -1;

        renderer.setView(glm::translate(glm::mat4(1.0f), glm::vec3(AppTools::normalizeX(mouseX), AppTools::normalizeY(mouseY), 0.0)));
        renderer.clear();

        renderer.drawShapes(&shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.deleteShader();
    glfwTerminate();
    return err;
}