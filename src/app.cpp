#include "app.h"

namespace mini_creator {

App::App(int &argc, char **argv) : app_(argc, argv), main_window_(nullptr) {}

int App::Execute() {
  main_window_ = new ui::MainWindow();
  main_window_->Show();

  return app_.exec();
}

App::~App() { delete main_window_; }

} // namespace mini_creator
