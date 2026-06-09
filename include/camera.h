#pragma once

#include <gl/glew.h>
#include "matrix.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
class Camera
{
    public:
    unsigned int camera_loc;
    vec3f position;
    vec3f rotation;
    mat4f model_matrix;
    float speed = 3.0f;
    float zoom_senstivity = 0.2f;
    Camera();
    void getUniformLocation(unsigned int shader);
    void Update(GLFWwindow *window, float dt);
    void DrawUI();
};

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);