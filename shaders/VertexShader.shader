#version 330 core
layout (location = 0) in vec3 position;

/*
uniform mat4 projection;
uniform mat4 view = mat4(1.0);
uniform mat4 model = mat4(1.0);
*/

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
}
