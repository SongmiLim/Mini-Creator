#include "light.h"

#include <glm/glm.hpp>

namespace mini_creator {
namespace components {

Light::Light() : ebo_(QOpenGLBuffer::IndexBuffer){
  position_ = QVector3D(5.0f, 5.0f, 1.0f);

  initializeOpenGLFunctions();
  Initialize();
}

Light::~Light() {
  vbo_.destroy();
  ebo_.destroy();
}

void Light::Initialize() {
    float vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,  
         0.5f, -0.5f,  0.5f,  
         0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        // Back face
        -0.5f, -0.5f, -0.5f,  
         0.5f, -0.5f, -0.5f,  
         0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f   
    };     

  unsigned int indices[] = {
    0, 1, 2, 2, 3, 0,  // Front
    4, 5, 6, 6, 7, 4,  // Back
    0, 4, 7, 7, 3, 0,  // Left
    1, 5, 6, 6, 2, 1,  // Right
    3, 2, 6, 6, 7, 3,  // Top
    0, 1, 5, 5, 4, 0   // Bottom
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

void Light::Draw(QOpenGLShaderProgram *shader_program) {
  if (!shader_program)
    return;

  QMatrix4x4 model;
  model.setToIdentity();
  model.translate(position_);
  model.scale(0.5f);

  shader_program->bind();
  shader_program->setUniformValue("model", model);

  vbo_.bind();
  ebo_.bind();

  int vertex_location = shader_program->attributeLocation("position");
  if (vertex_location != -1) {
    shader_program->enableAttributeArray(vertex_location);
    shader_program->setAttributeBuffer(vertex_location, GL_FLOAT, 0, 3, sizeof(float));
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
  }

  ebo_.release();
  vbo_.release();
}

void Light::SetPosition(const QVector3D &position) { position_ = position; }

QVector3D Light::GetPosition() const { return position_; }

} // namespace components
} // namespace mini_creator
