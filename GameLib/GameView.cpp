/**
 * @file GameView.cpp
 * @author Anurag Kompalli
 */

#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glog/logging.h>
#include <iostream>

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
        LOG(ERROR) << "GLFW Failed to Initialize. Exiting Now";
        glfwTerminate();
    }

    LOG(INFO) << "Initializing window of width " << mWidth << " height "
                << mHeight << " and name " << mName;

    mWindow = glfwCreateWindow(mWidth, mHeight, mName.c_str(), NULL, NULL);

    if(!mWindow)
    {
        LOG(ERROR) << "Failed to Create a Window. Exiting Now";
        glfwTerminate();
    }

    glfwMakeContextCurrent(mWindow);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        LOG(ERROR) << "Failed To Initialize GLEW. Exiting Now";
        glfwTerminate();
    }

    glfwSetWindowUserPointer(mWindow, this);
    glfwSetWindowSizeCallback(mWindow, GameView::ResizeCallback);
    glfwSetKeyCallback(mWindow, GameView::KeyCallback);
}

void GameView::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}

GameView::~GameView()
{
    LOG(INFO) << "Destructor Called. Closing Window Gracefully";
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
