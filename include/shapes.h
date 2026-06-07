#pragma once


#include <gl/glew.h>
#include <iostream>
#include "matrix.h"


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

};

void createVaoVbo(unsigned int *VAO, unsigned int *VBO);