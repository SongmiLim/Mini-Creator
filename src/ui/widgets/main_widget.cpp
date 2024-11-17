#include "main_widget.h"

#include <QVBoxLayout>

namespace mini_creator {
namespace ui {
namespace widgets {

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout;

  render_widget_ = new main_widget::RenderWidget();
  layout->addWidget(render_widget_);

  setLayout(layout);
}

} // namespace widgets
} // namespace ui
} // namespace mini_creator