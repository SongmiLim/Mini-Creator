#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "ui/menu_bar.h"
#include "ui/tool_bar.h"
#include "ui/widgets/object_control_widget.h"
#include "ui/widgets/render_widget.h"

namespace mini_creator {
namespace ui {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow();
  ~MainWindow() = default;

  void Show();

private:
  void LoadUi();
  void LoadMenuBar();
  void LoadToolBar();
  void LoadCentralWidget();

  MenuBar *menu_bar_;
  ToolBar *tool_bar_;

  widgets::ObjectControlWidget *object_control_widget_;
  widgets::RenderWidget *render_widget_;
};

} // namespace ui
} // namespace mini_creator

#endif // MAIN_WINDOW_H
