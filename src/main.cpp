#include "app.h"

int main(int argc, char *argv[]) {
  mini_creator::App app(argc, argv);

  return app.Execute();
}