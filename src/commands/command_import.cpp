#include "command_import.h"

#include <QDebug>
#include <QString>

#include <vector>

#include "../core/model_manager.h"

namespace mini_creator {
namespace commands {

void CommandImport::Execute(const QString &file_path) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
      file_path.toStdString(),
      aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !scene->mRootNode) {
    qCritical() << "Failed to load model:" << file_path;
    return;
  }

  qDebug() << "Successfully loaded model:" << file_path;

  std::shared_ptr<components::Model> model =
      std::make_shared<components::Model>(file_path);
  ProcessNode(scene->mRootNode, scene, model);
  core::ModelManager::Instance().AddModel(model);
}

void CommandImport::ProcessNode(
    aiNode *node, const aiScene *scene,
    std::shared_ptr<components::Model> &model) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    auto meshIndex = node->mMeshes[i];
    auto mesh = scene->mMeshes[meshIndex];
    std::shared_ptr<components::Mesh> newMesh = ProcessMesh(mesh, scene);
    model->AddMesh(newMesh);
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i], scene, model);
  }
}

std::shared_ptr<components::Mesh>
CommandImport::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  std::shared_ptr<components::Mesh> newMesh =
      std::make_shared<components::Mesh>();

  std::vector<glm::vec3> vertices(mesh->mNumVertices);
  std::vector<glm::vec3> normals(mesh->mNumVertices);
  std::vector<uint32_t> indices(mesh->mNumFaces * 3);

  bool hasTexCoords = mesh->HasTextureCoords(0);
  std::vector<glm::vec2> texCoords;
  if (hasTexCoords) {
    texCoords.resize(mesh->mNumVertices);
  }

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    vertices[i] = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y,
                            mesh->mVertices[i].z);

    normals[i] = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y,
                           mesh->mNormals[i].z);
    if (hasTexCoords) {
      texCoords[i] =
          glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
    }
  }

  indices.resize(mesh->mNumFaces * 3);
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    indices[3 * i] = mesh->mFaces[i].mIndices[0];
    indices[3 * i + 1] = mesh->mFaces[i].mIndices[1];
    indices[3 * i + 2] = mesh->mFaces[i].mIndices[2];
  }

  newMesh->SetVertices(vertices);
  newMesh->SetNormals(normals);
  newMesh->SetIndices(indices);
  if (hasTexCoords) {
    newMesh->SetTexCoords(texCoords);
  }
  return newMesh;
}

void CommandImport::ImportTestCubeModel() {
  std::vector<glm::vec3> cubeVertices = {
      {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f},
      {0.5f, 0.5f, -0.5f},   {-0.5f, 0.5f, -0.5f},

      {-0.5f, -0.5f, 0.5f},  {0.5f, -0.5f, 0.5f},
      {0.5f, 0.5f, 0.5f},    {-0.5f, 0.5f, 0.5f}};

  std::vector<uint32_t> cubeIndices = {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4,
                                       0, 4, 7, 7, 3, 0, 1, 5, 6, 6, 2, 1,
                                       0, 1, 5, 5, 4, 0, 3, 2, 6, 6, 7, 3};

  std::shared_ptr<components::Model> model =
      std::make_shared<components::Model>("TestCube");
  std::shared_ptr<components::Mesh> mesh = std::make_shared<components::Mesh>();
  mesh->SetVertices(cubeVertices);
  mesh->SetIndices(cubeIndices);
  model->AddMesh(mesh);
  core::ModelManager::Instance().AddModel(model);
}

} // namespace commands
} // namespace mini_creator
