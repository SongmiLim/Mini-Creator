#ifndef FILE_MENU_H_
#define FILE_MENU_H_

#include <QMenu>
#include <QActionGroup>

namespace mini_creator {
namespace ui {
namespace menu_bar {

class FileMenu : public QMenu {
  Q_OBJECT

 public:
	 FileMenu();

 private slots:
	 void HandleNew();
	 void HandleImport();

 private:
	 void InitializeActions();
	 void AddActionsToMenu();

	  QAction* new_action_;
	  QAction* import_action_;
};

}
}
}

#endif  // FILE_MENU_H_