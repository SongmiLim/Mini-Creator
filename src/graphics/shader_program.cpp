#include "shader_program.h"

#include <QCoreApplication>
#include <QDebug>

namespace mini_creator {
namespace graphics {

ShaderProgram::ShaderProgram() { shader_program_ = new QOpenGLShaderProgram(); }

ShaderProgram::~ShaderProgram() {
  if (shader_program_) {
    delete shader_program_;
    shader_program_ = nullptr;
  }
}

bool ShaderProgram::Load(const QString &vertexPath,
                         const QString &fragmentPath) {
  if (!shader_program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                                vertexPath)) {
    qDebug() << "Vertex ShaderProgram Error: " << shader_program_->log();
    return false;
  }

  if (!shader_program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                                fragmentPath)) {
    qDebug() << "Fragment ShaderProgram Error: " << shader_program_->log();
    return false;
  }

  if (!shader_program_->link()) {
    qDebug() << "ShaderProgram Program Linking Error: "
             << shader_program_->log();
    return false;
  }

  return true;
}

void ShaderProgram::Use() {
  if (shader_program_) {
    shader_program_->bind();
  }
}

void ShaderProgram::SetUniform(const QString &name, float value) {
  shader_program_->setUniformValue(name.toUtf8().constData(), value);
}

void ShaderProgram::SetUniform(const QString &name, int value) {
  shader_program_->setUniformValue(name.toUtf8().constData(), value);
}

void ShaderProgram::SetUniform(const QString &name, const QVector3D &value) {
  shader_program_->setUniformValue(name.toUtf8().constData(), value);
}

void ShaderProgram::SetUniform(const QString &name, const glm::vec3 &value) {
  shader_program_->setUniformValue(name.toUtf8().constData(), value.r, value.g,
                                   value.b);
}

void ShaderProgram::SetUniform(const QString &name, const QMatrix4x4 &matrix) {
  shader_program_->setUniformValue(name.toUtf8().constData(), matrix);
}

void ShaderProgram::SetAttribute(const QString &name, GLenum type, int offset,
                                 int size, int stride) {
  int location = shader_program_->attributeLocation(name);
  if (location != -1) {
    shader_program_->enableAttributeArray(location);
    shader_program_->setAttributeBuffer(location, type, offset, size, stride);
  } else {
    qDebug() << "Attribute not found: " << name;
  }
}

} // namespace graphics
} // namespace mini_creator
