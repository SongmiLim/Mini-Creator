#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLShaderProgram>
#include <QString>
#include <QVector3D>
#include <glm/glm.hpp>

namespace mini_creator {
namespace components {

class Shader {
public:
  Shader();
  ~Shader();

  bool Load(const QString &vertexPath, const QString &fragmentPath);
  void Use();

  void SetUniform(const QString &name, float value);
  void SetUniform(const QString &name, int value);
  void SetUniform(const QString &name, const QVector3D &value);
  void SetUniform(const QString &name, const glm::vec3 &value);
  void SetUniform(const QString &name, const QMatrix4x4 &matrix);

  void SetAttribute(const QString &name, GLenum type, int offset, int size,
                    int stride);

  QOpenGLShaderProgram *GetProgram() { return shader_program_; }

private:
  QOpenGLShaderProgram *shader_program_;
};

} // namespace components
} // namespace mini_creator

#endif // SHADER_H
