#include "model.h"

#include <qdebug.h>

namespace mini_creator {
namespace model {

Model::Model(const QString &name)
    : name_(name), position_(0.0f), rotation_(0.0f), scale_(1.0f) {}

Model::~Model() { meshes_.clear(); }

void Model::AddMesh(std::shared_ptr<Mesh> mesh) {
  if (mesh) {
    meshes_.push_back(mesh);
    // qDebug() << "Mesh added to model:" << name_;
  } else {
    // qDebug() << "Attempted to add null mesh to model:" << name_;
  }
}

void Model::SetPosition(const glm::vec3 &position) {
  position_ = position;
  // qDebug() << "Model position set to:" << position_.x << position_.y
           //<< position_.z;
}

void Model::SetRotation(const glm::vec3 &rotation) {
  rotation_ = glm::vec3(-0.5f, 0.5f, 1.0f);
  // qDebug() << "Model rotation set to:" << rotation_.x << rotation_.y
           //<< rotation_.z;
}

void Model::SetScale(const glm::vec3 &scale) {
  scale_ = scale;
  // qDebug() << "Model scale set to:" << scale_.x << scale_.y << scale_.z;
}

void Model::Draw(QOpenGLShaderProgram *shader_program) {
  if (!shader_program) {
    qDebug() << "Shader program is null for model:" << name_;
    return;
  }

  shader_program->bind();

  QMatrix4x4 modelMatrix;
  modelMatrix.setToIdentity();
  modelMatrix.translate(position_.x, position_.y, position_.z);
  modelMatrix.rotate(45.0f, QVector3D(-1.0f, 1.0f, 0.0f));
  modelMatrix.scale(2.0f, 2.0f, 2.0f);

  shader_program->setUniformValue("model", modelMatrix);

  for (const auto &mesh : meshes_) {
    if (mesh) {
      mesh->Draw(shader_program);
    }
  }

  shader_program->release();

  // qDebug() << "Model drawn:" << name_;
}

} // namespace model
} // namespace mini_creator
