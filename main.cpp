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
#include <Shader.h>

using namespace Engine::Graphics;

int main(int argc, char* argv[])
{
    std::shared_ptr<Engine::Graphics::GameView> view =
            std::make_shared<Engine::Graphics::GameView>(800, 600, "Anurag");
    view->Initialize();

    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
            0.5f, -0.5f, 0.0f, // right
            0.0f,  0.5f, 0.0f  // top
    };

    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);

    GLuint vbuf;
    glGenBuffers(1, &vbuf);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArrayAPPLE(0);
    Shader shader("VertexShader.shader", "FragmentShader.shader");
    shader.enable();

    while(!view->IsClosed())
    {
        view->Clear();

        glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        view->Update();
    }

    return 0;
}
