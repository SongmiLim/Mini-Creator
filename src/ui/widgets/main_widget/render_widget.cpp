#include "render_widget.h"

namespace mini_creator {
namespace ui {
namespace widgets {
namespace main_widget {

RenderWidget::RenderWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void RenderWidget::initializeGL() { initializeOpenGLFunctions(); }

void RenderWidget::resizeGL(int w, int h) {}

void RenderWidget::paintGL() {}

} // namespace main_widget
} // namespace widgets
} // namespace ui
} // namespace mini_creator