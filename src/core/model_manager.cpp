#include "model_manager.h"

namespace mini_creator {
namespace core {

ModelManager &ModelManager::Instance() {
  static ModelManager instance;
  return instance;
}

void ModelManager::AddModel(std::shared_ptr<Model> model) {
  models_.push_back(model);
}

std::shared_ptr<Model> ModelManager::GetModel(const QString &name) const {
  for (const auto &model : models_) {
    if (model->GetName() == name) {
      return model;
    }
  }
  return nullptr;
}

const std::vector<std::shared_ptr<Model>> &ModelManager::GetAllModels() const {
  return models_;
}

} // namespace core
} // namespace mini_creator
