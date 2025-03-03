#include "model.h"

#include <QCoreApplication>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

namespace mini_creator {
namespace graphics {

Model::Model(const QString &name) : name_(name) {
  initializeOpenGLFunctions();

  shader_program_ = std::make_shared<ShaderProgram>();
  shader_program_->Load(QCoreApplication::applicationDirPath() +
                            "/../../src/graphics/shader/mesh.vs",
                        QCoreApplication::applicationDirPath() +
                            "/../../src/graphics/shader/mesh.fs");
}

Model::~Model() { meshes_.clear(); }

void Model::AddMesh(std::shared_ptr<Mesh> mesh) {
  if (mesh) {
    meshes_.push_back(mesh);
  }
}

void Model::SetTranslation(const glm::vec3 &translation) {
  translation_ = translation;
}

void Model::SetRotation(const glm::vec3 &rotation) { rotation_ = rotation; }

void Model::SetScale(const glm::vec3 &scale) { scale_ = scale; }

const glm::vec3 &Model::GetMinBound() {
  if (meshes_.empty()) {
    return min_bound_;
  }

  min_bound_ = glm::vec3(FLT_MAX);
  for (const auto &mesh : meshes_) {
    glm::vec3 mesh_min_bound = mesh->GetMinBound();
    min_bound_ = glm::min(min_bound_, mesh_min_bound);
  }
  return min_bound_;
}

const glm::vec3 &Model::GetMaxBound() {
  if (meshes_.empty()) {
    return max_bound_;
  }

  max_bound_ = glm::vec3(-FLT_MAX);
  for (const auto &mesh : meshes_) {
    glm::vec3 mesh_max_bound = mesh->GetMaxBound();
    max_bound_ = glm::max(max_bound_, mesh_max_bound);
  }
  return max_bound_;
}

void Model::Draw(const QMatrix4x4 &view_matrix,
                 const QMatrix4x4 &projection_matrix,
                 const QVector3D &light_position,
                 const QVector3D &camera_position) {
  if (!shader_program_) {
    qDebug() << "ShaderProgram program is null for model:" << name_;
    return;
  }

  QMatrix4x4 model_matrix;
  model_matrix.setToIdentity();
  model_matrix.translate(translation_.x, translation_.y, translation_.z);
  model_matrix.rotate(rotation_.x, QVector3D(1.0f, 0.0f, 0.0f));
  model_matrix.rotate(rotation_.y, QVector3D(0.0f, 1.0f, 0.0f));
  model_matrix.rotate(rotation_.z, QVector3D(0.0f, 0.0f, 1.0f));
  model_matrix.scale(scale_.x, scale_.y, scale_.z);

  shader_program_->Use();
  shader_program_->SetUniform("model", model_matrix);
  shader_program_->SetUniform("view", view_matrix);
  shader_program_->SetUniform("projection", projection_matrix);
  shader_program_->SetUniform("lightPos", light_position);
  shader_program_->SetUniform("cameraPos", camera_position);

  for (const auto &mesh : meshes_) {
    if (mesh) {
      mesh->Draw(shader_program_);
    }
  }
}

void Model::DrawBoundingBox(const QMatrix4x4 &view_matrix,
                            const QMatrix4x4 &projection_matrix) {
  if (!bounding_box_initialized_) {
    InitializeBoundingBox();
  }
  UpdateBoundingBox();

  bounding_box_shader_->Use();
  bounding_box_shader_->SetUniform("model", QMatrix4x4());
  bounding_box_shader_->SetUniform("view", view_matrix);
  bounding_box_shader_->SetUniform("projection", projection_matrix);

  vbo_.bind();
  bounding_box_shader_->SetAttribute("position", GL_FLOAT, 0, 3,
                                     sizeof(glm::vec3));

  ebo_.bind();
  glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, nullptr);

  vbo_.release();
  ebo_.release();
}

void Model::InitializeBoundingBox() {
  bounding_box_shader_ = std::make_shared<ShaderProgram>();
  bounding_box_shader_->Load(QCoreApplication::applicationDirPath() +
                                 "/../../src/graphics/shader/bounding_box.vs",
                             QCoreApplication::applicationDirPath() +
                                 "/../../src/graphics/shader/bounding_box.fs");

  vbo_.create();
  ebo_.create();

  bounding_box_initialized_ = true;
}

void Model::UpdateBoundingBox() {
  glm::vec3 min_bound = GetMinBound();
  glm::vec3 max_bound = GetMaxBound();

  glm::vec3 left_bottom_front = {min_bound.x, min_bound.y, min_bound.z};  // 0
  glm::vec3 right_bottom_front = {max_bound.x, min_bound.y, min_bound.z}; // 1
  glm::vec3 right_top_front = {max_bound.x, max_bound.y, min_bound.z};    // 2
  glm::vec3 left_top_front = {min_bound.x, max_bound.y, min_bound.z};     // 3

  glm::vec3 left_bottom_back = {min_bound.x, min_bound.y, max_bound.z};  // 4
  glm::vec3 right_bottom_back = {max_bound.x, min_bound.y, max_bound.z}; // 5
  glm::vec3 right_top_back = {max_bound.x, max_bound.y, max_bound.z};    // 6
  glm::vec3 left_top_back = {min_bound.x, max_bound.y, max_bound.z};     // 7

  std::vector<glm::vec3> bounding_box_vertices = {
      left_bottom_front, right_bottom_front, right_top_front, left_top_front,
      left_bottom_back,  right_bottom_back,  right_top_back,  left_top_back};

  vbo_.bind();
  vbo_.allocate(bounding_box_vertices.data(),
                bounding_box_vertices.size() * sizeof(glm::vec3));
  vbo_.release();

  std::vector<uint32_t> bounding_box_indices = {
      0, 1, 1, 2, 2, 3, 3, 0, // front face
      4, 5, 5, 6, 6, 7, 7, 4, // back face
      0, 4, 1, 5, 2, 6, 3, 7  // connecting edges
  };

  ebo_.bind();
  ebo_.allocate(bounding_box_indices.data(),
                bounding_box_indices.size() * sizeof(uint32_t));
  ebo_.release();
}

} // namespace graphics
} // namespace mini_creator
