#pragma once
#include "matrix.h"

class Camera
{
    public:
    vec3f position;
    vec3f rotation;
    mat4f model_matrix;
    Camera();
};