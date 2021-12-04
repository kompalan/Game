/**
 * @file GameView.h
 * @author Anurag Kompalli
 *
 *
 */

#ifndef GAME_GAMEVIEW_H
#define GAME_GAMEVIEW_H
#include <GLFW/glfw3.h>

/**
 * Main View Class for the Whole Game.
 * Manages the Game Loop.
 */
class GameView {
private:
    /// The Window
    GLFWwindow* mWindow;

    /// Timer
    double mTime;

    unsigned int mVBO;

    double positions[6] = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
    };

public:
    GameView() = delete;

    explicit GameView(GLFWwindow* window);
    void Initialize();

    void Draw();

    static void KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif //GAME_GAMEVIEW_H
