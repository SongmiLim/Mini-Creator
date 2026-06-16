#ifndef MESH_H
#define MESH_H

#include <memory>

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QString>
#include <glm/glm.hpp>

#include "graphics/shader_program.h"

namespace mini_creator {
namespace graphics {

class Mesh : protected QOpenGLFunctions {
public:
  Mesh();
  ~Mesh();

  // Owns a raw QOpenGLTexture and GL buffers; copying would double-free.
  Mesh(const Mesh &) = delete;
  Mesh &operator=(const Mesh &) = delete;

  void SetVertices(const std::vector<glm::vec3> &vertices);
  void SetNormals(const std::vector<glm::vec3> &normals);
  void SetIndices(const std::vector<uint32_t> &indices);
  void SetTexCoords(const std::vector<glm::vec2> &texCoords);
  void SetDiffuseColor(const glm::vec3 &color);
  void SetSpecularColor(const glm::vec3 &color);
  void SetAmbientColor(const glm::vec3 &color);
  void SetShininess(float shininess);

  const std::vector<glm::vec3> &GetVertices() const { return vertices_; }
  const glm::vec3 GetMinBound() const;
  const glm::vec3 GetMaxBound() const;

  void LoadTexture(const QString &file_path);
  void CreateDefaultTexture();

  void Draw(std::shared_ptr<ShaderProgram> shader);

private:
  QOpenGLBuffer vbo_vertices_{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer vbo_normals_{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer vbo_tex_coords_{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer ebo_{QOpenGLBuffer::IndexBuffer};
  QOpenGLTexture *texture_ = nullptr;

  glm::vec3 diffuse_color_{1.0f, 1.0f, 1.0f};
  glm::vec3 specular_color_{1.0f, 1.0f, 1.0f};
  glm::vec3 ambient_color_{1.0f, 1.0f, 1.0f};
  float shininess_{32.0f};

  // std::shared_ptr<Material> material_;
  std::vector<glm::vec3> vertices_;
  size_t index_count_ = 0;
};

} // namespace graphics
} // namespace mini_creator

#endif // MESH_H
