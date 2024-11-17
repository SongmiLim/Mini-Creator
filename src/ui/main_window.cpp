#include "main_window.h"

namespace mini_creator{
namespace ui{

MainWindow::MainWindow() {
    QMainWindow::setWindowTitle("Mini Creator");
    QMainWindow::setMinimumSize(800, 600);
    QMainWindow::showMaximized();

    menu_bar_ = new MenuBar();
    QMainWindow::setMenuBar(menu_bar_);
}

void MainWindow::Render() {
    QMainWindow::show();
}

}
}

