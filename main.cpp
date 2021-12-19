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
#include <glog/logging.h>

int main(int argc, char* argv[])
{
    fLB::FLAGS_log_prefix = true;
    fLB::FLAGS_alsologtostderr = true;
    fLB::FLAGS_colorlogtostderr = true;

    google::InitGoogleLogging(argv[0]);
    std::shared_ptr<Engine::Graphics::GameView> view =
            std::make_shared<Engine::Graphics::GameView>(800, 600, "Anurag");
    view->Initialize();

    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    while(!view->IsClosed())
    {
        view->Clear();

        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        view->Update();
    }

    return 0;
}
