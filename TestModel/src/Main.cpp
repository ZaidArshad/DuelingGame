#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Helper/Logger.h"
#include "Helper/AppTools.h"
#include "TestShape/TestShape.h"
#include "Shape/Model.h"
#include "TestTools/TestTools.h"

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
    GLFWwindow* window = glfwCreateWindow(100, 100,
        "DuelingGame", NULL, NULL);
    glViewport(0, 0, 100, 100);
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
    // END OF BOILERPLATE

	testModel();
}