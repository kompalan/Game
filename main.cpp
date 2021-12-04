#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GameView.h>

void error_callback(int error, const char* description)
{
    std::cout << "Error: " << description << std::endl;
}

int main()
{
    GLFWwindow* window;

    // Set the Error Callback function
    glfwSetErrorCallback(error_callback);

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }



    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "Anurag's Amazing Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window context current
    glfwMakeContextCurrent(window);

    std::shared_ptr<GameView> view = std::make_shared<GameView>(window);
    view->Initialize();

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        std::cout << "Error!" << std::endl;
        glfwTerminate();
    }

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        // Draw the Screen
        view->Draw();

        // Swap Front and Back Buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwSetWindowShouldClose(window, GLFW_TRUE);
    glfwTerminate();

    return 0;
}
