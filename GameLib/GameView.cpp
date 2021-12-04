/**
 * @file GameView.cpp
 * @author Anurag Kompalli
 */

#define GL_SILENCE_DEPRECATION
#define GLEW_STATIC
#include "GameView.h"
#include "linmath.h"
#include <glm/mat2x2.hpp>
#include <glm/gtc/matrix_transform.hpp>

/// Define the triangle
static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
        {
                { -0.6f, -0.4f, 1.f, 0.f, 0.f },
                {  0.6f, -0.4f, 0.f, 1.f, 0.f },
                {   0.f,  0.6f, 0.f, 0.f, 1.f }
        };

/// Define the shaders
static const char* vertex_shader_text =
        "#version 110\n"
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";

/// Define the shaders
static const char* fragment_shader_text =
        "#version 110\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

/**
 * Constructor
 * @param window GLFW window
 */
GameView::GameView(GLFWwindow* window) : mWindow(window)
{
}

/**
 * Initialize the GameView and Set up Stuff for OpenGL
 */
void GameView::Initialize()
{
    glm::mat2x2 a;
    
    glfwSetKeyCallback(mWindow, GameView::KeyHandler);
    mTime = glfwGetTime();

    int width, height;
    glfwGetFramebufferSize(mWindow, &width, &height);
    glViewport(0, 0, width, height);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
            sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
            sizeof(vertices[0]), (void*) (sizeof(float) * 2));
}

/**
 * Handle Keypress events from GLFW.
 * https://www.glfw.org/docs/3.3/group__input.html
 *
 * @param window GLFW window
 * @param key Key that was pressed
 * @param scancode The system-specific scancode of the key.
 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
 * @param mods Bit field describing which modifier keys were held down.
 */
void GameView::KeyHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(key)
    {
        case GLFW_KEY_ESCAPE:
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        }
        case GLFW_KEY_RIGHT:
        {
            break;
        }
        case GLFW_KEY_LEFT:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

/**
 * Draw the screen in the mWindow context
 */
void GameView::Draw()
{
    // Render Here
    glClear(GL_COLOR_BUFFER_BIT);

    float ratio;
    int width, height;
    mat4x4 m, p, mvp;

    glfwGetFramebufferSize(mWindow, &width, &height);
    ratio = (float)width / (float) height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
