#include "light.h"

Light::Light()
{
    position = {1.0f, 1.0f, 2.0f};
    color = {1.0f, 1.0f, 1.0f};
    
}

void Light::getUniformLocation(unsigned int shaderProgram)
{
    pos_loc = glGetUniformLocation(shaderProgram, "lightPos");
    color_loc = glGetUniformLocation(shaderProgram, "lightColor");
    glUniform3fv(color_loc, 1, &color.x);
}

void Light::Update()
{
    glUniform3fv(pos_loc,1,&position.x);
}

