#ifndef TOOL_BAR_H_
#define TOOL_BAR_H_

#include <QToolBar>

namespace mini_creator {
namespace ui {

class ToolBar : public QToolBar {
  Q_OBJECT

public:
  explicit ToolBar(QWidget *parent = nullptr);
  ~ToolBar() = default;

private slots:
  void HandleNew();
  void HandleImport();

private:
  void AddActionsToToolBar();
  void InitializeActions();

  QAction *new_action_;
  QAction *import_action_;
};

} // namespace ui
} // namespace mini_creator

#endif // TOOL_BAR_H_