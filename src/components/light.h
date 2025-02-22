#ifndef LIGHT_H
#define LIGHT_H

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

namespace mini_creator {
namespace components {

class Light : protected QOpenGLFunctions {
public:
  Light();
  ~Light();

  void Draw(QOpenGLShaderProgram *shader_program);
  void SetPosition(const QVector3D &position);
  QVector3D GetPosition() const;

private:
  void Initialize();

  QVector3D position_;
  QOpenGLBuffer vbo_;
  QOpenGLBuffer ebo_;
};

} // namespace components
} // namespace mini_creator

#endif // LIGHT_H
