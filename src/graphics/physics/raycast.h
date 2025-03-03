#ifndef RAYCAST_H
#define RAYCAST_H

#include <QVector3D>
#include <memory>

#include "graphics/model.h"

namespace mini_creator {
namespace graphics {
namespace physics {

class Raycast {
public:
  static std::shared_ptr<graphics::Model> Execute(const QVector3D &origin,
                                                  const QVector3D &direction);

private:
  static bool RayIntersectsBox(const glm::vec3 &ray_origin,
                               const glm::vec3 &ray_direction,
                               const glm::vec3 &box_min,
                               const glm::vec3 &box_max, float &tmin,
                               float &tmax);
};

} // namespace physics
} // namespace graphics
} // namespace mini_creator

#endif // RAYCAST_H
