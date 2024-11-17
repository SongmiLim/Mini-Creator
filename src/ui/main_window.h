#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "menu_bar.h"
#include "tool_bar.h"

namespace mini_creator{
namespace ui{

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    void Render();

private:
    MenuBar *menu_bar_;
    ToolBar *tool_bar_;
};

}
}

#endif // MAIN_WINDOW_H
