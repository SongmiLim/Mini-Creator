#include "menu_bar.h"

#include <QFileDialog>
#include <QMessageBox>

namespace mini_creator{
namespace ui{

MenuBar::MenuBar() : QMenuBar() {
    file_menu_ = new menu_bar::FileMenu();
    QMenuBar::addMenu(file_menu_);
}

MenuBar::~MenuBar() {}

}
}
