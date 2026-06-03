#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;
uniform vec3 scale;
uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos *scale, 1.0f);
    vertexColor = vec4(aColor , 1.0f);
}