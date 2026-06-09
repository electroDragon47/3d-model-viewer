#pragma once


#include <gl/glew.h>
#include <iostream>
#include "matrix.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class Cube
{
    public:
    vec3f position;
    vec3f rotation;
    vec3f scale;
    mat4f model;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int model_loc;
    unsigned int scale_loc;
    Cube();
    void getUniformLocation(unsigned int shader);
    void Update();
    void Draw();
    void DrawUI();
    ~Cube();

};

void createVaoVbo(unsigned int *VAO, unsigned int *VBO);