/**
 * @file main.cpp
 * @author Anurag Kompalli
 *
 * Sets up GLFW, sets up the GLFW error callback, and
 * calls GameView to kick off the game.
 */
#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <GameView.h>
#include <iostream>

int main(int argc, char* argv[])
{
    std::shared_ptr<Engine::Graphics::GameView> view =
            std::make_shared<Engine::Graphics::GameView>(800, 600, "Anurag");
    view->Initialize();

    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    while(!view->IsClosed())
    {
        view->Clear();
        view->Update();
    }

    return 0;
}
