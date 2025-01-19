#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include "model.h"
#include <vector>
#include <memory>

namespace mini_creator {
namespace core {

class ModelManager {
public:
    static ModelManager& Instance();

    void AddModel(std::shared_ptr<Model> model);
    std::shared_ptr<Model> GetModel(const QString& name) const;
    const std::vector<std::shared_ptr<Model>>& GetAllModels() const;

private:
    ModelManager() = default;
    ~ModelManager() = default;
    
    std::vector<std::shared_ptr<Model>> models_;
};

} // namespace core
} // namespace mini_creator

#endif // MODEL_MANAGER_H
