#pragma once

#include "gl/glew.h"
#include <iostream>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "matrix.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class Vertex
{
public:
    vec3f position;
    vec3f normal;
};

class Model
{
public:
    
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int indexCount;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    vec3f position;
    vec3f rotation;
    vec3f scale;
    mat4f model;

    unsigned int model_loc;
    unsigned int scale_loc;

    Model();
    void getUniformLocation(unsigned int shader);
    void Update();
    void import(std::string path);
    void createMesh();
    void meshDraw();
    void DrawUI();
    ~Model();
};

