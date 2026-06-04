#include "matrix.h"

mat4f create_translation(vec3f translation, vec3f rotation)
{
    float rx = rotation.x * PI / 180.0f;
    float ry = rotation.y * PI / 180.0f;
    float rz = rotation.z * PI / 180.0f;

    float cx = cosf(rx);
    float sx = sinf(rx);

    float cy = cosf(ry);
    float sy = sinf(ry);

    float cz = cosf(rz);
    float sz = sinf(rz);

    mat4f matrix;

    // Column 0
    matrix.entries[0] = cz * cy;
    matrix.entries[1] = sz * cy;
    matrix.entries[2] = -sy;
    matrix.entries[3] = 0.0f;

    // Column 1
    matrix.entries[4] = cz * sy * sx - sz * cx;
    matrix.entries[5] = sz * sy * sx + cz * cx;
    matrix.entries[6] = cy * sx;
    matrix.entries[7] = 0.0f;

    // Column 2
    matrix.entries[8]  = cz * sy * cx + sz * sx;
    matrix.entries[9]  = sz * sy * cx - cz * sx;
    matrix.entries[10] = cy * cx;
    matrix.entries[11] = 0.0f;

    // Translation
    matrix.entries[12] = translation.x;
    matrix.entries[13] = translation.y;
    matrix.entries[14] = translation.z;
    matrix.entries[15] = 1.0f;

    return matrix;
}