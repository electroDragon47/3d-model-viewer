#include "shapes.h"

void createVaoVbo(unsigned int *VAO, unsigned int *VBO)
{
    float vertices[] =
{
    // Front face (z = +0.25) - Red
    -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 0.0f,
     0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 0.0f,
     0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 0.0f,

    -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 0.0f,
     0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 0.0f,
    -0.25f, -0.25f,  0.25f,  1.0f, 0.0f, 0.0f,

    // Back face (z = -0.25) - Blue
    -0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,  
     0.25f, -0.25f, -0.25f,  0.0f, 0.0f, 1.0f,  
     0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,  

    -0.25f,  0.25f, -0.25f,  0.0f, 0.0f, 1.0f,  
    -0.25f, -0.25f, -0.25f,  0.0f, 0.0f, 1.0f,  
     0.25f, -0.25f, -0.25f,  0.0f, 0.0f, 1.0f,  

    // Left face (x = -0.25) - Green
    -0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 0.0f,  
    -0.25f,  0.25f,  0.25f,  0.0f, 1.0f, 0.0f,  
    -0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 0.0f,  

    -0.25f,  0.25f, -0.25f,  0.0f, 1.0f, 0.0f,  
    -0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 0.0f,  
    -0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 0.0f,  

    // Right face (x = +0.25) - Yellow
     0.25f,  0.25f,  0.25f,  1.0f, 1.0f, 0.0f,
     0.25f,  0.25f, -0.25f,  1.0f, 1.0f, 0.0f,
     0.25f, -0.25f, -0.25f,  1.0f, 1.0f, 0.0f,

     0.25f,  0.25f,  0.25f,  1.0f, 1.0f, 0.0f,
     0.25f, -0.25f, -0.25f,  1.0f, 1.0f, 0.0f,
     0.25f, -0.25f,  0.25f,  1.0f, 1.0f, 0.0f,

    // Top face (y = +0.25) - Magenta
    -0.25f,  0.25f, -0.25f,  1.0f, 0.0f, 1.0f,
     0.25f,  0.25f, -0.25f,  1.0f, 0.0f, 1.0f,
     0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,

    -0.25f,  0.25f, -0.25f,  1.0f, 0.0f, 1.0f,
     0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,
    -0.25f,  0.25f,  0.25f,  1.0f, 0.0f, 1.0f,

    // Bottom face (y = -0.25) - Cyan
    -0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 1.0f,  
     0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 1.0f,  
     0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,  

    -0.25f, -0.25f,  0.25f,  0.0f, 1.0f, 1.0f,  
     0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f,  
    -0.25f, -0.25f, -0.25f,  0.0f, 1.0f, 1.0f 
};
    
    glGenVertexArrays(1, VAO); // use pointer
    glGenBuffers(1, VBO);
    glBindVertexArray(*VAO); // use value

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(*VAO);
}

