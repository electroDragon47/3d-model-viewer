#pragma once


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "matrix.h"
#include <gl/glew.h>

class Light
{
    public:
    vec3f position;
    vec3f color;
    unsigned int pos_loc;
    unsigned int color_loc;
    Light(); 
    void getUniformLocation(unsigned int shaderProgram);
    void Update();
    void DrawUI();
};

