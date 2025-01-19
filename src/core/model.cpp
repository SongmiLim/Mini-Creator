#include "model.h"
#include <qdebug.h>

namespace mini_creator {
namespace core {

Model::Model(const QString &name) {
  name_ = name;
  vertex_count_ = 0;
}

Model::~Model() { vbo_.destroy(); }

void Model::Initialize(std::vector<GLfloat> vertices) {
  initializeOpenGLFunctions();

  if (!vbo_.create()) {
    qDebug() << "Failed to create VBO.";
    return;
  }
  vbo_.bind();
  vbo_.allocate(vertices.data(), vertices.size() * sizeof(GLfloat));
  vbo_.release();

  vertex_count_ = static_cast<int>(vertices.size() / 3);
}

void Model::Draw(QOpenGLShaderProgram *shader_program) {
  if (!vbo_.isCreated()) {
    qDebug() << "VBO is not created.";
    return;
  }
  vbo_.bind();

  int vertex_location = shader_program->attributeLocation("position");
  if (vertex_location == -1) {
    qDebug() << "Shader attribute 'position' not found.";
    return;
  }
  shader_program->enableAttributeArray(vertex_location);
  shader_program->setAttributeBuffer(vertex_location, GL_FLOAT, 0, 3,
                                     3 * sizeof(GLfloat));
  glDrawArrays(GL_TRIANGLES, 0, vertex_count_);

  vbo_.release();
}

} // namespace core
} // namespace mini_creator
