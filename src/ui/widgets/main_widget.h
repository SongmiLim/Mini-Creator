#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>

#include "main_widget/render_widget.h"

namespace mini_creator {
namespace ui {
namespace widgets {

class MainWidget : public QWidget {
  Q_OBJECT

public:
  explicit MainWidget(QWidget *parent = nullptr);
  ~MainWidget() = default;

private:
  main_widget::RenderWidget *render_widget_;
};

} // namespace widgets
} // namespace ui
} // namespace mini_creator

#endif // MAIN_WIDGET_H
