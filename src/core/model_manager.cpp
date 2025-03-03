#include "model_manager.h"

namespace mini_creator {
namespace core {

bool ModelManager::is_bounding_box_changed_ = false;
std::vector<std::shared_ptr<graphics::Model>> ModelManager::models_;
std::shared_ptr<graphics::Model> ModelManager::selected_model_ = nullptr;

void ModelManager::AddModel(std::shared_ptr<graphics::Model> model) {
  models_.push_back(model);
  is_bounding_box_changed_ = true;
}

void ModelManager::SetSelectedModel(std::shared_ptr<graphics::Model> model) {
  selected_model_ = model;
}

std::shared_ptr<graphics::Model> ModelManager::GetModel(const QString &name) {
  for (const auto &model : models_) {
    if (model->GetName() == name) {
      return model;
    }
  }
  return nullptr;
}

std::shared_ptr<graphics::Model> ModelManager::GetSelectedModel() {
  return selected_model_;
}

std::vector<std::shared_ptr<graphics::Model>> &ModelManager::GetAllModels() {
  return models_;
}

bool ModelManager::IsBoundingBoxChanged() { return is_bounding_box_changed_; }

void ModelManager::ResetBoundingBoxChangedFlag() {
  is_bounding_box_changed_ = false;
}

} // namespace core
} // namespace mini_creator
