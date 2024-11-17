#include "menu_bar.h"

namespace mini_creator {
namespace ui {

MenuBar::MenuBar() : QMenuBar() {
  file_menu_ = new menu_bar::FileMenu();
  QMenuBar::addMenu(file_menu_);
}

MenuBar::~MenuBar() {}

} // namespace ui
} // namespace mini_creator
