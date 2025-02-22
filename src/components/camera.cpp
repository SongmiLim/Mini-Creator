#include "camera.h"

namespace mini_creator {
namespace components {

Camera::Camera() {
  position_ = QVector3D(0.0f, 0.0f, 5.0f);
  target_ = QVector3D(0.0f, 0.0f, 0.0f);
  front_ = QVector3D(0.0f, 0.0f, -1.0f);
  up_ = QVector3D(0.0f, 1.0f, 0.0f);

  yaw_ = -90.0f;
  pitch_ = 0.0f, fov_ = 45.0f;

  aspect_ratio_ = 1.0f;

  near_plane_ = 0.1f;
  far_plane_ = 1000.0f;

  movement_speed_ = 0.5f;
  mouse_sensitivity_ = 0.1f;

  UpdateViewMatrix();
  UpdateProjectionMatrix();
}

void Camera::SetAspectRatio(int width, int height) {
  if (height != 0) {
    aspect_ratio_ = static_cast<float>(width) / static_cast<float>(height);
    UpdateProjectionMatrix();
  } else {
    qDebug() << "Height cannot be zero!";
  }
}

void Camera::SetPerspective(float fov, float aspect_ratio, float near_plane,
                            float far_plane) {
  fov_ = fov;
  aspect_ratio_ = aspect_ratio;
  near_plane_ = near_plane;
  far_plane_ = far_plane;

  UpdateProjectionMatrix();
}

QMatrix4x4 Camera::GetViewMatrix() const { return view_matrix_; }

QMatrix4x4 Camera::GetProjectionMatrix() const { return projection_matrix_; }

QVector3D Camera::GetPosition() const { return position_; }
Mode Camera::GetMode() const { return mode_; }

void Camera::ToggleMode() {
  mode_ = (mode_ == Mode::FirstPerson) ? Mode::ThirdPerson : Mode::FirstPerson;

  UpdateViewMatrix();
  UpdateProjectionMatrix();
}

void Camera::FitToBoundingBox(const glm::vec3 &min_bound,
                              const glm::vec3 &max_bound) {
  glm::vec3 center = (min_bound + max_bound) * 0.5f;
  glm::vec3 size = max_bound - min_bound;
  float radius = glm::length(size) * 0.5f;
  distance_ = radius / std::tan(glm::radians(fov_) / 2.0f);

  if (mode_ == Mode::ThirdPerson) {
    target_ = QVector3D(center.x, center.y, center.z);
    position_ = target_ - front_ * distance_;
  } else {
    position_ = QVector3D(center.x, center.y, center.z);
    target_ = position_ + front_;
  }

  UpdateViewMatrix();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
  yaw_ -= xoffset * mouse_sensitivity_;
  pitch_ += yoffset * mouse_sensitivity_;

  if (pitch_ > 89.0f)
    pitch_ = 89.0f;
  if (pitch_ < -89.0f)
    pitch_ = -89.0f;

  QVector3D front;
  front.setX(cos(qDegreesToRadians(yaw_)) * cos(qDegreesToRadians(pitch_)));
  front.setY(sin(qDegreesToRadians(pitch_)));
  front.setZ(sin(qDegreesToRadians(yaw_)) * cos(qDegreesToRadians(pitch_)));
  front_ = front.normalized();

  if (mode_ == Mode::ThirdPerson) {
    position_ = target_ - front_ * distance_;
  }

  UpdateViewMatrix();
}

void Camera::ProcessMouseScroll(float yoffset) {
  fov_ -= yoffset;
  if (fov_ < 20.0f)
    fov_ = 20.0f;
  if (fov_ > 80.0f)
    fov_ = 80.0f;
  UpdateProjectionMatrix();
}

void Camera::ProcessKeyboardInput(const QString &key) {
  if (mode_ == Mode::ThirdPerson) {
    // 🔹 3인칭: `target_`을 이동시키고 `position_`을 따라가도록 함
    if (key == "W")
      target_ += front_ * movement_speed_;
    if (key == "S")
      target_ -= front_ * movement_speed_;
    if (key == "A")
      target_ -=
          QVector3D::crossProduct(front_, up_).normalized() * movement_speed_;
    if (key == "D")
      target_ +=
          QVector3D::crossProduct(front_, up_).normalized() * movement_speed_;

    position_ =
        target_ - front_ * distance_; // 🔹 카메라가 항상 캐릭터 뒤쪽에서 유지됨
  } else {
    // 🔹 1인칭: `front_` 방향으로 직접 이동
    if (key == "W")
      position_ += front_ * movement_speed_;
    if (key == "S")
      position_ -= front_ * movement_speed_;
    if (key == "A")
      position_ +=
          QVector3D::crossProduct(front_, up_).normalized() * movement_speed_;
    if (key == "D")
      position_ -=
          QVector3D::crossProduct(front_, up_).normalized() * movement_speed_;
  }
  UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
  view_matrix_.setToIdentity();

  if (mode_ == Mode::ThirdPerson) {
    view_matrix_.lookAt(position_, target_, up_);
  } else {
    view_matrix_.lookAt(position_, position_ + front_, up_);
  }
}

void Camera::UpdateProjectionMatrix() {
  projection_matrix_.setToIdentity();
  projection_matrix_.perspective(fov_, aspect_ratio_, near_plane_, far_plane_);
}

} // namespace components
} // namespace mini_creator
