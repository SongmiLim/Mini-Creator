
#include "tool_bar.h"

#include <QFileDialog>
#include <QIcon>
#include <QMessageBox>

namespace mini_creator {
namespace ui {

ToolBar::ToolBar(QWidget *parent) : QToolBar(parent) {
  InitializeActions();
  AddActionsToToolBar();
}

void ToolBar::InitializeActions() {
  new_action_ = new QAction(
      QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew).pixmap(QSize(10, 10)),
      "New", this);
  import_action_ = new QAction(
      QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen).pixmap(QSize(10, 10)),
      "Import", this);

  connect(new_action_, &QAction::triggered, this, &ToolBar::HandleNew);
  connect(import_action_, &QAction::triggered, this, &ToolBar::HandleImport);
}

void ToolBar::AddActionsToToolBar() {
  QToolBar::addAction(new_action_);
  QToolBar::addAction(import_action_);
}

void ToolBar::HandleNew() {}

void ToolBar::HandleImport() {
  QString selectedFile = QFileDialog::getOpenFileName(
      this, "Select File", "", "3D Models (*.obj *.fbx)");

  if (!selectedFile.isEmpty()) {
    QMessageBox::information(this, "File Selected",
                             "You selected: " + selectedFile);
  }
}

} // namespace ui
} // namespace mini_creator