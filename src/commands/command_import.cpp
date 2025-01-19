#include "command_import.h"

#include <QFile>
#include <QTextStream>
#include <iostream>

#include "../core/model_manager.h"

namespace mini_creator {
namespace commands {

void CommandImport::Execute(const QString& file_path) {
    QFile file(file_path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Failed to open file: " << file_path.toStdString() << std::endl;
        return;
    }

    std::vector<GLfloat> vertices;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList values = line.split(" ");
        for (const QString& value : values) {
            vertices.push_back(value.toFloat());
        }
    }

    std::shared_ptr<core::Model> model = std::make_shared<core::Model>(file_path);
    model->Initialize(vertices);
    core::ModelManager::Instance().AddModel(model);
}

void CommandImport::ImportTestCubeModel() {
      std::vector<GLfloat> cubeVertices = {
  -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f, -0.5f, -0.5f,  0.5f, -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f, -0.5f,  0.5f,  0.5f, -0.5f,  0.5f, -0.5f
    };

    std::shared_ptr<core::Model> model = std::make_shared<core::Model>("TestCube");
    model->Initialize(cubeVertices);
    core::ModelManager::Instance().AddModel(model);
}

} // namespace commands
} // namespace mini_creator
