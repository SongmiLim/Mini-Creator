#include "camera_menu.h"

#include <QActionGroup>
#include <QMessageBox>

#include "commands/command_import.h"

namespace mini_creator {
namespace ui {
namespace menu_bar {

CameraMenu::CameraMenu() : QMenu("&Camera") {
  LoadActions();
  AddActionsToMenu();
}

void CameraMenu::LoadActions() {}

void CameraMenu::AddActionsToMenu() {}

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator