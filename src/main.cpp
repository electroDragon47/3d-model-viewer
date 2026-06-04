#define GLEW_STATIC

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

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

    float screenAspectRatio = ((float)WINDOW_WIDTH)/((float)WINDOW_HEIGHT);
    window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "3d Model Viewer", NULL, NULL);
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

    // projection matrix
    mat4f  projection_matrix = create_perspective_projection(45.0f, screenAspectRatio, 0.1f, 10.0f);
    // uniform locations
    unsigned int scale_loc = glGetUniformLocation(shaderProgram, "scale");
    unsigned int model_loc = glGetUniformLocation(shaderProgram, "model");
    unsigned int camera_loc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projection_loc = glGetUniformLocation(shaderProgram, "projection");

    // uploading projection matrix once
    glUniformMatrix4fv(projection_loc,1,GL_FALSE, projection_matrix.entries);

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
        // delta time
        float current_time = glfwGetTime();
        float deltaTime = current_time - time_elapsed;
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // using gl program
        glUseProgram(shaderProgram);

        // uploading scale data
        
        // making modal matrix
        cube_model = create_translation(cube.position, cube.rotation);
        camera.Update(window, deltaTime);
        
        
        // uploading to gpu
        glUniform3fv(scale_loc,1,&cube.scale.x); // uploading scale data
        glUniformMatrix4fv(model_loc,1,GL_FALSE, cube_model.entries); // uploading modal data
        glUniformMatrix4fv(camera_loc,1, GL_FALSE, camera.model_matrix.entries); // uploading view data (camera matrix)

        glBindVertexArray(cube.VAO);
        glDrawArrays(GL_TRIANGLES, 0 , 36);

        // impui rendering
        ImGui::Begin("Inspector");
        ImGui::Text("cube");
        ImGui::SliderFloat3("Position", &cube.position.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("rotation", &cube.rotation.x, -180.0f, 180.0f);
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

     glDeleteVertexArrays(1, &cube.VAO);
    glDeleteBuffers(1, &cube.VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}