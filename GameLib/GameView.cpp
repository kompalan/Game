/**
 * @file GameView.cpp
 * @author Anurag Kompalli
 */

#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <iostream>
#include <fstream>

#include "GameView.h"

using namespace Engine::Graphics;

std::bitset<1024> Keys = std::bitset<1024>();

GameView::GameView(int width, int height, std::string name)
{
    mWidth = width;
    mHeight = height;
    mName = name;
}

void GameView::Initialize()
{
    if(!glfwInit())
    {
        glfwTerminate();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    mWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), NULL, NULL);

    if(!mWindow)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(mWindow);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        glfwTerminate();
    }

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetWindowSizeCallback(mWindow, GameView::ResizeCallback);
    glfwSetKeyCallback(mWindow, GameView::KeyCallback);

    std::ofstream ShaderFile("shaders/FragmentShader.shader");
}

void GameView::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}

GameView::~GameView()
{
    glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
    glfwTerminate();
}

void GameView::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool GameView::IsClosed()
{
    return glfwWindowShouldClose(mWindow) == GLFW_TRUE;
}

void GameView::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        Keys.set(key, true);
    }
    else if(action == GLFW_RELEASE)
    {
        Keys.set(key, false);
    }
}

void GameView::ResizeCallback(GLFWwindow* window, int width, int height)
{

    glViewport(0, 0, width, height);
}

bool GameView::IsKeyPressed(int key)
{
    if(Keys.test(key))
    {
        return true;
    }
    return false;
}
