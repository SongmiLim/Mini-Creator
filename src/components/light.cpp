#include "light.h"

#include <QCoreApplication>
#include <glm/glm.hpp>

namespace mini_creator {
namespace components {

Light::Light() : ebo_(QOpenGLBuffer::IndexBuffer) {
  initializeOpenGLFunctions();

  shader_program_ = new QOpenGLShaderProgram();
  LoadShaders();
  BindBuffers();
}

Light::~Light() {
  vbo_.destroy();
  ebo_.destroy();
}

void Light::Draw(const QMatrix4x4 &view_matrix,
                 const QMatrix4x4 &projection_matrix) {
  if (!shader_program_)
    return;

  QMatrix4x4 model_matrix;
  model_matrix.setToIdentity();
  model_matrix.translate(position_);
  model_matrix.scale(0.5f);

  shader_program_->bind();
  vbo_.bind();
  ebo_.bind();

  shader_program_->setUniformValue("model", model_matrix);
  shader_program_->setUniformValue("view", view_matrix);
  shader_program_->setUniformValue("projection", projection_matrix);

  int vertex_location = shader_program_->attributeLocation("position");
  if (vertex_location != -1) {
    shader_program_->enableAttributeArray(vertex_location);
    shader_program_->setAttributeBuffer(vertex_location, GL_FLOAT, 0, 3,
                                        sizeof(float));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
  }

  ebo_.release();
  vbo_.release();
}

void Light::SetPosition(const QVector3D &position) { position_ = position; }

QVector3D Light::GetPosition() const { return position_; }

void Light::BindBuffers() {
  float vertices[] = {-0.5f, -0.5f, 0.5f,  0.5f,  -0.5f, 0.5f,
                      0.5f,  0.5f,  0.5f,  -0.5f, 0.5f,  0.5f,

                      -0.5f, -0.5f, -0.5f, 0.5f,  -0.5f, -0.5f,
                      0.5f,  0.5f,  -0.5f, -0.5f, 0.5f,  -0.5f};

  unsigned int indices[] = {
      0, 1, 2, 2, 3, 0, // Front
      4, 5, 6, 6, 7, 4, // Back
      0, 4, 7, 7, 3, 0, // Left
      1, 5, 6, 6, 2, 1, // Right
      3, 2, 6, 6, 7, 3, // Top
      0, 1, 5, 5, 4, 0  // Bottom
  };

  vbo_.create();
  vbo_.bind();
  vbo_.allocate(vertices, sizeof(vertices));

  ebo_.create();
  ebo_.bind();
  ebo_.allocate(indices, sizeof(indices));

  vbo_.release();
  ebo_.release();
}

void Light::LoadShaders() {
  shader_program_ = new QOpenGLShaderProgram();
  if (!shader_program_->addShaderFromSourceFile(
          QOpenGLShader::Vertex,
          QCoreApplication::applicationDirPath() +
              "/../../src/graphics/shader/light_cube.vs")) {
    qDebug() << "Vertex Shader Error:" << shader_program_->log();
  }

  if (!shader_program_->addShaderFromSourceFile(
          QOpenGLShader::Fragment,
          QCoreApplication::applicationDirPath() +
              "/../../src/graphics/shader/light_cube.fs")) {
    qDebug() << "Fragment Shader Error:" << shader_program_->log();
  }

  if (!shader_program_->link()) {
    qDebug() << "Shader Program Linking Error:" << shader_program_->log();
  }
  if (!shader_program_->bind()) {
    qDebug() << "Shader Program Binding Error:" << shader_program_->log();
  }
}

} // namespace components
} // namespace mini_creator
