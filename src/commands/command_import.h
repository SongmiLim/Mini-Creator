#ifndef COMMAND_IMPORT_H
#define COMMAND_IMPORT_H

#include <QObject>
#include <QString>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "graphics/mesh.h"
#include "graphics/model.h"

namespace mini_creator {
namespace commands {

class CommandImport : public QObject {
  Q_OBJECT

public:
  static CommandImport &instance() {
    static CommandImport instance;
    return instance;
  }

  void Execute(const QString &file_path);
  void ImportTestCubeModel();

signals:
  void ProgressUpdated(int value);

private:
  CommandImport() = default;
  void ProcessNode(aiNode *node, const aiScene *scene,
                   std::shared_ptr<graphics::Model> &model);
  std::shared_ptr<graphics::Mesh> ProcessMesh(aiMesh *mesh,
                                              const aiScene *scene);
  QString file_path_ = "";
  int progress_value_ = 0;
};

} // namespace commands
} // namespace mini_creator

#endif // COMMAND_IMPORT_H
