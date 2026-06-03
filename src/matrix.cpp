#include "matrix.h"

mat4f create_translation(vec3f translation)
{
    mat4f matrix;
    
    matrix.entries[0] = 1.0f;
    matrix.entries[1] = 0.0f;
    matrix.entries[2] = 0.0f;
    matrix.entries[3] = 0.0f;
    
    matrix.entries[4] = 0.0f;
    matrix.entries[5] = 1.0f;
    matrix.entries[6] = 0.0f;
    matrix.entries[7] = 0.0f;

    matrix.entries[8] = 0.0f;
    matrix.entries[9] = 0.0f;
    matrix.entries[10] = 1.0f;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = translation.x;
    matrix.entries[13] = translation.y;
    matrix.entries[14] = translation.z;
    matrix.entries[15] = 1.0f;

    return matrix;

}