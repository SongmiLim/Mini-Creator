#include "main_window.h"

#include <QHBoxLayout>
#include <QWidget>

namespace mini_creator {
namespace ui {

MainWindow::MainWindow() {
  QMainWindow::setWindowTitle("Mini Creator");
  QMainWindow::setMinimumSize(800, 600);
  QMainWindow::showMaximized();

  menu_bar_ = new MenuBar();
  QMainWindow::setMenuBar(menu_bar_);

  tool_bar_ = new ToolBar(this);
  QMainWindow::addToolBar(tool_bar_);

  QWidget *central_widget = new QWidget;
  QMainWindow::setCentralWidget(central_widget);

  main_widget_ = new widgets::MainWidget(this);
  object_control_widget_ = new widgets::ObjectControlWidget(this);

  QHBoxLayout *main_layout = new QHBoxLayout;
  main_layout->addWidget(main_widget_, 4);
  main_layout->addWidget(object_control_widget_, 1);

  central_widget->setLayout(main_layout);
}

void MainWindow::Render() { QMainWindow::show(); }

} // namespace ui
} // namespace mini_creator
