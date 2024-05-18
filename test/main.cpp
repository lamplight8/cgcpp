#include <iostream>
#include <GL/gl.h>
#include <glfw3.h>

int main()
{
    GLFWwindow* win;
    if(!glfwInit())
        return -1;
    win = glfwCreateWindow(480, 320, "TestOpenGL", NULL, NULL);
    if(!win)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(win);

    while(!glfwWindowShouldClose(win))
    {
        glBegin(GL_TRIANGLES);

        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-1.0, -1.0, 0.0);

        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(1.0, -1.0, 0.0);

        glEnd();

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}