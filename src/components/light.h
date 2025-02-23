#ifndef LIGHT_H
#define LIGHT_H

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

namespace mini_creator {
namespace components {

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

  QOpenGLShaderProgram *shader_program_;
  QVector3D position_ = QVector3D(5.0f, 5.0f, 5.0f);
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
};

} // namespace components
} // namespace mini_creator

#endif // LIGHT_H
