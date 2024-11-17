#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace mini_creator{
namespace ui{

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    void Render();
};

}
}

#endif // MAIN_WINDOW_H
