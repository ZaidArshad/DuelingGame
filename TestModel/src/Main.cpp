#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper/Logger.h"
#include "Helper/AppTools.h"
#include "Shape/Model.h"
#include "TestTools/TestTools.h"
#include "Shader/Shader.h"
#include "Renderer/Renderer.h"
#include "Shape/Box.h"
#include "Model/Player.h"


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

    return 0;
}