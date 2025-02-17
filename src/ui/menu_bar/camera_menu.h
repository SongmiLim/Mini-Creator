#ifndef CAMERA_MENU_H_
#define CAMERA_MENU_H_

#include <QMenu>

namespace mini_creator {
namespace ui {
namespace menu_bar {

class CameraMenu : public QMenu {
  Q_OBJECT

public:
  explicit CameraMenu();

private slots:

private:
  void SetupActions();
  void AddActionsToMenu();
};

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator

#endif // CAMERA_MENU_H_