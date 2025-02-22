#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <memory>
#include <vector>

#include "components/model.h"

namespace mini_creator {
namespace core {

class ModelManager {
public:
  static ModelManager &Instance();

  void AddModel(std::shared_ptr<components::Model> model);
  std::shared_ptr<components::Model> GetModel(const QString &name) const;
  const std::vector<std::shared_ptr<components::Model>> &GetAllModels() const;
  bool IsBoundingBoxChanged() const { return is_bounding_box_changed; }
  void ResetBoundingBoxChangedFlag() { is_bounding_box_changed = false; }

private:
  ModelManager() = default;
  ~ModelManager() = default;
  bool is_bounding_box_changed = false;
  std::vector<std::shared_ptr<components::Model>> models_;
};

} // namespace core
} // namespace mini_creator

#endif // MODEL_MANAGER_H
