#include "camera.h"

namespace mini_creator {
namespace components {

Camera::Camera() {
  position_ = QVector3D(0.0f, 0.0f, 5.0f);
  target_ = QVector3D(0.0f, 0.0f, 0.0f);
  up_ = QVector3D(0.0f, 1.0f, 0.0f);

  fov_ = 45.0f;
  aspect_ratio_ = 1.0f;
  near_plane_ = 0.1f;
  far_plane_ = 1000.0f;

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

void Camera::FitToBoundingBox(const glm::vec3 &min_bound,
                              const glm::vec3 &max_bound) {
  glm::vec3 center = (min_bound + max_bound) * 0.5f;
  glm::vec3 size = max_bound - min_bound;
  float radius = glm::length(size) * 0.5f;

  float distance = radius / std::tan(glm::radians(fov_) / 2.0f);
  position_ = QVector3D(center.x, center.y, center.z + distance * 2);
  target_ = QVector3D(center.x, center.y, center.z);

  UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
  view_matrix_.setToIdentity();
  view_matrix_.lookAt(position_, target_, up_);
}

void Camera::UpdateProjectionMatrix() {
  projection_matrix_.setToIdentity();
  projection_matrix_.perspective(fov_, aspect_ratio_, near_plane_, far_plane_);
}

} // namespace components
} // namespace mini_creator
