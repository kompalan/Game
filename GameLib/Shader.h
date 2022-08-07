/**
 * @file Shader.h
 * @author Anurag Kompalli
 *
 *
 */

#ifndef GAME_SHADER_H
#define GAME_SHADER_H

#include "Utils.h"
#include <GL/glew.h>

namespace Engine {
    namespace Graphics {
        class Shader {
        private:
            GLuint mShader;

            const char* mVertexShaderPath;
            const char* mFragmentShaderPath;

        public:
            Shader(const char* vertexShader, const char* fragmentShader);

            GLuint load();

            void enable() const;
            void disable() const;

            ~Shader();
        };
    }
}

#endif //GAME_SHADER_H
