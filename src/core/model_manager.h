#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <memory>
#include <vector>

#include "graphics/model.h"

namespace mini_creator {
namespace core {

class ModelManager {
public:
  static void AddModel(std::shared_ptr<graphics::Model> model);

  static void SetSelectedModel(std::shared_ptr<graphics::Model> model);

  static std::shared_ptr<graphics::Model> GetModel(const QString &name);
  static std::shared_ptr<graphics::Model> GetSelectedModel();
  static std::vector<std::shared_ptr<graphics::Model>> &GetAllModels();

  static bool IsBoundingBoxChanged();
  static void ResetBoundingBoxChangedFlag();

private:
  static bool is_bounding_box_changed_;
  static std::vector<std::shared_ptr<graphics::Model>> models_;
  static std::shared_ptr<graphics::Model> selected_model_;
};

} // namespace core
} // namespace mini_creator

#endif // MODEL_MANAGER_H
