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
#include "Renderer/Texture.h"
#include "Helper/AppTools.h"
#include "Helper/Logger.h"
#include "Controller/InputController.h"
#include "Shader/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Shape/Pyramid.h"
#include "Shape/Cube.h"
#include "Model/Player.h"

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Options* options = static_cast<Options*>(glfwGetWindowUserPointer(window));
    options->scroll = yoffset;
}

App::App()
{
    m_window = nullptr;
    m_options = nullptr;
}

Status App::setup()
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
    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
        "DuelingGame", NULL, NULL);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!m_window)
    {
        Logger::log("Error initializing GLFW\n");
        return STATUS_BAD;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        Logger::log("Error initializing GLEW\n");
        return STATUS_BAD;
    }

    m_options = new Options();
    glfwSetWindowUserPointer(m_window, m_options);
    glfwSetScrollCallback(m_window, scroll_callback);

    Logger::log((const char*)glGetString(GL_VERSION));
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEPTH_TEST);
    glDebugMessageCallback(MessageCallback, 0);

    // Enables transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    return STATUS_OK;
}

Status App::run()
{
    // err should be STATUS_OK after setup
    Status err = setup();
    if (err == STATUS_BAD)
    {
        glfwTerminate();
        return STATUS_BAD;
    }

    Shader shader;
    err = shader.generateShader("res/Shaders/Vertex.shader",
                                "res/Shaders/Fragment.shader");
    if (err == STATUS_BAD)
    {
        glfwTerminate();
        return STATUS_BAD;
    }
    shader.useShader();

    Renderer renderer;

    Box box = Box(0.25, 0.25);
    box.translate(-0.5, 0.375, -1);
    box.setTexture("res/Images/him.PNG");
    renderer.addShape(&box, true);

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

    Player player;
    renderer.addShape(player.getModel(), true);

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

    float r = 0;
    float i = 0.005f;

    glfwSwapInterval(1);

    ///* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window) && !glfwGetKey(m_window, GLFW_KEY_ESCAPE))
    {
        player.move(m_window);
        
        pyramid.rotate(0.01, 0, 1, 0);
        box3.setColor(r, 1.0f-r, 1.0f, 1.0f);
        r += i;
        if (r >= 1 || r <= 0) i *= -1;

        renderer.getCamera()->pan(m_window, m_options->scroll/10);
        renderer.getCamera()->followModel(player.getModel()->getModelMatrix());
        m_options->scroll = 0;

        renderer.clear();

        renderer.drawShapes(&shader);

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.deleteShader();
    glfwTerminate();
    return err;
}