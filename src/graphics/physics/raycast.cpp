#include "raycast.h"

#include <glm/glm.hpp>
#include <limits>

#include "core/model_manager.h"
#include "graphics/mesh.h"

namespace mini_creator {
namespace graphics {
namespace physics {

std::shared_ptr<graphics::Model>
Raycast::Execute(const QVector3D &camera_position,
                 const QVector3D &camera_direction) {
  std::shared_ptr<graphics::Model> closest_model = nullptr;
  float closest_distance = std::numeric_limits<float>::max();

  auto &models = core::ModelManager::GetAllModels();
  for (const auto &model : models) {
    glm::vec3 min_bound = model->GetMinBound();
    glm::vec3 max_bound = model->GetMaxBound();

    const QMatrix4x4 model_matrix = model->GetModelMatrix();

    QVector3D ray_origin = model_matrix.inverted() * camera_position;
    QVector3D ray_direction =
    (model_matrix.inverted() * QVector4D(camera_direction, 0.0)).toVector3D();

    float tmin, tmax;
    if (RayIntersectsBox(
            glm::vec3(ray_origin.x(), ray_origin.y(), ray_origin.z()),
            glm::vec3(ray_direction.x(), ray_direction.y(), ray_direction.z()),
            min_bound, max_bound, tmin, tmax)) {
      if (tmin < closest_distance) {
        closest_distance = tmin;
        closest_model = model;
      }
    }
  }

  return closest_model;
}

bool Raycast::RayIntersectsBox(const glm::vec3 &ray_origin,
                               const glm::vec3 &ray_direction,
                               const glm::vec3 &box_min,
                               const glm::vec3 &box_max, float &tmin,
                               float &tmax) {
  tmin = (box_min.x - ray_origin.x) / ray_direction.x;
  tmax = (box_max.x - ray_origin.x) / ray_direction.x;

  if (tmin > tmax)
    std::swap(tmin, tmax);

  float tymin = (box_min.y - ray_origin.y) / ray_direction.y;
  float tymax = (box_max.y - ray_origin.y) / ray_direction.y;

  if (tymin > tymax)
    std::swap(tymin, tymax);

  if ((tmin > tymax) || (tymin > tmax))
    return false;

  if (tymin > tmin)
    tmin = tymin;

  if (tymax < tmax)
    tmax = tymax;

  float tzmin = (box_min.z - ray_origin.z) / ray_direction.z;
  float tzmax = (box_max.z - ray_origin.z) / ray_direction.z;

  if (tzmin > tzmax)
    std::swap(tzmin, tzmax);

  if ((tmin > tzmax) || (tzmin > tmax))
    return false;

  if (tzmin > tmin)
    tmin = tzmin;

  if (tzmax < tmax)
    tmax = tzmax;

  return true;
}

} // namespace physics
} // namespace graphics
} // namespace mini_creator
