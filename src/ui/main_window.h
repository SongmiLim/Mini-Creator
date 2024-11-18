#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "menu_bar.h"
#include "tool_bar.h"
#include "widgets/main_widget.h"
#include "widgets/object_control_widget.h"

namespace mini_creator {
namespace ui {

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow();

  void Render();

  ~MainWindow() = default;

private:
  MenuBar *menu_bar_;
  ToolBar *tool_bar_;

  widgets::MainWidget *main_widget_;
  widgets::ObjectControlWidget *object_control_widget_;
};

} // namespace ui
} // namespace mini_creator

#endif // MAIN_WINDOW_H
