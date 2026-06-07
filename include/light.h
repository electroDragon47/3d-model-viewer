#pragma once

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
};

