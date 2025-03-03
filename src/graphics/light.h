#ifndef LIGHT_H
#define LIGHT_H

#include <memory>

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "graphics/shader_program.h"

namespace mini_creator {
namespace graphics {

class Light : protected QOpenGLFunctions {
public:
  Light();
  ~Light();

  void Draw(const QMatrix4x4 &view_matrix, const QMatrix4x4 &projection_matrix);

  void SetPosition(const QVector3D &position);
  QVector3D GetPosition() const;

private:
  void BindBuffers();
  void LoadShaders();

  std::shared_ptr<ShaderProgram> shader_;
  QVector3D position_ = QVector3D(5.0f, 5.0f, 5.0f);
  QOpenGLBuffer vbo_{QOpenGLBuffer::VertexBuffer};
  QOpenGLBuffer ebo_{QOpenGLBuffer::IndexBuffer};
};

} // namespace graphics
} // namespace mini_creator

#endif // LIGHT_H
