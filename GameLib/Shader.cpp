/**
 * @file Shader.cpp
 * @author Anurag Kompalli
 */

#include "Shader.h"

Engine::Graphics::Shader::Shader(const char* vertexShader, const char* fragmentShader) :
    mVertexShaderPath(vertexShader), mFragmentShaderPath(fragmentShader)
{
    mShader = load();
}

GLuint Engine::Graphics::Shader::load()
{
    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexShaderSource = Engine::Utils::ReadFile(mVertexShaderPath);
    std::string fragmentShaderSource = Engine::Utils::ReadFile(mFragmentShaderPath);

    const char* v = vertexShaderSource.c_str();
    const char* f = fragmentShaderSource.c_str();

    glShaderSource(vertex, 1, &v, nullptr);
    glCompileShader(vertex);

    GLint resultVertex;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &resultVertex);

    if(resultVertex == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);

        char* log = (char*) calloc(length, sizeof(char));
        glGetShaderInfoLog(vertex, length, &length, log);

        printf("%s", log);
        glDeleteShader(vertex);
        return 0;
    }

    glShaderSource(fragment, 1, &f, nullptr);
    glCompileShader(fragment);

    GLint resultFragment;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &resultFragment);

    if(resultFragment == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);

        char* log = (char*) calloc(length, sizeof(char));
        glGetShaderInfoLog(fragment, length, &length, log);

        printf("%s", log);
        glDeleteShader(fragment);
        return 0;
    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        printf("%s", infoLog);
    }

    glValidateProgram(program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return program;
}

void Engine::Graphics::Shader::enable() const
{
    glUseProgram(mShader);
}

void Engine::Graphics::Shader::disable() const
{
    glUseProgram(0);
}

Engine::Graphics::Shader::~Shader()
{
    glDeleteProgram(mShader);
}
