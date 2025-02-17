#include "mesh.h"

#include <QFileInfo>
#include <qdebug.h>

namespace mini_creator {
namespace components {

Mesh::Mesh() : ebo_(QOpenGLBuffer::IndexBuffer) {
  QOpenGLFunctions::initializeOpenGLFunctions();
  index_count_ = 0;
}

Mesh::~Mesh() {
  vbo_vertices_.destroy();
  vbo_normals_.destroy();
  vbo_texCoords_.destroy();
  ebo_.destroy();
}

void Mesh::SetVertices(const std::vector<glm::vec3> &vertices) {
  vertices_ = vertices;
  if (vertices.empty()) {
    qDebug() << "Mesh::SetVertices - Empty vertex data.";
    return;
  }

  vbo_vertices_.create();
  vbo_vertices_.bind();
  vbo_vertices_.allocate(vertices.data(), vertices.size() * sizeof(glm::vec3));
  vbo_vertices_.release();
}

void Mesh::SetNormals(const std::vector<glm::vec3> &normals) {
  if (normals.empty()) {
    return;
  }
  vbo_normals_.create();
  vbo_normals_.bind();
  vbo_normals_.allocate(normals.data(), normals.size() * sizeof(glm::vec3));
  vbo_normals_.release();
}

void Mesh::SetIndices(const std::vector<uint32_t> &indices) {
  if (indices.empty()) {
    return;
  }
  ebo_.create();
  ebo_.bind();
  ebo_.allocate(indices.data(), indices.size() * sizeof(uint32_t));
  ebo_.release();

  index_count_ = static_cast<int>(indices.size());
}

void Mesh::SetTexCoords(const std::vector<glm::vec2> &texCoords) {
  if (texCoords.empty()) {
    return;
  }
  vbo_texCoords_.create();
  vbo_texCoords_.bind();
  vbo_texCoords_.allocate(texCoords.data(),
                          texCoords.size() * sizeof(glm::vec2));
  vbo_texCoords_.release();
}

void Mesh::CreateDefaultTexture() {
  if (texture_) {
    delete texture_;
    texture_ = nullptr;
  }

  QImage default_image(1, 1, QImage::Format_RGB888);
  default_image.fill(QColor(160, 160, 160));

  texture_ = new QOpenGLTexture(default_image);

  if (!texture_->isCreated()) {
    qDebug() << "Error: Failed to create default texture!";
    delete texture_;
    texture_ = nullptr;
    return;
  }

  texture_->setWrapMode(QOpenGLTexture::Repeat);
  texture_->setMinificationFilter(QOpenGLTexture::Linear);
  texture_->setMagnificationFilter(QOpenGLTexture::Linear);

  texture_->release();
}

void Mesh::LoadTexture(const QString &file_path) {
  if (texture_) {
    delete texture_;
    texture_ = nullptr;
  }

  QFileInfo file_info(file_path);
  if (!file_info.exists()) {
    qDebug() << "Error: Texture file does not exist ->" << file_path;
    CreateDefaultTexture();
    return;
  }

  QImage image(file_path);
  if (image.isNull()) {
    qDebug() << "Error: Failed to load image ->" << file_path;
    CreateDefaultTexture();
    return;
  }

  texture_ = new QOpenGLTexture(image.mirrored());
  if (!texture_->isCreated()) {
    qDebug() << "Failed to create OpenGL texture for ->" << file_path;
    delete texture_;
    texture_ = nullptr;
  }
  texture_->release();
}

void Mesh::SetDiffuseColor(const glm::vec3 &color) { diffuse_color_ = color; }
void Mesh::SetSpecularColor(const glm::vec3 &color) { specular_color_ = color; }
void Mesh::SetAmbientColor(const glm::vec3 &color) { ambient_color_ = color; }
void Mesh::SetShininess(float shininess) { shininess_ = shininess; }

void Mesh::Draw(QOpenGLShaderProgram *shader_program) {
  if (!shader_program) {
    qDebug() << "Mesh::Draw - Shader program is null.";
    return;
  }

  shader_program->setUniformValue("material.diffuse", diffuse_color_.r,
                                  diffuse_color_.g, diffuse_color_.b);
  shader_program->setUniformValue("material.specular", specular_color_.r,
                                  specular_color_.g, specular_color_.b);
  shader_program->setUniformValue("material.ambient", ambient_color_.r,
                                  ambient_color_.g, ambient_color_.b);
  shader_program->setUniformValue("material.shininess", shininess_);

  if (texture_) {
    glActiveTexture(GL_TEXTURE0);
    texture_->bind();
    shader_program->setUniformValue("textureMap", 0);
  } else {
    qDebug() << "Warning: No texture bound! This may cause rendering issues.";
  }

  if (vbo_vertices_.isCreated()) {
    vbo_vertices_.bind();
    int vertex_location = shader_program->attributeLocation("position");
    if (vertex_location != -1) {
      shader_program->enableAttributeArray(vertex_location);
      shader_program->setAttributeBuffer(vertex_location, GL_FLOAT, 0, 3,
                                         sizeof(glm::vec3));
    }
  }

  if (vbo_normals_.isCreated()) {
    vbo_normals_.bind();
    int normalLocation = shader_program->attributeLocation("normal");
    if (normalLocation != -1) {
      shader_program->enableAttributeArray(normalLocation);
      shader_program->setAttributeBuffer(normalLocation, GL_FLOAT, 0, 3,
                                         sizeof(glm::vec3));
    }
  }

  if (vbo_texCoords_.isCreated()) {
    vbo_texCoords_.bind();
    int texCoordLocation = shader_program->attributeLocation("texCoord");
    if (texCoordLocation != -1) {
      shader_program->enableAttributeArray(texCoordLocation);
      shader_program->setAttributeBuffer(texCoordLocation, GL_FLOAT, 0, 2,
                                         sizeof(glm::vec2));
    }
  }

  if (ebo_.isCreated()) {
    ebo_.bind();
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);
    ebo_.release();
  }

  vbo_vertices_.release();
  vbo_normals_.release();
  vbo_texCoords_.release();

  if (texture_) {
    texture_->release();
  }
}

} // namespace components
} // namespace mini_creator
