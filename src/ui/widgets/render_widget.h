#ifndef RENDER_WIDGET_H
#define RENDER_WIDGET_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>

namespace mini_creator {
namespace ui {
namespace widgets {

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  explicit RenderWidget(QWidget *parent = nullptr);
  ~RenderWidget() = default;

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private:
  void SetupShaders();

  QOpenGLShaderProgram *shader_program_;

  QMatrix4x4 projection_matrix_;
  QMatrix4x4 view_matrix_;
  QMatrix4x4 model_matrix_;
};

} // namespace widgets
} // namespace ui
} // namespace mini_creator

#endif // RENDER_WIDGET_H
