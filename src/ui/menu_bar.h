#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>

#include "menu_bar/file_menu.h"
#include "menu_bar/edit_menu.h"
#include "menu_bar/animation_menu.h"
#include "menu_bar/camera_menu.h"

namespace mini_creator {
namespace ui {

class MenuBar : public QMenuBar {
  Q_OBJECT

public:
  explicit MenuBar();
  ~MenuBar() = default;
  
  void Render();

private:
  void CreateMenu();
  
  menu_bar::FileMenu *file_menu_;
  menu_bar::EditMenu *edit_menu_;
  menu_bar::AnimationMenu *animation_menu_;
  menu_bar::CameraMenu *camera_menu_;
};

} // namespace ui
} // namespace mini_creator

#endif // MENUBAR_H
