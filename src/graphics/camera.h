#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>
#include <glm/glm.hpp>

#include "graphics/camera_mode.h"

namespace mini_creator {
namespace graphics {

class Camera {

public:
  Camera();

  void SetAspectRatio(int width, int height);
  void SetPerspective(float fov, float aspect_ratio, float near_plane,
                      float far_plane);

  QMatrix4x4 GetViewMatrix() const;
  QMatrix4x4 GetProjectionMatrix() const;
  QVector3D GetPosition() const;
  CameraMode GetMode() const;

  void ToggleMode();

  void AdjustToBoundingBox(const glm::vec3 &min_bound,
                           const glm::vec3 &max_bound);

  void ProcessMouseMovement(float xoffset, float yoffset);
  void ProcessMouseScroll(float yoffset);
  void ProcessKeyboardInput(const QString &key);

  QVector3D CalculateWorldRayFromScreenPos(const QPoint &screen_pos,
                                           int screen_width,
                                           int screen_height) const;

private:
  void UpdateViewMatrix();
  void UpdateProjectionMatrix();

  QVector3D position_ = QVector3D(0.0f, 0.0f, 5.0f);
  QVector3D target_ = QVector3D(0.0f, 0.0f, 0.0f);
  QVector3D front_ = QVector3D(0.0f, 0.0f, -1.0f);
  QVector3D up_ = QVector3D(0.0f, 1.0f, 0.0f);

  float aspect_ratio_ = 1.0f;
  float distance_ = 1.0f;
  float yaw_ = -90.0f;
  float pitch_ = 0.0f;
  float fov_ = 45.0f;

  float near_plane_ = 0.1f;
  float far_plane_ = 1000.0f;

  float movement_speed_ = 0.5f;
  float mouse_sensitivity_ = 0.1f;

  QMatrix4x4 view_matrix_ = QMatrix4x4();
  QMatrix4x4 projection_matrix_ = QMatrix4x4();

  CameraMode mode_ = CameraMode::ThirdPerson;
};

} // namespace graphics
} // namespace mini_creator

#endif // CAMERA_H
