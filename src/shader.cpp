#include "shader.h"

std::string getShader(const char* path)
{
    std::ifstream shaderFile(path);
    if(!shaderFile.is_open())
    {
        std::cout << "file not opne" << "\n";
    }
    else if(shaderFile.is_open())
    {
        std::cout << "file opne" << "\n";
    }
    std::cout << path << "\n";
    std::string allText;
    std::string myText; 
    while (getline(shaderFile, myText))
    {
        allText += myText + '\n';
    }
    return allText;
}

unsigned int createShader(const char* v, const char* f)
{
    std::string vertexSrc = getShader(v); // "res/vertex.shader"
    const char *vs = vertexSrc.c_str();

    std::string fragSrc = getShader(f);
    const char *fs = fragSrc.c_str();

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}