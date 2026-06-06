#include "importer.h"

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

bool Importer::loadModel(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_JoinIdenticalVertices
    );

    if (!scene ||
        scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode)
    {
        std::cerr << importer.GetErrorString() << '\n';
        return false;
    }

    meshes.clear();

    processNode(scene->mRootNode, scene);

    return true;
}

const std::vector<MeshData>& Importer::getMeshes() const
{
    return meshes;
}

void Importer::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

MeshData Importer::processMesh(aiMesh* mesh)
{
    MeshData data;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        // Position
        data.vertices.push_back(mesh->mVertices[i].x);
        data.vertices.push_back(mesh->mVertices[i].y);
        data.vertices.push_back(mesh->mVertices[i].z);

        // Normal
        if (mesh->HasNormals())
        {
            data.vertices.push_back(mesh->mNormals[i].x);
            data.vertices.push_back(mesh->mNormals[i].y);
            data.vertices.push_back(mesh->mNormals[i].z);
        }
        else
        {
            data.vertices.push_back(0.0f);
            data.vertices.push_back(0.0f);
            data.vertices.push_back(0.0f);
        }
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            data.indices.push_back(face.mIndices[j]);
        }
    }

    return data;
}