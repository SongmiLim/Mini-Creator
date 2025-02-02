#ifndef MESH_H
#define MESH_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
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
  void SetIndices(const std::vector<uint32_t> &indices);

  void SetTexCoords(const std::vector<glm::vec2> &texCoords);
  void LoadTexture(const QString &file_path);
  void CreateDefaultWhiteTexture();

  void SetDiffuseColor(const glm::vec3 &color);
  void SetSpecularColor(const glm::vec3 &color);
  void SetAmbientColor(const glm::vec3 &color);
  void SetShininess(float shininess);

  const std::vector<glm::vec3> &GetVertices() const { return vertices_; }

  void Draw(QOpenGLShaderProgram *shader_program);

private:
  QOpenGLBuffer vbo_vertices_;
  QOpenGLBuffer vbo_normals_;
  QOpenGLBuffer vbo_texCoords_;
  QOpenGLBuffer ebo_;
  QOpenGLTexture *texture_ = nullptr;

  glm::vec3 diffuse_color_{1.0f, 1.0f, 1.0f};
  glm::vec3 specular_color_{1.0f, 1.0f, 1.0f};
  glm::vec3 ambient_color_{1.0f, 1.0f, 1.0f};
  float shininess_{32.0f};

  // std::shared_ptr<Material> material_;
  std::vector<glm::vec3> vertices_;
  int index_count_;
};

} // namespace components
} // namespace mini_creator

#endif // MESH_H
