#ifndef APP_H
#define APP_H

#include <QApplication>

#include "ui/main_window.h"

namespace mini_creator {

class App {
public:
  App(int &argc, char **argv);

  int Run();

  ~App();

private:
  QApplication app_;
  ui::MainWindow *main_window_;
};

} // namespace mini_creator

#endif // APP_H
