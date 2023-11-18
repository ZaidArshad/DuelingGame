#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper/Logger.h"
#include "Helper/AppTools.h"
#include "Shape/Model.h"
#include "TestTools/TestTools.h"
#include "Shader/Shader.h"
#include "Renderer/Renderer.h"


int main()
{
    // BOILERPLATE TO INIT GLFW AND GLEW
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
    GLFWwindow* window = glfwCreateWindow(500, 500,
        "DuelingGame", NULL, NULL);
    glViewport(0, 0, 500, 500);
    if (!window)
    {
        Logger::log("Error initializing GLFW\n");
        return STATUS_BAD;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        Logger::log("Error initializing GLEW\n");
        return STATUS_BAD;
    }

    Shader shader;
    Status err = shader.generateShader("res/Shaders/Vertex.shader",
        "res/Shaders/Fragment.shader");
    if (err == STATUS_BAD)
    {
        glfwTerminate();
        return STATUS_BAD;
    }
    shader.useShader();

    Renderer renderer;
    Model model("res/Models/cube/model");
    model.setTexture("res/Models/Letters.png");
    renderer.addShape(&model, true);

    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        renderer.clear();

        renderer.drawShapes(&shader);

        renderer.getCamera()->followModel(model.getModelMatrix());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    shader.deleteShader();
    glfwTerminate();
    return err;
}