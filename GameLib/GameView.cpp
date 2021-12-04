/**
 * @file GameView.cpp
 * @author Anurag Kompalli
 */

#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include "GameView.h"

/**
 * Constructor
 * @param window GLFW window
 */
GameView::GameView(GLFWwindow* window) : mWindow(window)
{
}

/**
 * Initialize the GameView and Set up Stuff for OpenGL
 */
void GameView::Initialize()
{
    glfwSetKeyCallback(mWindow, GameView::KeyHandler);
    mTime = glfwGetTime();

    int width, height;
    glfwGetFramebufferSize(mWindow, &width, &height);
    glViewport(0, 0, width, height);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
}

/**
 * Draw the screen in the mWindow context
 */
void GameView::Draw()
{
    // Render Here
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


/**
 * Handle Keypress events from GLFW.
 * https://www.glfw.org/docs/3.3/group__input.html
 *
 * @param window GLFW window
 * @param key Key that was pressed
 * @param scancode The system-specific scancode of the key.
 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
 * @param mods Bit field describing which modifier keys were held down.
 */
void GameView::KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(key)
    {
    case GLFW_KEY_ESCAPE:
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    }
    case GLFW_KEY_RIGHT:
    {
        break;
    }
    case GLFW_KEY_LEFT:
    {
        break;
    }
    default:
    {
        break;
    }
    }
}
