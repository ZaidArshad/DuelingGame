#include <GLFW/glfw3.h>
#include "Box.h"
#include "AppTools.h"
#include "InputController.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "DuelingGame", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    double xpos = 0;
    double ypos = 0;

    Box box = Box(200, 200, 50, 50);
    InputController inputController = InputController(2);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        inputController.move2D(window, &xpos, &ypos);

        //glfwGetCursorPos(window, &xpos, &ypos);
        box.setPosition(xpos, ypos);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        box.drawBox();
        //glBegin(GL_TRIANGLES);
        //glVertex2d((xpos-320)/320, (240-ypos)/240);
        //glVertex2d(0.5, 0.5);
        //glVertex2d(-0.5, -0.5);
        //glEnd();



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}