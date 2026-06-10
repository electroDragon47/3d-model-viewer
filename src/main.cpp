#include "project.h"

int main()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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

    if(!glewInit() == GLEW_OK) std::cout << "glew Not Loaded\n";

    unsigned int importShader  = createShader("shaders/i_vertex.shader", "shaders/i_fragment.shader");
    glUseProgram(importShader);
    
    Light lig; // light
    Camera camera; // camera
    Model model; // model

    mat4f  projection_matrix = create_perspective_projection(45.0f, screenAspectRatio, 0.1f, 10.0f);
    
    lig.getUniformLocation(importShader);
    camera.getUniformLocation(importShader);
    model.getUniformLocation(importShader);
    
    unsigned int camera_loc = glGetUniformLocation(importShader, "view");
    unsigned int projection_loc = glGetUniformLocation(importShader, "projection");
    glUniformMatrix4fv(projection_loc,1,GL_FALSE, projection_matrix.entries);

    float last_frame_time = 0.0f; // for deltatime
    
    glEnable(GL_DEPTH_TEST); // to enable depth ig

    // imgui initialization
    imguiinit(window);
    
    bool modelLoaded = false;

    while (!glfwWindowShouldClose(window))
    {
        // delta time
        float current_time = glfwGetTime();
        float deltaTime = current_time - last_frame_time;

        imgui_newframe();
 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     
        if(modelLoaded)
        {
            glUseProgram(importShader);
            lig.Update();
            camera.Update(window, deltaTime);
            glUniformMatrix4fv(camera_loc,1,GL_FALSE, camera.model_matrix.entries);
            model.Update();
            model.meshDraw();
        }
        
        ImGui::SetNextWindowPos(ImVec2(0, 0),ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, 500),ImGuiCond_Always);

        ImGui::Begin("Inspector",nullptr,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        if (ImGui::Button("Load OBJ"))
        {
            std::string path = OpenFileDialog();
            std::cout << "load buttton";

            if (!path.empty())
            {
                printf("Selected: %s\n", path.c_str());
                model.import(path);
                modelLoaded = true;
            }
        }
    
        camera.DrawUI();
        if(modelLoaded) model.DrawUI();
        lig.DrawUI();
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
        last_frame_time = current_time;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glDeleteProgram(importShader);
    glfwTerminate();
    return 0;
}