#ifndef RENDER_WIDGET_H
#define RENDER_WIDGET_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QWheelEvent>

#include "../../components/camera.h"

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

  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private slots:
  void ToggleCameraMode();

private:
  void SetupShaders();
  void AdjustCameraToModel();

  void SetupUI();
  void UpdateToggleButtonText();

  QOpenGLShaderProgram *shader_program_;
  QPushButton *toggle_button_;

  std::shared_ptr<components::Camera> camera_;

  bool is_mouse_pressed_ = false;
  QPoint last_mouse_pos_;
};

} // namespace widgets
} // namespace ui
} // namespace mini_creator

#endif // RENDER_WIDGET_H
