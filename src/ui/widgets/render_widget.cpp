#include "render_widget.h"

#include <QCoreApplication>
#include <QDebug>
#include <Qtimer>

#include "components/camera_mode.h"
#include "core/model_manager.h"

namespace mini_creator {
namespace ui {
namespace widgets {

RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent) {
  camera_ = std::make_shared<components::Camera>();
  light_ = std::make_shared<components::Light>();

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this,
          QOverload<>::of(&QOpenGLWidget::update));
  timer->start(16);

  setFocusPolicy(Qt::StrongFocus);
  setFocus();

  LoadUi();
}

void RenderWidget::initializeGL() { initializeOpenGLFunctions(); }

void RenderWidget::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);

  camera_->SetAspectRatio(width, height);
  camera_->SetPerspective(45.0f, float(width) / height, 0.1f, 1000.0f);

  toggle_button_->move(this->width() - toggle_button_->width() - 10, 10);
}

void RenderWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  const QMatrix4x4 &view_matrix = camera_->GetViewMatrix();
  const QMatrix4x4 &projection_matrix = camera_->GetProjectionMatrix();
  const QVector3D &light_position = light_->GetPosition();
  const QVector3D &camera_position = camera_->GetPosition();

  auto &models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {

    if (core::ModelManager::Instance().IsBoundingBoxChanged()) {
      AdjustCameraToModel();
      core::ModelManager::Instance().ResetBoundingBoxChangedFlag();
    }
    model->Draw(view_matrix, projection_matrix, light_position,
                camera_position);
  }

  light_->Draw(view_matrix, projection_matrix);
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

void RenderWidget::ToggleCameraMode() {
  camera_->ToggleMode();
  UpdateToggleButtonText();
}

void RenderWidget::LoadUi() {
  toggle_button_ = new QPushButton("Camera Mode: Third Person", this);
  toggle_button_->setFixedSize(170, 30);
  toggle_button_->move(this->width() - toggle_button_->width() - 10, 10);
  connect(toggle_button_, &QPushButton::clicked, this,
          &RenderWidget::ToggleCameraMode);
}

void RenderWidget::UpdateToggleButtonText() {
  if (camera_->GetMode() == components::CameraMode::FirstPerson) {
    toggle_button_->setText("Camera Mode: First Person");
  } else {
    toggle_button_->setText("Camera Mode: Third Person");
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

} // namespace widgets
} // namespace ui
} // namespace mini_creator