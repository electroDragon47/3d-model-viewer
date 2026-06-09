#pragma once

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1000

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "imgui_imp.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "light.h"
#include "shader.h"
#include "matrix.h"
#include "shapes.h"
#include "camera.h"
// #include "importer.h"
// #include "mesh.h"
#include "loader.h"
#include "model.h"
