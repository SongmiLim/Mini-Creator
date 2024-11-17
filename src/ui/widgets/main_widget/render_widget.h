#ifndef RENDER_WIDGET_H
#define RENDER_WIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

namespace mini_creator {
namespace ui {
namespace widgets {
namespace main_widget {

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  explicit RenderWidget(QWidget *parent = nullptr);
  ~RenderWidget() = default;

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

} // namespace main_widget
} // namespace widgets
} // namespace ui
} // namespace mini_creator

#endif // RENDER_WIDGET_H
