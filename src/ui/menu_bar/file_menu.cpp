#include "file_menu.h"

#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>

#include "../../commands/command_import.h"
namespace mini_creator {
namespace ui {
namespace menu_bar {

FileMenu::FileMenu() : QMenu("&File") {
  SetupActions();
  AddActionsToMenu();
}

void FileMenu::SetupActions() {
  new_action_ = new QAction(
      QIcon::fromTheme("document-new").pixmap(QSize(16, 16)), "&New", this);
  import_action_ = new QAction(
      QIcon::fromTheme("document-open").pixmap(QSize(16, 16)), "&Import", this);

  QMenu::connect(new_action_, &QAction::triggered, this,
                 &FileMenu::OnNewTriggered);
  QMenu::connect(import_action_, &QAction::triggered, this,
                 &FileMenu::OnImportTriggered);
}

void FileMenu::AddActionsToMenu() {
  QMenu::addAction(new_action_);
  QMenu::addAction(import_action_);
}

void FileMenu::OnNewTriggered() {}

void FileMenu::OnImportTriggered() {
  QString fileName = QFileDialog::getOpenFileName(
      this, "File Explorer", "",
      "3D Model Files (*.obj *.fbx);;OBJ Files (*.obj);;FBX Files (*.fbx)");

  if (!fileName.isEmpty()) {
    commands::CommandImport::Execute(fileName);
  } else {
    QMessageBox::warning(this, "Error", "No file selected!");
  }
}

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator