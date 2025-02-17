#ifndef EDIT_MENU_H_
#define EDIT_MENU_H_

#include <QMenu>

namespace mini_creator {
namespace ui {
namespace menu_bar {

class EditMenu : public QMenu {
  Q_OBJECT

public:
  explicit EditMenu();

private slots:

private:
  void SetupActions();
  void AddActionsToMenu();
};

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator

#endif // EDIT_MENU_H_