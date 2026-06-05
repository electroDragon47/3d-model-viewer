#include "shapes.h"

Cube::Cube()
{
    position = {0.0f, 0.0f, 0.0f};
    rotation = {0.0f, 0.0f, 0.0f};
    scale = {1.0f, 1.0f, 1.0f};
}

void createVaoVbo(unsigned int *VAO, unsigned int *VBO)
{
    float vertices[] =
{
    // Front (+Z)
    -0.25f,  0.25f,  0.25f,  1.0f,0.0f,0.0f,  0.0f,0.0f, 1.0f,
     0.25f,  0.25f,  0.25f,  1.0f,0.0f,0.0f,  0.0f,0.0f, 1.0f,
     0.25f, -0.25f,  0.25f,  1.0f,0.0f,0.0f,  0.0f,0.0f, 1.0f,

    -0.25f,  0.25f,  0.25f,  1.0f,0.0f,0.0f,  0.0f,0.0f, 1.0f,
     0.25f, -0.25f,  0.25f,  1.0f,0.0f,0.0f,  0.0f,0.0f, 1.0f,
    -0.25f, -0.25f,  0.25f,  1.0f,0.0f,0.0f,  0.0f,0.0f, 1.0f,

    // Back (-Z)
    -0.25f,  0.25f, -0.25f,  0.0f,0.0f,1.0f,  0.0f,0.0f,-1.0f,
     0.25f, -0.25f, -0.25f,  0.0f,0.0f,1.0f,  0.0f,0.0f,-1.0f,
     0.25f,  0.25f, -0.25f,  0.0f,0.0f,1.0f,  0.0f,0.0f,-1.0f,

    -0.25f,  0.25f, -0.25f,  0.0f,0.0f,1.0f,  0.0f,0.0f,-1.0f,
    -0.25f, -0.25f, -0.25f,  0.0f,0.0f,1.0f,  0.0f,0.0f,-1.0f,
     0.25f, -0.25f, -0.25f,  0.0f,0.0f,1.0f,  0.0f,0.0f,-1.0f,

    // Left (-X)
    -0.25f,  0.25f, -0.25f,  0.0f,1.0f,0.0f, -1.0f,0.0f,0.0f,
    -0.25f,  0.25f,  0.25f,  0.0f,1.0f,0.0f, -1.0f,0.0f,0.0f,
    -0.25f, -0.25f,  0.25f,  0.0f,1.0f,0.0f, -1.0f,0.0f,0.0f,

    -0.25f,  0.25f, -0.25f,  0.0f,1.0f,0.0f, -1.0f,0.0f,0.0f,
    -0.25f, -0.25f,  0.25f,  0.0f,1.0f,0.0f, -1.0f,0.0f,0.0f,
    -0.25f, -0.25f, -0.25f,  0.0f,1.0f,0.0f, -1.0f,0.0f,0.0f,

    // Right (+X)
     0.25f,  0.25f,  0.25f,  1.0f,1.0f,0.0f,  1.0f,0.0f,0.0f,
     0.25f,  0.25f, -0.25f,  1.0f,1.0f,0.0f,  1.0f,0.0f,0.0f,
     0.25f, -0.25f, -0.25f,  1.0f,1.0f,0.0f,  1.0f,0.0f,0.0f,

     0.25f,  0.25f,  0.25f,  1.0f,1.0f,0.0f,  1.0f,0.0f,0.0f,
     0.25f, -0.25f, -0.25f,  1.0f,1.0f,0.0f,  1.0f,0.0f,0.0f,
     0.25f, -0.25f,  0.25f,  1.0f,1.0f,0.0f,  1.0f,0.0f,0.0f,

    // Top (+Y)
    -0.25f,  0.25f, -0.25f,  1.0f,0.0f,1.0f,  0.0f,1.0f,0.0f,
     0.25f,  0.25f, -0.25f,  1.0f,0.0f,1.0f,  0.0f,1.0f,0.0f,
     0.25f,  0.25f,  0.25f,  1.0f,0.0f,1.0f,  0.0f,1.0f,0.0f,

    -0.25f,  0.25f, -0.25f,  1.0f,0.0f,1.0f,  0.0f,1.0f,0.0f,
     0.25f,  0.25f,  0.25f,  1.0f,0.0f,1.0f,  0.0f,1.0f,0.0f,
    -0.25f,  0.25f,  0.25f,  1.0f,0.0f,1.0f,  0.0f,1.0f,0.0f,

    // Bottom (-Y)
    -0.25f, -0.25f,  0.25f,  0.0f,1.0f,1.0f,  0.0f,-1.0f,0.0f,
     0.25f, -0.25f,  0.25f,  0.0f,1.0f,1.0f,  0.0f,-1.0f,0.0f,
     0.25f, -0.25f, -0.25f,  0.0f,1.0f,1.0f,  0.0f,-1.0f,0.0f,

    -0.25f, -0.25f,  0.25f,  0.0f,1.0f,1.0f,  0.0f,-1.0f,0.0f,
     0.25f, -0.25f, -0.25f,  0.0f,1.0f,1.0f,  0.0f,-1.0f,0.0f,
    -0.25f, -0.25f, -0.25f,  0.0f,1.0f,1.0f,  0.0f,-1.0f,0.0f
};
    
    glGenVertexArrays(1, VAO); // use pointer
    glGenBuffers(1, VBO);
    glBindVertexArray(*VAO); // use value

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0); 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(*VAO);
}


