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

    matrix.entries[0] = cz * cy;
    matrix.entries[1] = sz * cy;
    matrix.entries[2] = -sy;
    matrix.entries[3] = 0.0f;
   
    matrix.entries[4] = cz * sy * sx - sz * cx;
    matrix.entries[5] = sz * sy * sx + cz * cx;
    matrix.entries[6] = cy * sx;
    matrix.entries[7] = 0.0f;

    matrix.entries[8]  = cz * sy * cx + sz * sx;
    matrix.entries[9]  = sz * sy * cx - cz * sx;
    matrix.entries[10] = cy * cx;
    matrix.entries[11] = 0.0f;

    matrix.entries[12] = translation.x;
    matrix.entries[13] = translation.y;
    matrix.entries[14] = translation.z;
    matrix.entries[15] = 1.0f;

    return matrix;
}

mat4f create_perspective_projection(float fovy, float aspect, float near, float far) {
    
    fovy = fovy * PI / 360.0f;
    float t = tanf(fovy);

    mat4f matrix;
    for (int i = 0; i < 16; i++) matrix.entries[i] = 0.0f;

    matrix.entries[0]  = 1.0f / (aspect * t);
    matrix.entries[5]  = 1.0f / t;
    matrix.entries[10] = -(far + near) / (far - near);
    matrix.entries[11] = -1.0f; 
    matrix.entries[14] = -(2.0f * far * near) / (far - near);

    return matrix;
}