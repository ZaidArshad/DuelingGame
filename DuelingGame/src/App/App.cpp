#include "App.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "Shape/Box.h"
#include "Model/Texture.h"
#include "Helper/AppTools.h"
#include "Helper/Logger.h"
#include "Controller/InputController.h"
#include "Shader/Shader.h"
#include "Renderer/Renderer.h"
#include "Model/VertexArray.h"
#include "Shape/Pyramid.h"
#include "Shape/Cube.h"

double g_scroll = 0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_scroll = yoffset;
}

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

    Box box = Box(0.25, 0.25);
    box.translate(-0.5, 0.375, -1);
    box.setTexture("res/Images/him.PNG");
    renderer.addShape(&box, true);

    InputController inputController = InputController(0.01f);

    Box box2 = Box(1, 5);
    box2.setTexture("res/Images/cobble.png");
    box2.makeTiled(5, 50);
    box2.rotate(glm::half_pi<float>(), 1, 0, 0);
    renderer.addShape(&box2, true);

    Box box3 = Box(0.25, 0.25);
    box3.translate(0.5, 0.5, 0);
    renderer.addShape(&box3);

    Pyramid pyramid = Pyramid(0.05f);
    pyramid.translate(0, 2, -1);
    pyramid.setTexture("res/Images/france.png");
    renderer.addShape(&pyramid, true);

    Cube cube = Cube(0.05f);
    renderer.addShape(&cube, true);
    cube.translate(-0.5, 0.051f, -1);
    cube.setTexture("res/Images/fella.png");

    std::vector<Cube*> towers;
    for (int i = 0; i < 6; i++)
    {
        Cube* tower = new Cube(0.05f);
        towers.push_back(tower);
        tower->translate(1 * (i%2) - 0.5, 0.15f, (i%3)*-1);
        tower->scale(1, 4, 1);
        tower->setTexture("res/Images/fella.png");
        renderer.addShape(tower, true);
    }

    renderer.getCamera()->translate(0, 0.25, 0);

    glfwSetScrollCallback(window, scroll_callback);

    float r = 0;
    float i = 0.005f;

    float scroll = 0;

    glfwSwapInterval(1);

    ///* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {

        inputController.move2D(window, &xpos, &ypos);

        double dragX = 0;
        double dragY = 0;
        inputController.mouseDrag2D(window, &dragX, &dragY);

        std::cout << glm::to_string(renderer.getCamera()->getView()) << std::endl;

        cube.translate(0, 0, ypos);

        cube.rotate(-xpos, 0, 1, 0);
        
        
        pyramid.rotate(0.01, 0, 1, 0);

        box3.setColor(r, 1.0f-r, 1.0f, 1.0f);
        // std::cout << r << std::endl;
        r += i;
        if (r >= 1 || r <= 0) i *= -1;

        //renderer.getCamera()->translate(
        //    dragX,
        //    dragY,
        //    g_scroll/10
        //);
        
        //renderer.getCamera()->translate(-xpos, 0, ypos);
        renderer.getCamera()->followModel(cube.getModelMatrix(), dragX, dragY, g_scroll / 10);
        g_scroll = 0;
        //renderer.getCamera()->rotate(xpos / 2, 0, 1, 0);
        //renderer.getCamera()->rotate(0.1, 1, 0, 0);

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