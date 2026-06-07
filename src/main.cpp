#include "project.h"

int main()
{
    std::string name;
    std::cout << "Enter 3D model file path: ";
    std::cin >> name;

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

    // unsigned int shaderProgram = createShader("shaders/vertex.shader", "shaders/fragment.shader");
    unsigned int importShader  = createShader("shaders/i_vertex.shader", "shaders/i_fragment.shader");

    //  [importer.h and mesh.h is generated using ai, learn later]
    // assimp
    Importer importer;
    importer.loadModel(name);
    std::vector<Mesh> gpuMeshes;
    for(const auto& meshData : importer.getMeshes())
    {
        gpuMeshes.emplace_back(meshData.vertices,meshData.indices);
    }
  
    // cube constructor
    Cube cube;
    Light lig;

    // camera 
    Camera camera;

    // projection matrix
    mat4f  projection_matrix = create_perspective_projection(45.0f, screenAspectRatio, 0.1f, 10.0f);

    // uniform locations
    lig.getUniformLocation(importShader);
    cube.getUniformLocation(importShader);
    camera.getUniformLocation(importShader);

    // projection
    unsigned int projection_loc = glGetUniformLocation(importShader, "projection");
    glUniformMatrix4fv(projection_loc,1,GL_FALSE, projection_matrix.entries);
    

    float time_elapsed = 0.0f; // for deltatime

    
    glEnable(GL_DEPTH_TEST); // to enable depth ig

    // imgui initialization
    imguiinit(window);
    

    while (!glfwWindowShouldClose(window))
    {
        // delta time
        float current_time = glfwGetTime();
        float deltaTime = current_time - time_elapsed;
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        imgui_newframe();

        // glUseProgram(shaderProgram);
        cube.Update();
        camera.Update(window, deltaTime);
        lig.Update();
        // cube.Draw();

        // ass imp 
        // glUseProgram(importShader);
        for(auto& mesh : gpuMeshes) mesh.draw();

        // impui rendering
        ImGui::Begin("Inspector");
        ImGui::Text("cube");
        ImGui::SliderFloat3("Position", &cube.position.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("rotation", &cube.rotation.x, -180.0f, 180.0f);
        ImGui::SliderFloat3("scale", &cube.scale.x, 0.0f, 5.0f);
        ImGui::SliderFloat3("lightPosition", &lig.position.x, -5.0f, 5.0f);
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
    glDeleteProgram(importShader);
    glfwTerminate();
    return 0;
}