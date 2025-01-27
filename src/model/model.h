#ifndef MODEL_H
#define MODEL_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QString>
#include <glm/glm.hpp>

#include "mesh.h"
#include <memory>

namespace mini_creator {
namespace model {

class Model : protected QOpenGLFunctions {
public:
  Model(const QString &name);
  ~Model();

  void AddMesh(std::shared_ptr<Mesh> mesh);
  void SetPosition(const glm::vec3 &position);
  void SetRotation(const glm::vec3 &rotation);
  void SetScale(const glm::vec3 &scale);
  void Draw(QOpenGLShaderProgram *shader_program);
  const QString& GetName() const { return name_; }
private:
  QString name_;
  std::vector<std::shared_ptr<Mesh>> meshes_;
  glm::vec3 position_;
  glm::vec3 rotation_;
  glm::vec3 scale_;
};

} // namespace model
} // namespace mini_creator

#endif // MODEL_H
