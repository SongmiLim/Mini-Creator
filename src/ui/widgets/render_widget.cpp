#include "render_widget.h"
#include "../../core/model_manager.h"

#include <QDebug>
#include <Qtimer>

namespace mini_creator {
namespace ui {
namespace widgets {

RenderWidget::RenderWidget(QWidget *parent)
    : QOpenGLWidget(parent), shader_program_(nullptr) {
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this,
          QOverload<>::of(&QOpenGLWidget::update));
  timer->start(16);
}

void RenderWidget::initializeGL() {
  initializeOpenGLFunctions();
  SetupShaders();

  view_matrix_.setToIdentity();
  view_matrix_.lookAt(QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 0.0f),
                      QVector3D(0.0f, 1.0f, 0.0f));
}

void RenderWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);

  projection_matrix_.setToIdentity();
  projection_matrix_.perspective(45.0f, GLfloat(width) / height, 0.1f, 100.0f);
}

void RenderWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  shader_program_->bind();

  model_matrix_.setToIdentity();
  model_matrix_.rotate(45.0f, QVector3D(1.0f, 1.0f, 0.0f));

  shader_program_->setUniformValue("mvp", projection_matrix_ * view_matrix_ *
                                              model_matrix_);

  auto &models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    model->Draw(shader_program_);
  }
}

void RenderWidget::SetupShaders() {
  shader_program_ = new QOpenGLShaderProgram();
  if (!shader_program_->addShaderFromSourceFile(
          QOpenGLShader::Vertex,
          "C:\\Users\\lsmi1\\MiniCreator\\src\\shader\\mesh.vs")) {
    qDebug() << "Vertex Shader Error:" << shader_program_->log();
  }

  if (!shader_program_->addShaderFromSourceFile(
          QOpenGLShader::Fragment,
          "C:\\Users\\lsmi1\\MiniCreator\\src\\shader\\mesh.fs")) {
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