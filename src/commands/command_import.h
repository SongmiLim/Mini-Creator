#ifndef COMMAND_IMPORT_H
#define COMMAND_IMPORT_H

#include <QString>

namespace mini_creator {
namespace commands {

class CommandImport {
public:
  static void Execute(const QString& file_path);
  static void ImportTestCubeModel();
};

} // namespace commands
} // namespace mini_creator

#endif // COMMAND_IMPORT_H
