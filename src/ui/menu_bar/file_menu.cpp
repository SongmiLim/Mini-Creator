#include "file_menu.h"

#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>


namespace mini_creator {
namespace ui {
namespace menu_bar {

FileMenu::FileMenu() : QMenu("&File") {
  InitializeActions();
  AddActionsToMenu();
}

void FileMenu::InitializeActions() {
  new_action_ = new QAction(
      QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew).pixmap(QSize(16, 16)),
      "&New", this);
  import_action_ = new QAction(
      QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen).pixmap(QSize(16, 16)),
      "&Import", this);

  QMenu::connect(new_action_, &QAction::triggered, this, &FileMenu::HandleNew);
  QMenu::connect(import_action_, &QAction::triggered, this,
                 &FileMenu::HandleImport);
}

void FileMenu::AddActionsToMenu() {
  QMenu::addAction(new_action_);
  QMenu::addAction(import_action_);
}

void FileMenu::HandleNew() {}

void FileMenu::HandleImport() {
  QString fileName =
      QFileDialog::getOpenFileName(this, "file explore", "", "*.obj, *fbx");

  if (!fileName.isEmpty()) {
    QMessageBox::information(this, "open", "selected file: " + fileName);
  }
}

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator