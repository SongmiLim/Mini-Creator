#ifndef MODEL_H
#define MODEL_H

#include <QOpenGLBuffer>
#include <QString>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <memory>

namespace mini_creator {
namespace core {

class Model: protected QOpenGLFunctions {
public:
  Model(const QString &name);
  ~Model();

  void Initialize(const std::vector<GLfloat> vertices);
  void Draw(QOpenGLShaderProgram *program);

  int GetVertexCount() const { return vertex_count_; }
  QString GetName() const { return name_; }

private:
  QString name_;
  QOpenGLBuffer vbo_;
  int vertex_count_;
};

} // namespace core
} // namespace mini_creator

#endif // MODEL_H
