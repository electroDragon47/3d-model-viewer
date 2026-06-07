#include "camera.h"

float camera_z = -1.0f;

Camera::Camera()
{
    position = {0.0f , 0.0f , camera_z};
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

    model_matrix.entries[12] = -position.x;
    model_matrix.entries[13] = -position.y;
    model_matrix.entries[14] = position.z;
    model_matrix.entries[15] = 1.0f;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera_z += yoffset;
}

void Camera::getUniformLocation(unsigned int shader)
{
    camera_loc = glGetUniformLocation(shader, "view");
}
    
void Camera::Update(GLFWwindow *window, float dt)
{
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) position.x += speed * dt;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) position.x -= speed * dt;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) position.y += speed * dt;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) position.y -= speed * dt;

    position.z = zoom_senstivity * camera_z;

    glfwSetScrollCallback(window, scroll_callback);

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

    model_matrix.entries[12] = -position.x;
    model_matrix.entries[13] = -position.y;
    model_matrix.entries[14] = position.z;
    model_matrix.entries[15] = 1.0f; 

    glUniformMatrix4fv(camera_loc,1, GL_FALSE, model_matrix.entries);
}