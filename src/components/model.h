#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QString>
#include <glm/glm.hpp>

#include "mesh.h"

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

  const glm::vec3 &GetTranslation() const { return translation_; }
  const glm::vec3 &GetRotation() const { return rotation_; }
  const glm::vec3 &GetScale() const { return scale_; }
  const glm::vec3 &GetMinBound() { return minBound_; }
  const glm::vec3 &GetMaxBound() { return maxBound_; }
  const std::vector<std::shared_ptr<Mesh>> &GetMeshes() { return meshes_; }
  const QString &GetName() { return name_; }

  void Draw(const QMatrix4x4 &view_matrix, const QMatrix4x4 &projection_matrix,
            const QVector3D &light_position, const QVector3D &camera_position);

private:
  void LoadShaders();

  QOpenGLShaderProgram *shader_program_;
  std::vector<std::shared_ptr<Mesh>> meshes_;

  QString name_;
  glm::vec3 translation_;
  glm::vec3 rotation_;
  glm::vec3 scale_;
  glm::vec3 minBound_, maxBound_;
};

} // namespace components
} // namespace mini_creator

#endif // MODEL_H
