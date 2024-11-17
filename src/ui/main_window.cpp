#include "main_window.h"

namespace mini_creator{
namespace ui{

MainWindow::MainWindow() {
    setWindowTitle("Mini Creator");
    setMinimumSize(1600, 900);
    showMaximized();
}

void MainWindow::Render() {
    show();
}

}
}

