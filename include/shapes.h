#pragma once
#define GLEW_STATIC

#include <gl/glew.h>
#include <iostream>
#include "matrix.h"


class Cube
{
    public:
    vec3f position;
    vec3f rotation;
    vec3f scale;
    unsigned int VAO;
    unsigned int VBO;
};

void createVaoVbo(unsigned int *VAO, unsigned int *VBO);