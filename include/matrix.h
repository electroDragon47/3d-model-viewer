#pragma once

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

mat4f create_translation(vec3f translation);
