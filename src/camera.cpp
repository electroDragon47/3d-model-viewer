#include "camera.h"


Camera::Camera()
{
    position = {0.0f , 0.0f , 0.0f};
    rotation = {0.0f , 0.0f , 0.0f};

    // matrix to learn 
    model_matrix.entries[0] = 1.0f;
    model_matrix.entries[1] = 0.0f;
    model_matrix.entries[2] = 0.0f;
    model_matrix.entries[3] = 0.0f;

    model_matrix.entries[4] = 0.0f;
    model_matrix.entries[5] = 1.0f;
    model_matrix.entries[6] = 0.0f;
    model_matrix.entries[7] = 0.0f;

    model_matrix.entries[8] = 0.0f;
    model_matrix.entries[9] = 0.0f;
    model_matrix.entries[10] = 1.0f;
    model_matrix.entries[11] = 0.0f;

    model_matrix.entries[12] = 0.0f;
    model_matrix.entries[13] = 0.0f;
    model_matrix.entries[14] = 0.0f;
    model_matrix.entries[15] = 1.0f;
}