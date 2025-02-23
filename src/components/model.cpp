#include "model.h"

#include <QCoreApplication>
#include <QDebug>

namespace mini_creator {
namespace components {

Model::Model(const QString &name)
    : name_(name), translation_(0.0f), rotation_(0.0f), scale_(1.0f) {
  shader_program_ = new QOpenGLShaderProgram();
  LoadShaders();
}

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

void Model::Draw(const QMatrix4x4 &view_matrix,
                 const QMatrix4x4 &projection_matrix,
                 const QVector3D &light_position,
                 const QVector3D &camera_position) {
  if (!shader_program_) {
    qDebug() << "Shader program is null for model:" << name_;
    return;
  }

  shader_program_->bind();

  QMatrix4x4 model_matrix;
  model_matrix.setToIdentity();
  model_matrix.translate(translation_.x, translation_.y, translation_.z);
  model_matrix.rotate(rotation_.x, QVector3D(1.0f, 0.0f, 0.0f));
  model_matrix.rotate(rotation_.y, QVector3D(0.0f, 1.0f, 0.0f));
  model_matrix.rotate(rotation_.z, QVector3D(0.0f, 0.0f, 1.0f));
  model_matrix.scale(scale_.x, scale_.y, scale_.z);

  shader_program_->setUniformValue("model", model_matrix);
  shader_program_->setUniformValue("view", view_matrix);
  shader_program_->setUniformValue("projection", projection_matrix);
  shader_program_->setUniformValue("lightPos", light_position);
  shader_program_->setUniformValue("cameraPos", camera_position);

  for (const auto &mesh : meshes_) {
    if (mesh) {
      mesh->Draw(shader_program_);
    }
  }

  shader_program_->release();
}

void Model::LoadShaders() {
  shader_program_ = new QOpenGLShaderProgram();
  if (!shader_program_->addShaderFromSourceFile(
          QOpenGLShader::Vertex, QCoreApplication::applicationDirPath() +
                                     "/../../src/graphics/shader/mesh.vs")) {
    qDebug() << QCoreApplication::applicationDirPath() +
                    "/../../src/graphics/shader/mesh.vs";
    qDebug() << "Vertex Shader Error:" << shader_program_->log();
  }

  if (!shader_program_->addShaderFromSourceFile(
          QOpenGLShader::Fragment, QCoreApplication::applicationDirPath() +
                                       "/../../src/graphics/shader/mesh.fs")) {
    qDebug() << "Fragment Shader Error:" << shader_program_->log();
  }

  if (!shader_program_->link()) {
    qDebug() << "Shader Program Linking Error:" << shader_program_->log();
  }
  if (!shader_program_->bind()) {
    qDebug() << "Shader Program Binding Error:" << shader_program_->log();
  }
}

} // namespace components
} // namespace mini_creator
