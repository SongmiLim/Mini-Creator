#include "render_widget.h"

#include "../../core/model_manager.h"
#include "../../components/camera_mode.h"

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

  setFocusPolicy(Qt::StrongFocus);
  setFocus();

  SetupUI();
}

void RenderWidget::SetupUI() {
  toggle_button_ = new QPushButton("모드 변경 (1인칭)", this);
  toggle_button_->setFixedSize(120, 30);   // 🔹 버튼 크기 설정
  toggle_button_->move(width() - 140, 10); // 🔹 오른쪽 상단에 배치

  connect(toggle_button_, &QPushButton::clicked, this,
          &RenderWidget::ToggleCameraMode);
}

void RenderWidget::initializeGL() {
  initializeOpenGLFunctions();
  SetupShaders();
}

void RenderWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);

  camera_->SetAspectRatio(width, height);
  camera_->SetPerspective(45.0f, float(width) / height, 0.1f, 1000.0f);

  toggle_button_->move(width() - 140, 10);
}

void RenderWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  shader_program_->bind();

  shader_program_->setUniformValue("view", camera_->GetViewMatrix());
  shader_program_->setUniformValue("projection",
                                   camera_->GetProjectionMatrix());
  shader_program_->setUniformValue("lightPos", 10.0f, 10.0f, 10.0f);
  shader_program_->setUniformValue("cameraPos", camera_->GetPosition().x(),
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

void RenderWidget::mouseMoveEvent(QMouseEvent *event) {
  if (is_mouse_pressed_) {

    QPoint current_pos = event->pos();
    float xoffset = current_pos.x() - last_mouse_pos_.x();
    float yoffset = current_pos.y() - last_mouse_pos_.y();

    camera_->ProcessMouseMovement(xoffset, yoffset);

    last_mouse_pos_ = event->pos();
  }
}

void RenderWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    last_mouse_pos_ = event->pos();
    is_mouse_pressed_ = true;
  }
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    is_mouse_pressed_ = false;
  }
}

void RenderWidget::wheelEvent(QWheelEvent *event) {
  float zoomOffset = event->angleDelta().y() / 120.0f;
  camera_->ProcessMouseScroll(zoomOffset);
}

void RenderWidget::keyPressEvent(QKeyEvent *event) {

  QString key = event->text().toUpper();
  if (key == "F") {
    ToggleCameraMode();
  } else if (key == "W" || key == "A" || key == "S" || key == "D") {
    camera_->ProcessKeyboardInput(key);
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
}

void RenderWidget::ToggleCameraMode() {
  camera_->ToggleMode();
  UpdateToggleButtonText();
  update();
}

void RenderWidget::UpdateToggleButtonText() {
  if (camera_->GetMode() == components::CameraMode::FirstPerson) {
    toggle_button_->setText("Camera Mode: First Person ");
  } else {
    toggle_button_->setText("Camera Mode: Third Person");
  }
}

} // namespace widgets
} // namespace ui
} // namespace mini_creator