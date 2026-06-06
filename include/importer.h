#pragma once
#include <vector>
#include <string>

#include <assimp/scene.h>

struct MeshData
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

class Importer
{
public:
    bool loadModel(const std::string& path);

    const std::vector<MeshData>& getMeshes() const;

private:
    std::vector<MeshData> meshes;

    void processNode(aiNode* node, const aiScene* scene);
    MeshData processMesh(aiMesh* mesh);
};