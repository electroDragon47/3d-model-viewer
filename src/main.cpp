#define GLEW_STATIC

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "matrix.h"
#include "shapes.h"
#include "camera.h"




int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(600, 600, "3d Model Viewer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    unsigned int shaderProgram = createShader("shaders/vertex.shader", "shaders/fragment.shader");


    // cube constructor
    Cube cube;

    // camera 
    Camera camera;

    createVaoVbo(&cube.VAO, &cube.VBO);

    mat4f cube_model = create_translation(cube.position, cube.rotation);
    float time_elapsed = 0.0f;

    glEnable(GL_DEPTH_TEST);

    // Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window))
    {
        float current_time = glfwGetTime();
        float deltaTime = current_time - time_elapsed;
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        glUseProgram(shaderProgram);
        // render here

        // cube.rotation.y += 50.f * deltaTime;

        unsigned int scale_loc = glGetUniformLocation(shaderProgram, "scale");
        glUniform3fv(scale_loc,1,&cube.scale.x);

        cube_model = create_translation(cube.position, cube.rotation);
        unsigned int model_loc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(model_loc,1,GL_FALSE, cube_model.entries);

        unsigned int camera_loc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(camera_loc,1, GL_FALSE, camera.model_matrix.entries);

        glDrawArrays(GL_TRIANGLES, 0 , 36);

        glBindVertexArray(cube.VAO);

        ImGui::Begin("Inspector");
        ImGui::Text("cube");
        ImGui::SliderFloat3("Position", &cube.position.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("rotation", &cube.rotation.x, -15.0f, 15.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
        time_elapsed = current_time;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}