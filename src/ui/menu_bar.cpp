#include "menu_bar.h"

namespace mini_creator {
namespace ui {

MenuBar::MenuBar() : QMenuBar() {
  file_menu_ = new menu_bar::FileMenu();
  QMenuBar::addMenu(file_menu_);

  edit_menu_ = new menu_bar::EditMenu();
  QMenuBar::addMenu(edit_menu_);

  animation_menu_ = new menu_bar::AnimationMenu();
  QMenuBar::addMenu(animation_menu_);
  
  camera_menu_ = new menu_bar::CameraMenu();
  QMenuBar::addMenu(camera_menu_);
}

} // namespace ui
} // namespace mini_creator
