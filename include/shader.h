

#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>

std::string getShader(const char* path);
unsigned int createShader(const char* vs, const char* fs);
