#pragma once


#include <vector>

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices,
         const std::vector<unsigned int>& indices);

    void draw();

private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int indexCount;
};