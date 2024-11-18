#ifndef OBJECT_CONTROL_WIDGET_H
#define OBJECT_CONTROL_WIDGET_H

#include <QCheckBox>
#include <QColor>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QWidget>


namespace mini_creator {
namespace ui {
namespace widgets {

class ObjectControlWidget : public QWidget {
  Q_OBJECT

public:
  explicit ObjectControlWidget(QWidget *parent = nullptr);
  ~ObjectControlWidget() = default;

private slots:
  void HandleXRotationChanged(const int value);
  void HandleYRotationChanged(const int value);
  void HandleZRotationChanged(const int value);
  void HandleXTranslationChanged(const int value);
  void HandleYTranslationChanged(const int value);
  void HandleZTranslationChanged(const int value);
  void HandleXScaleChanged(const int value);
  void HandleYScaleChanged(const int value);
  void HandleZScaleChanged(const int value);
  void HandleDirectionXChanged(const double value);
  void HandleDirectionYChanged(const double value);
  void HandleDirectionZChanged(const double value);
  void HandleAmbientChanged();
  void HandleDiffuseChanged();
  void HandleSpecularChanged();
  void ResetSliders();

private:
  QSlider *CreateSlider(int min, int max, int initial_value);
  QLabel *CreateLabel(const QString &text);
  QGroupBox *CreateGroupBox(const QString &title,
                            const QVector<QWidget *> &widgets);
  QGroupBox *CreateTransformGroupBox();
  QGroupBox *CreateLightGroupBox();
  void ConnectSignals();

  QCheckBox *animation_checkbox_;

  QSlider *x_rotation_slider_;
  QSlider *y_rotation_slider_;
  QSlider *z_rotation_slider_;
  QLabel *x_rotation_label_;
  QLabel *y_rotation_label_;
  QLabel *z_rotation_label_;

  QSlider *x_translation_slider_;
  QSlider *y_translation_slider_;
  QSlider *z_translation_slider_;
  QLabel *x_translation_label_;
  QLabel *y_translation_label_;
  QLabel *z_translation_label_;

  QSlider *x_scale_slider_;
  QSlider *y_scale_slider_;
  QSlider *z_scale_slider_;
  QLabel *x_scale_label_;
  QLabel *y_scale_label_;
  QLabel *z_scale_label_;

  QDoubleSpinBox *direction_x_spinbox_;
  QDoubleSpinBox *direction_y_spinbox_;
  QDoubleSpinBox *direction_z_spinbox_;
  QVector<QDoubleSpinBox *> direction_sliders_;
  QLabel *direction_x_label_;
  QLabel *direction_y_label_;
  QLabel *direction_z_label_;
  QVector<QLabel *> direction_labels_;

  QColor ambient_color_;
  QColor diffuse_color_;
  QColor specular_color_;
  QLabel *ambient_color_label_;
  QLabel *diffuse_color_label_;
  QLabel *specular_color_label_;
  QPushButton *ambient_button_;
  QPushButton *diffuse_button_;
  QPushButton *specular_button_;

  QPushButton *reset_button_;
};

} // namespace widgets
} // namespace ui
} // namespace mini_creator

#endif // OBJECT_CONTROL_WIDGET_H
