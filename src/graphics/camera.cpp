#include "camera.h"

namespace mini_creator {
namespace graphics {

Camera::Camera() {
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

CameraMode Camera::GetMode() const { return mode_; }

void Camera::ToggleMode() {
  mode_ = (mode_ == CameraMode::FirstPerson) ? CameraMode::ThirdPerson
                                             : CameraMode::FirstPerson;

  UpdateViewMatrix();
  UpdateProjectionMatrix();
}

void Camera::AdjustToBoundingBox(const glm::vec3 &min_bound,
                                 const glm::vec3 &max_bound) {
  glm::vec3 bounding_box_size = max_bound - min_bound;
  float bounding_box_radius = glm::length(bounding_box_size) * 0.5f;
  distance_ = bounding_box_radius / std::tan(glm::radians(fov_) / 2.0f);

  glm::vec3 center = (min_bound + max_bound) * 0.5f;
  target_ = QVector3D(center.x, center.y, center.z);
  position_ = target_ - front_ * distance_;

  UpdateViewMatrix();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
  yaw_ += xoffset * mouse_sensitivity_;
  pitch_ -= yoffset * mouse_sensitivity_;

  if (pitch_ > 89.0f)
    pitch_ = 89.0f;
  if (pitch_ < -89.0f)
    pitch_ = -89.0f;

  QVector3D front;
  front.setX(cos(qDegreesToRadians(yaw_)) * cos(qDegreesToRadians(pitch_)));
  front.setY(sin(qDegreesToRadians(pitch_)));
  front.setZ(sin(qDegreesToRadians(yaw_)) * cos(qDegreesToRadians(pitch_)));
  front_ = front.normalized();

  if (mode_ == CameraMode::ThirdPerson) {
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
  if (mode_ == CameraMode::ThirdPerson) {
    // Third-person mode: Move `target_` and keep `position_` following it
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
        target_ - front_ * distance_; // Keep the camera behind the character
  } else {
    // First-person mode: Move directly in the `front_` direction
    if (key == "W")
      position_ += front_ * movement_speed_;
    if (key == "S")
      position_ -= front_ * movement_speed_;
    if (key == "A")
      position_ -=
          QVector3D::crossProduct(front_, up_).normalized() * movement_speed_;
    if (key == "D")
      position_ +=
          QVector3D::crossProduct(front_, up_).normalized() * movement_speed_;
  }
  UpdateViewMatrix();
}

QVector3D Camera::CalculateWorldRayFromScreenPos(const QPoint &screen_pos,
                                                 int screen_width,
                                                 int screen_height) const {
  float x = (2.0f * screen_pos.x()) / screen_width - 1.0f;
  float y = 1.0f - (2.0f * screen_pos.y()) / screen_height;
  float z = 1.0f;

  QVector3D ray_nds(x, y, z);
  QVector4D ray_clip(ray_nds.x(), ray_nds.y(), -1.0, 1.0);
  QVector4D ray_eye = projection_matrix_.inverted() * ray_clip;
  ray_eye = QVector4D(ray_eye.x(), ray_eye.y(), -1.0, 0.0);

  QVector3D ray_world = (view_matrix_.inverted() * ray_eye).toVector3D();
  ray_world.normalize();

  return ray_world;
}

void Camera::UpdateViewMatrix() {
  view_matrix_.setToIdentity();

  if (mode_ == CameraMode::ThirdPerson) {
    view_matrix_.lookAt(position_, target_, up_);
  } else {
    view_matrix_.lookAt(position_, position_ + front_, up_);
  }
}

void Camera::UpdateProjectionMatrix() {
  projection_matrix_.setToIdentity();
  projection_matrix_.perspective(fov_, aspect_ratio_, near_plane_, far_plane_);
}

} // namespace graphics
} // namespace mini_creator
