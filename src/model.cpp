#include "model.h"

Model::Model()
{
    std::cout << "model created" << "\n";
    position = {0.0f, 0.0f, 0.0f};
    rotation = {0.0f, 0.0f, 0.0f};
    scale = {1.0f, 1.0f, 1.0f};
}

void Model::import(std::string path)
{

    // importer object
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene)
    {
        std::cout << importer.GetErrorString() << "\n";
    }
    std::cout << scene->mNumMeshes; // get mesh count

    aiMesh *mesh = scene->mMeshes[0];
    mesh->mVertices;


    // storeing position vertices in vertex vector
    for (int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        aiVector3D pos = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];
        vertex.position = {pos.x, pos.y, pos.z};
        vertex.normal = {normal.x, normal.y, normal.z};
        vertices.push_back(vertex);
    }
    // for normals
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    createMesh();
}

void Model::createMesh()
{
    indexCount = indices.size();
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Model::meshDraw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void Model::getUniformLocation(unsigned int shader)
{
    scale_loc = glGetUniformLocation(shader, "scale");
    model_loc = glGetUniformLocation(shader, "model");
}

void Model::Update()
{
    glUniform3fv(scale_loc,1,&scale.x); // uploading scale data
    model = create_translation(position, rotation);
    glUniformMatrix4fv(model_loc,1,GL_FALSE, model.entries); 
}

void Model::DrawUI()
{
    ImGui::Text("Model");
    ImGui::SliderFloat3("Position##model", &position.x, -5.0f, 5.0f);
    ImGui::SliderFloat3("rotation##model", &rotation.x, -180.0f, 180.0f);
    ImGui::SliderFloat3("scale##model", &scale.x, 0.0f, 5.0f);
}
// destructor
Model::~Model()
{
    if (vao) glDeleteVertexArrays(1, &vao);
    if (vbo) glDeleteBuffers(1, &vbo);
    if (ebo) glDeleteBuffers(1, &ebo);
}