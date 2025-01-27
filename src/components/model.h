#ifndef MODEL_H
#define MODEL_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QString>
#include <glm/glm.hpp>

#include "mesh.h"
#include <memory>

namespace mini_creator {
namespace components {

class Model : protected QOpenGLFunctions {
public:
  Model(const QString &name);
  ~Model();

  void AddMesh(std::shared_ptr<Mesh> mesh);

  void SetTranslation(const glm::vec3 &translation);
  void SetRotation(const glm::vec3 &rotation);
  void SetScale(const glm::vec3 &scale);
  const glm::vec3 &GetMinBound() { return minBound_; }
  const glm::vec3 &GetMaxBound() { return maxBound_; }
  const std::vector<std::shared_ptr<Mesh>> &GetMeshes() { return meshes_; }
  const QString &GetName() { return name_; }

  void Draw(QOpenGLShaderProgram *shader_program);

private:
  QString name_;
  std::vector<std::shared_ptr<Mesh>> meshes_;
  glm::vec3 translation_;
  glm::vec3 rotation_;
  glm::vec3 scale_;
  glm::vec3 minBound_, maxBound_;
};

} // namespace components
} // namespace mini_creator

#endif // MODEL_H
