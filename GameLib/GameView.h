/**
 * @file GameView.h
 * @author Anurag Kompalli
 *
 *
 */

#ifndef GAME_GAMEVIEW_H
#define GAME_GAMEVIEW_H
#include <GLFW/glfw3.h>
#include <string>
#include <bitset>


class Logger;
namespace Engine
{
    namespace Graphics
    {
        /**
         * Main View class for the game,
         * manages the GLFW window
         */
        class GameView {
        private:
            int mWidth = 0;
            int mHeight = 0;

            std::string mName = "";
            GLFWwindow* mWindow;

        public:

            GameView() = delete;

            explicit GameView(int width, int height, std::string name);

            void Initialize();

            void Update();

            void Clear();

            bool IsClosed();

            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

            static void ResizeCallback(GLFWwindow* window, int width, int height);

            static bool IsKeyPressed(int key);

            ~GameView();
        };
    }
}

#endif //GAME_GAMEVIEW_H
