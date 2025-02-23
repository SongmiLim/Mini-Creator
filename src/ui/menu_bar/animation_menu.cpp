#include "animation_menu.h"

#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>

#include "commands/command_import.h"

namespace mini_creator {
namespace ui {
namespace menu_bar {

AnimationMenu::AnimationMenu() : QMenu("&Animation") {
  LoadActions();
  AddActionsToMenu();
}

void AnimationMenu::LoadActions() {}

void AnimationMenu::AddActionsToMenu() {}

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator