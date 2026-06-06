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

    //  [importer.h and mesh.h is generated using ai, learn later]
    // assimp
    Importer importer;
    importer.loadModel("assets/Pikachu_B.obj");
    std::vector<Mesh> gpuMeshes;
    for(const auto& meshData : importer.getMeshes())
    {
        gpuMeshes.emplace_back(meshData.vertices,meshData.indices);
    }
  
    // cube constructor
    Cube cube;
    Cube cube2;
    Light lig;

    // camera 
    Camera camera;

    createVaoVbo(&cube.VAO, &cube.VBO);
    createVaoVbo(&cube2.VAO, &cube2.VBO);

    cube2.position = {0.5f, 0.0f, 0.0f};
    cube2.scale = {0.5f, 0.5f, 0.5f};

    mat4f cube_model = create_translation(cube.position, cube.rotation);
    mat4f cube2_model = create_translation(cube2.position, cube2.rotation);

    // projection matrix
    mat4f  projection_matrix = create_perspective_projection(45.0f, screenAspectRatio, 0.1f, 10.0f);

    // uniform locations
    unsigned int light_pos_loc = glGetUniformLocation(shaderProgram, "lightPos");
    unsigned int light_color_loc = glGetUniformLocation(shaderProgram, "lightColor");
    unsigned int scale_loc = glGetUniformLocation(shaderProgram, "scale");
    unsigned int model_loc = glGetUniformLocation(shaderProgram, "model");
    unsigned int camera_loc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projection_loc = glGetUniformLocation(shaderProgram, "projection");
    
    // uploading projection matrix once
    glUniformMatrix4fv(projection_loc,1,GL_FALSE, projection_matrix.entries);
    glUniform3fv(light_color_loc, 1, &lig.color.x);

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

        // imgui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // using gl program
        glUseProgram(shaderProgram);
        
        // making modal matrix
        cube_model = create_translation(cube.position, cube.rotation);
        camera.Update(window, deltaTime);
        
        // uploading to gpu
        glUniform3fv(scale_loc,1,&cube.scale.x); // uploading scale data
        glUniformMatrix4fv(model_loc,1,GL_FALSE, cube_model.entries); // uploading modal data
        glUniformMatrix4fv(camera_loc,1, GL_FALSE, camera.model_matrix.entries); // uploading view data (camera matrix)
        glUniform3fv(light_pos_loc,1,&lig.position.x);

        // glBindVertexArray(cube.VAO);
        // glDrawArrays(GL_TRIANGLES, 0 , 36);

        // glUniform3fv(scale_loc,1,&cube2.scale.x); // uploading scale data
        // glUniformMatrix4fv(model_loc,1,GL_FALSE, cube2_model.entries); // uploading modal data
        // glDrawArrays(GL_TRIANGLES, 0 , 36);


        // ass imp 
        for(auto& mesh : gpuMeshes)
        {
            mesh.draw();
        }



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
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}