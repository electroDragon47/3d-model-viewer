#pragma once

#define PI 3.14159
#include <cmath>

struct vec2f
{
    float x;
    float y;
};

struct vec3f
{
    float x;
    float y;
    float z;
};

struct mat4f
{
    float entries[16];
};

mat4f create_translation(vec3f translation, vec3f rotation);
mat4f create_perspective_projection(float fovy, float aspect, float near, float far);
