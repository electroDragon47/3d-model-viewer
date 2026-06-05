#pragma once
#include "matrix.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Camera
{
    public:
    vec3f position;
    vec3f rotation;
    mat4f model_matrix;
    float speed = 3.0f;
    float zoom_senstivity = 0.2f;
    Camera();
    void Update(GLFWwindow *window, float dt);
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);