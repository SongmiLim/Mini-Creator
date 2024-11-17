#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>


#include "menu_bar/file_menu.h"

namespace mini_creator {
namespace ui {

class MenuBar : public QMenuBar {
  Q_OBJECT

public:
  explicit MenuBar();
  void Render();
  ~MenuBar();

private:
  void CreateMenu();
  menu_bar::FileMenu *file_menu_;
};

} // namespace ui
} // namespace mini_creator

#endif // MENUBAR_H
