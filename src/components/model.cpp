#include "model.h"

#include <qdebug.h>

namespace mini_creator {
namespace components {

Model::Model(const QString &name)
    : name_(name), translation_(0.0f), rotation_(0.0f), scale_(1.0f) {}

Model::~Model() { meshes_.clear(); }

void Model::AddMesh(std::shared_ptr<Mesh> mesh) {
  if (mesh) {
    meshes_.push_back(mesh);
  } else {
  }
}

void Model::SetTranslation(const glm::vec3 &translation) {
  translation_ = translation;
}

void Model::SetRotation(const glm::vec3 &rotation) { rotation_ = rotation; }

void Model::SetScale(const glm::vec3 &scale) { scale_ = scale; }

void Model::Draw(QOpenGLShaderProgram *shader_program) {
  if (!shader_program) {
    qDebug() << "Shader program is null for model:" << name_;
    return;
  }

  shader_program->bind();

  QMatrix4x4 model_matrix;
  model_matrix.setToIdentity();
  model_matrix.translate(translation_.x, translation_.y, translation_.z);
  model_matrix.rotate(rotation_.x, QVector3D(1.0f, 0.0f, 0.0f));
  model_matrix.rotate(rotation_.y, QVector3D(0.0f, 1.0f, 0.0f));
  model_matrix.rotate(rotation_.z, QVector3D(0.0f, 0.0f, 1.0f));
  model_matrix.scale(scale_.x, scale_.y, scale_.z);

  shader_program->setUniformValue("model", model_matrix);

  for (const auto &mesh : meshes_) {
    if (mesh) {
      mesh->Draw(shader_program);
    }
  }

  shader_program->release();

  // qDebug() << "Model drawn:" << name_;
}

} // namespace components
} // namespace mini_creator
