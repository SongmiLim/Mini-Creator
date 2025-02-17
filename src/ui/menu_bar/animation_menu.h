#ifndef ANIMATION_MENU_H_
#define ANIMATION_MENU_H_

#include <QMenu>

namespace mini_creator {
namespace ui {
namespace menu_bar {

class AnimationMenu : public QMenu {
  Q_OBJECT

public:
  explicit AnimationMenu();

private slots:

private:
  void SetupActions();
  void AddActionsToMenu();
};

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator

#endif // ANIMATION_MENU_H_