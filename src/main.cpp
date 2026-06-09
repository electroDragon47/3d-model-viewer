#include "project.h"

int main()
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
    unsigned int importShader  = createShader("shaders/i_vertex.shader", "shaders/i_fragment.shader");
    
  
    // cube constructor
    Cube cube;
    Light lig;
    Model pikachu;
    pikachu.import("assets/pikachu_B.obj");

    // camera 
    Camera camera;

    // projection matrix
    mat4f  projection_matrix = create_perspective_projection(45.0f, screenAspectRatio, 0.1f, 10.0f);

    // uniform locations
    // glUseProgram(importShader);
    // lig.getUniformLocation(importShader);
    // cube.getUniformLocation(importShader);
    // camera.getUniformLocation(importShader);
    // lig.getUniformLocation(importShader);

    cube.getUniformLocation(shaderProgram);
    camera.getUniformLocation(shaderProgram);

    glUseProgram(importShader);
    pikachu.getUniformLocation(importShader);
    unsigned int camera_loc = glGetUniformLocation(importShader, "view");

    // projection
    // unsigned int projection_loc = glGetUniformLocation(shaderProgram, "projection");
    // glUniformMatrix4fv(projection_loc,1,GL_FALSE, projection_matrix.entries);

    unsigned int projection_loc = glGetUniformLocation(importShader, "projection");
    glUniformMatrix4fv(projection_loc,1,GL_FALSE, projection_matrix.entries);
    

    float time_elapsed = 0.0f; // for deltatime

    
    glEnable(GL_DEPTH_TEST); // to enable depth ig

    // imgui initialization
    imguiinit(window);
    
    

    while (!glfwWindowShouldClose(window))
    {
        
        glUseProgram(shaderProgram);
        // delta time
        float current_time = glfwGetTime();
        float deltaTime = current_time - time_elapsed;
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        imgui_newframe();
        cube.Update();
        camera.Update(window, deltaTime);
        lig.Update();
        cube.Draw();
        glUseProgram(importShader);
        glUniformMatrix4fv(camera_loc,1,GL_FALSE, camera.model_matrix.entries);
        pikachu.Update();
        pikachu.meshDraw();

        // impui rendering
        std::cout << "loop running" << "\n";

        
        ImGui::SetNextWindowPos(ImVec2(0, 0),ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, 300),ImGuiCond_Always);

        ImGui::Begin("Inspector",nullptr,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    //     if (ImGui::Button("Load OBJ"))
    // {
    //     std::string path = OpenFileDialog();

    //     if (!path.empty())
    //     {
    //         printf("Selected: %s\n", path.c_str());
    //         Importer importer;
    //         importer.loadModel(path);
    
    //         for(const auto& meshData : importer.getMeshes())
    //         {
    //             gpuMeshes.emplace_back(meshData.vertices,meshData.indices);
    //         }
    //     }
    // }
        cube.DrawUI();
        pikachu.DrawUI();
        camera.DrawUI();
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
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}