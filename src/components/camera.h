#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

#include <glm/glm.hpp>

#include "components/camera_mode.h"

namespace mini_creator {
namespace components {

class Camera {

public:
  Camera();

  void SetPerspective(float fov, float aspect_ratio, float near_plane,
                      float far_plane);
  void SetAspectRatio(int width, int height);

  QMatrix4x4 GetViewMatrix() const;
  QMatrix4x4 GetProjectionMatrix() const;
  QVector3D GetPosition() const;

  void ToggleMode();

  void FitToBoundingBox(const glm::vec3 &min_bound, const glm::vec3 &max_bound);

  void ProcessMouseMovement(float xoffset, float yoffset);
  void ProcessMouseScroll(float yoffset);
  void ProcessKeyboardInput(const QString &key);

  Mode GetMode() const;
  static enum struct Mode { FirstPerson, ThirdPerson };

private:
  void UpdateViewMatrix();
  void UpdateProjectionMatrix();

  QVector3D position_;
  QVector3D target_;
  QVector3D front_;
  QVector3D up_;

  float aspect_ratio_;
  float distance_;
  float yaw_;
  float pitch_;
  float fov_;

  float movement_speed_;
  float mouse_sensitivity_;

  float near_plane_;
  float far_plane_;

  QMatrix4x4 view_matrix_;
  QMatrix4x4 projection_matrix_;

  CameraMode mode_ = CameraMode::ThirdPerson;
};

} // namespace components
} // namespace mini_creator

#endif // CAMERA_H
