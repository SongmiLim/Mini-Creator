#include "mesh.h"

#include <qdebug.h>

namespace mini_creator {
namespace model {

Mesh::Mesh() : ebo_(QOpenGLBuffer::IndexBuffer) {
  QOpenGLFunctions::initializeOpenGLFunctions();

  // vbo_vertices_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  // vbo_normals_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  // vbo_texCoords_ = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  // ebo_ = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

  // vertex_count_ = 0;
  index_count_ = 0;
}

Mesh::~Mesh() {
  vbo_vertices_.destroy();
  vbo_normals_.destroy();
  vbo_texCoords_.destroy();
  ebo_.destroy();
}

void Mesh::SetVertices(const std::vector<glm::vec3> &vertices) {
  if (vertices.empty()) {
    qDebug() << "Mesh::SetVertices - Empty vertex data.";
    return;
  }
  vbo_vertices_.create();
  vbo_vertices_.bind();
  vbo_vertices_.allocate(vertices.data(), vertices.size() * sizeof(glm::vec3));
  vbo_vertices_.release();

  // vertex_count_ = static_cast<int>(vertices_.size());
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

void Mesh::SetIndices(const std::vector<uint32_t> &indices) {
  if (indices.empty()) {
    return;
  }
  ebo_.create();
  ebo_.bind();
  ebo_.allocate(indices.data(), indices.size() * sizeof(uint32_t));
  ebo_.release();

  index_count_ = static_cast<int>(indices.size());

  // qDebug() << "Vertex count:" << vertex_count_;
}

// void Mesh::SetMaterial(std::shared_ptr<Material> material) {
//   material_ = material;
//   qDebug() << "Material set for mesh.";
// }

void Mesh::Draw(QOpenGLShaderProgram *shader_program) {
  if (!shader_program) {
    qDebug() << "Mesh::Draw - Shader program is null.";
    return;
  }

  if (vbo_vertices_.isCreated()) {
    vbo_vertices_.bind();
    int vertex_location = shader_program->attributeLocation("position");
    if (vertex_location == -1) {
      qDebug() << "Shader attribute 'position' not found.";
      return;
    }
    shader_program->enableAttributeArray(vertex_location);
    shader_program->setAttributeBuffer(vertex_location, GL_FLOAT, 0, 3,
                                       sizeof(glm::vec3));
  }

  if (vbo_normals_.isCreated()) {
    vbo_normals_.bind();
    int normalLocation = shader_program->attributeLocation("normal");
    if (normalLocation != -1) {
      shader_program->enableAttributeArray(normalLocation);
      shader_program->setAttributeBuffer(normalLocation, GL_FLOAT, 0, 3,
                                         sizeof(glm::vec3));
    } else {
      // qDebug() << "Mesh::Draw - Normal attribute not found.";
    }
  }

  // vbo_texCoords_.bind();
  // int texCoordLocation = shader_program->attributeLocation("texCoord");
  // if (texCoordLocation != -1) {
  //   shader_program->enableAttributeArray(texCoordLocation);
  //   shader_program->setAttributeBuffer(texCoordLocation, GL_FLOAT, 0, 2,
  //                                      sizeof(glm::vec2));
  // } else {
  //   // qDebug() << "Mesh::Draw - Texture coordinate attribute not found.";
  // }
  
  if (ebo_.isCreated()) {
    ebo_.bind();
    glDrawElements(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);

    // vbo_vertices_.release();
    // vbo_normals_.release();
    // vbo_texCoords_.release();
    // ebo_.release();
    // shader_program->release();
  } else {
    // glDrawArray(GL_TRIANGLES, index_count_, GL_UNSIGNED_INT, nullptr);

  }
}

} // namespace model
} // namespace mini_creator
