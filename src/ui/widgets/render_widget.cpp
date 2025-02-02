#include "render_widget.h"

#include "../../core/model_manager.h"

#include <QCoreApplication>
#include <QDebug>
#include <Qtimer>

namespace mini_creator {
namespace ui {
namespace widgets {

RenderWidget::RenderWidget(QWidget *parent)
    : QOpenGLWidget(parent), shader_program_(nullptr) {
  camera_ = std::make_shared<components::Camera>();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this,
          QOverload<>::of(&QOpenGLWidget::update));
  timer->start(16);
}

void RenderWidget::initializeGL() {
  initializeOpenGLFunctions();
  SetupShaders();

  shader_program_->setUniformValue("view", camera_->GetViewMatrix());
}

void RenderWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);

  camera_->SetAspectRatio(width, height);
  camera_->SetPerspective(45.0f, float(width) / height, 0.1f, 1000.0f);
  shader_program_->setUniformValue("projection",
                                   camera_->GetProjectionMatrix());
}

void RenderWidget::AdjustCameraToModel() {
  auto &models = core::ModelManager::Instance().GetAllModels();
  if (models.empty()) {
    return;
  }

  glm::vec3 minBound(FLT_MAX), maxBound(-FLT_MAX);

  for (const auto &model : models) {
    for (const auto &mesh : model->GetMeshes()) {
      for (const auto &vertex : mesh->GetVertices()) {
        minBound = glm::min(minBound, vertex);
        maxBound = glm::max(maxBound, vertex);
      }
    }
  }

  camera_->FitToBoundingBox(minBound, maxBound);
  shader_program_->setUniformValue("view", camera_->GetViewMatrix());
}

void RenderWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  shader_program_->bind();

  shader_program_->setUniformValue("lightPos", 10.0f, 10.0f, 10.0f);
  shader_program_->setUniformValue("viewPos", camera_->GetPosition().x(),
                                   camera_->GetPosition().y(),
                                   camera_->GetPosition().z());

  auto &models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {

    if (core::ModelManager::Instance().IsBoundingBoxChanged()) {
      AdjustCameraToModel();
      core::ModelManager::Instance().ResetBoundingBoxChangedFlag();
    }
    model->Draw(shader_program_);
  }
}

void RenderWidget::SetupShaders() {
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

} // namespace widgets
} // namespace ui
} // namespace mini_creator