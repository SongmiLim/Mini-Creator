#ifndef COMMAND_IMPORT_H
#define COMMAND_IMPORT_H

#include <QString>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "../components/mesh.h"
#include "../components/model.h"
namespace mini_creator {
namespace commands {

class CommandImport {

public:
  static void Execute(const QString &file_path);
  static void ImportTestCubeModel();

private:
  static void ProcessNode(aiNode *node, const aiScene *scene,
                          std::shared_ptr<components::Model> &model);
  static std::shared_ptr<components::Mesh> ProcessMesh(aiMesh *mesh,
                                                       const aiScene *scene);
  static QString file_path_;
};

} // namespace commands
} // namespace mini_creator

#endif // COMMAND_IMPORT_H
