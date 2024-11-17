#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <QAction>

#include "menu_bar/file_menu.h"

namespace mini_creator{
namespace ui{

class MenuBar : public QMenuBar {
    Q_OBJECT

public:
    MenuBar();
    void Render();
    ~MenuBar();

private:
    void CreateMenu();
    menu_bar::FileMenu* file_menu_;
};

}
}

#endif // MENUBAR_H
