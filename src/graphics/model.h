#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QString>
#include <glm/glm.hpp>


#include "graphics/mesh.h"
#include "graphics/shader_program.h"


namespace mini_creator {
namespace graphics {

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
  const glm::vec3 &GetMinBound();
  const glm::vec3 &GetMaxBound();
  const std::vector<std::shared_ptr<Mesh>> &GetMeshes() const {
    return meshes_;
  }
  const QString &GetName() const { return name_; }

  void Draw(const QMatrix4x4 &view_matrix, const QMatrix4x4 &projection_matrix,
            const QVector3D &light_position, const QVector3D &camera_position);
  void DrawBoundingBox(const QMatrix4x4 &view_matrix,
                       const QMatrix4x4 &projection_matrix);

private:
  void InitializeBoundingBox();
  void UpdateBoundingBox();

  std::vector<std::shared_ptr<Mesh>> meshes_;
  std::shared_ptr<ShaderProgram> shader_program_;
  std::shared_ptr<ShaderProgram> bounding_box_shader_;
  QOpenGLBuffer vbo_{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer ebo_{QOpenGLBuffer::IndexBuffer};

  QString name_;
  glm::vec3 translation_{0.0f};
  glm::vec3 rotation_{0.0f};
  glm::vec3 scale_{1.0f};
  glm::vec3 min_bound_{FLT_MAX};
  glm::vec3 max_bound_{-FLT_MAX};
  bool bounding_box_initialized_ = false;
};

} // namespace graphics
} // namespace mini_creator

#endif // MODEL_H
