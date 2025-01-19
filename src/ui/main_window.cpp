#include "main_window.h"
#include "widgets/render_widget.h"

#include <QHBoxLayout>
#include <QWidget>

namespace mini_creator {
namespace ui {

MainWindow::MainWindow()
    : menu_bar_(nullptr), tool_bar_(nullptr), render_widget_(nullptr),
      object_control_widget_(nullptr) {
  setWindowTitle("Mini Creator");
  setMinimumSize(800, 600);
  showMaximized();
}

void MainWindow::InitializeUI() {
  SetupMenuBar();
  SetupToolBar();
  SetupCentralWidget();
}

void MainWindow::SetupMenuBar() {
  menu_bar_ = new MenuBar();
  QMainWindow::setMenuBar(menu_bar_);
}

void MainWindow::SetupToolBar() {
  tool_bar_ = new ToolBar(this);
  QMainWindow::addToolBar(tool_bar_);
}

void MainWindow::SetupCentralWidget() {
  QWidget *central_widget = new QWidget;
  QMainWindow::setCentralWidget(central_widget);

  render_widget_ = new widgets::RenderWidget(this);
  object_control_widget_ = new widgets::ObjectControlWidget(this);

  QHBoxLayout *main_layout = new QHBoxLayout;
  main_layout->addWidget(render_widget_, 4);
  main_layout->addWidget(object_control_widget_, 1);

  central_widget->setLayout(main_layout);
}

void MainWindow::Show() {
  InitializeUI();
  QMainWindow::show();
}

} // namespace ui
} // namespace mini_creator
