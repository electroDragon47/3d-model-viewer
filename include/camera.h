#pragma once
#include "matrix.h"
#include "GLFW/glfw3.h"

class Camera
{
    public:
    vec3f position;
    vec3f rotation;
    mat4f model_matrix;
    float speed = 5.0f;
    Camera();
    void Update(GLFWwindow *window, float dt);

};