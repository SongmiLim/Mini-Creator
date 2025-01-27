#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

#include <glm/glm.hpp>

namespace mini_creator {
namespace components {

class Camera {
public:
  Camera();

  void SetPerspective(float fov, float aspect_ratio, float near_plane,
                      float far_plane);
  QMatrix4x4 GetViewMatrix() const;
  QMatrix4x4 GetProjectionMatrix() const;

  void FitToBoundingBox(const glm::vec3& min_bound, const glm::vec3& max_bound);

private:
    QVector3D position_;
    QVector3D target_;
    QVector3D up_;

  float fov_;
  float aspect_ratio_;
  float near_plane_;
  float far_plane_;

  QMatrix4x4 view_matrix_;
  QMatrix4x4 projection_matrix_;

  void UpdateViewMatrix();
  void UpdateProjectionMatrix();
};

} // namespace components
} // namespace mini_creator

#endif // CAMERA_H
