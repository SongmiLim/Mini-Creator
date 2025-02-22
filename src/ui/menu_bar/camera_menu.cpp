#include "camera_menu.h"

#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>

#include "commands/command_import.h"

namespace mini_creator {
namespace ui {
namespace menu_bar {

CameraMenu::CameraMenu() : QMenu("&Camera") {
  SetupActions();
  AddActionsToMenu();
}

void CameraMenu::SetupActions() {}

void CameraMenu::AddActionsToMenu() {}

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator