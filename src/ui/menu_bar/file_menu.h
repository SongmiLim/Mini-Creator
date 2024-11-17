#ifndef FILE_MENU_H_
#define FILE_MENU_H_

#include <QMenu>

namespace mini_creator {
namespace ui {
namespace menu_bar {

class FileMenu : public QMenu {
  Q_OBJECT

public:
  explicit FileMenu();

private slots:
  void HandleNew();
  void HandleImport();

private:
  void InitializeActions();
  void AddActionsToMenu();

  QAction *new_action_;
  QAction *import_action_;
};

} // namespace menu_bar
} // namespace ui
} // namespace mini_creator

#endif // FILE_MENU_H_