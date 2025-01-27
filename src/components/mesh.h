#ifndef MESH_H
#define MESH_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QString>
#include <glm/glm.hpp>

#include <memory>

namespace mini_creator {
namespace components {

class Mesh : protected QOpenGLFunctions {
public:
  Mesh();
  ~Mesh();

  void SetVertices(const std::vector<glm::vec3> &vertices);
  void SetNormals(const std::vector<glm::vec3> &normals);
  void SetTexCoords(const std::vector<glm::vec2> &texCoords);
  void SetIndices(const std::vector<uint32_t> &indices);
  // void SetMaterial(std::shared_ptr<Material> material);

  const std::vector<glm::vec3> &GetVertices() { return vertices_; }

  void Draw(QOpenGLShaderProgram *shader_program);

private:
  QOpenGLBuffer vbo_vertices_;
  QOpenGLBuffer vbo_normals_;
  QOpenGLBuffer vbo_texCoords_;
  QOpenGLBuffer ebo_;

  // std::shared_ptr<Material> material_;
  std::vector<glm::vec3> vertices_;
  int index_count_;
};

} // namespace components
} // namespace mini_creator

#endif // MESH_H
