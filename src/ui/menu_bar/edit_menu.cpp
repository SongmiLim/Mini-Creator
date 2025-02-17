#include "edit_menu.h"

#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>

#include "../../commands/command_import.h"

namespace mini_creator {
namespace ui {
namespace menu_bar {

EditMenu::EditMenu() : QMenu("&Edit") {
  SetupActions();
  AddActionsToMenu();
}

void EditMenu::SetupActions() {}

void EditMenu::AddActionsToMenu() {}

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator