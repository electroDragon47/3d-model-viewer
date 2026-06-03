#define GLEW_STATIC

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "matrix.h"
#include "shapes.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    unsigned int shaderProgram = createShader("shaders/vertex.shader", "shaders/fragment.shader");


    // make shader , buffers , vertices and then render

    Cube cube;
    cube.scale.x = 2.0f;
    cube.scale.y = 1.0f;
    cube.scale.z = 1.0f;
    cube.position = {1.0f, 1.0f, 0.0f};

    createVaoVbo(&cube.VAO, &cube.VBO);

    mat4f cube_model = create_translation(cube.position);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        // render here

        unsigned int scale_loc = glGetUniformLocation(shaderProgram, "scale");
        glUniform3fv(scale_loc,1,&cube.scale.x);

        unsigned int model_loc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(model_loc,1,GL_FALSE, cube_model.entries);

        glDrawArrays(GL_TRIANGLES, 0 , 36);


        glBindVertexArray(cube.VAO);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}