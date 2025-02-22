#include "object_control_widget.h"

#include <QColorDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "core/model_manager.h"

namespace mini_creator {
namespace ui {
namespace widgets {

ObjectControlWidget::ObjectControlWidget(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *main_layout = new QVBoxLayout(this);

  QGroupBox *transform_group_box = CreateTransformGroupBox();
  main_layout->addWidget(transform_group_box);

  QGroupBox *light_group_box = CreateLightGroupBox();
  main_layout->addWidget(light_group_box);

  reset_button_ = new QPushButton("Reset", this);
  main_layout->addWidget(reset_button_);

  setLayout(main_layout);

  ConnectSignals();
}

QGroupBox *ObjectControlWidget::CreateTransformGroupBox() {
  x_rotation_slider_ = CreateSlider(-180, 180, 0, 1);
  x_rotation_label_ = CreateLabel("X: 0°");
  y_rotation_slider_ = CreateSlider(-180, 180, 0, 1);
  y_rotation_label_ = CreateLabel("Y: 0°");
  z_rotation_slider_ = CreateSlider(-180, 180, 0, 1);
  z_rotation_label_ = CreateLabel("Z: 0°");

  x_translation_slider_ = CreateSlider(-10000, 10000, 0, 0.01f);
  x_translation_label_ = CreateLabel("X: 0.00");
  y_translation_slider_ = CreateSlider(-10000, 10000, 0, 0.01f);
  y_translation_label_ = CreateLabel("Y: 0.00");
  z_translation_slider_ = CreateSlider(-10000, 10000, 0, 0.01f);
  z_translation_label_ = CreateLabel("Z: 0.00");

  x_scale_slider_ = CreateSlider(1, 1000, 100, 0.01f);
  x_scale_label_ = CreateLabel("X: 1.000");
  y_scale_slider_ = CreateSlider(1, 1000, 100, 0.01f);
  y_scale_label_ = CreateLabel("Y: 1.000");
  z_scale_slider_ = CreateSlider(1, 1000, 100, 0.01f);
  z_scale_label_ = CreateLabel("Z: 1.000");

  QGroupBox *transform_group_box = new QGroupBox("Transform", this);
  QVBoxLayout *transform_layout = new QVBoxLayout(transform_group_box);

  QGroupBox *rotation_group = CreateGroupBox(
      "Rotation", {x_rotation_label_, x_rotation_slider_, y_rotation_label_,
                   y_rotation_slider_, z_rotation_label_, z_rotation_slider_});
  QGroupBox *translation_group = CreateGroupBox(
      "Translation",
      {x_translation_label_, x_translation_slider_, y_translation_label_,
       y_translation_slider_, z_translation_label_, z_translation_slider_});
  QGroupBox *scale_group = CreateGroupBox(
      "Scale", {x_scale_label_, x_scale_slider_, y_scale_label_,
                y_scale_slider_, z_scale_label_, z_scale_slider_});

  transform_layout->addWidget(rotation_group);
  transform_layout->addWidget(translation_group);
  transform_layout->addWidget(scale_group);
  transform_group_box->setLayout(transform_layout);

  return transform_group_box;
}

QGroupBox *ObjectControlWidget::CreateLightGroupBox() {
  direction_x_spinbox_ = new QDoubleSpinBox(this);
  direction_x_spinbox_->setRange(-100.0, 100.0);
  direction_x_spinbox_->setSingleStep(0.1);
  direction_x_spinbox_->setValue(0.0);
  direction_x_label_ = CreateLabel("X");

  direction_y_spinbox_ = new QDoubleSpinBox(this);
  direction_y_spinbox_->setRange(-100.0, 100.0);
  direction_y_spinbox_->setSingleStep(0.1);
  direction_y_spinbox_->setValue(0.0);
  direction_y_label_ = CreateLabel("Y");

  direction_z_spinbox_ = new QDoubleSpinBox(this);
  direction_z_spinbox_->setRange(-100.0, 100.0);
  direction_z_spinbox_->setSingleStep(0.1);
  direction_z_spinbox_->setValue(0.0);
  direction_z_label_ = CreateLabel("Z");

  QVBoxLayout *direction_layout = new QVBoxLayout;
  QHBoxLayout *x_layout = new QHBoxLayout;
  x_layout->addWidget(direction_x_label_, 1);
  x_layout->addWidget(direction_x_spinbox_, 2);

  QHBoxLayout *y_layout = new QHBoxLayout;
  y_layout->addWidget(direction_y_label_, 1);
  y_layout->addWidget(direction_y_spinbox_, 2);

  QHBoxLayout *z_layout = new QHBoxLayout;
  z_layout->addWidget(direction_z_label_, 1);
  z_layout->addWidget(direction_z_spinbox_, 2);

  direction_layout->addLayout(x_layout);
  direction_layout->addLayout(y_layout);
  direction_layout->addLayout(z_layout);

  ambient_color_label_ = CreateLabel("Ambient: (255, 255, 255)");
  diffuse_color_label_ = CreateLabel("Diffuse: (255, 255, 255)");
  specular_color_label_ = CreateLabel("Specular: (255, 255, 255)");
  ambient_button_ = new QPushButton("Choose", this);
  diffuse_button_ = new QPushButton("Choose", this);
  specular_button_ = new QPushButton("Choose", this);

  QVBoxLayout *color_layout = new QVBoxLayout;
  QHBoxLayout *ambient_layout = new QHBoxLayout;
  ambient_layout->addWidget(ambient_color_label_);
  ambient_layout->addWidget(ambient_button_);

  QHBoxLayout *diffuse_layout = new QHBoxLayout;
  diffuse_layout->addWidget(diffuse_color_label_);
  diffuse_layout->addWidget(diffuse_button_);

  QHBoxLayout *specular_layout = new QHBoxLayout;
  specular_layout->addWidget(specular_color_label_);
  specular_layout->addWidget(specular_button_);

  color_layout->addLayout(ambient_layout);
  color_layout->addLayout(diffuse_layout);
  color_layout->addLayout(specular_layout);

  QVBoxLayout *light_layout = new QVBoxLayout;
  light_layout->addLayout(direction_layout);
  light_layout->addLayout(color_layout);

  QGroupBox *light_group_box = new QGroupBox("Light");
  light_group_box->setLayout(light_layout);

  return light_group_box;
}

void ObjectControlWidget::ConnectSignals() {
  QObject::connect(x_rotation_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleXRotationChanged);
  QObject::connect(y_rotation_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleYRotationChanged);
  QObject::connect(z_rotation_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleZRotationChanged);

  QObject::connect(x_translation_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleXTranslationChanged);
  QObject::connect(y_translation_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleYTranslationChanged);
  QObject::connect(z_translation_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleZTranslationChanged);

  QObject::connect(x_scale_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleXScaleChanged);
  QObject::connect(y_scale_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleYScaleChanged);
  QObject::connect(z_scale_slider_, &QSlider::valueChanged, this,
                   &ObjectControlWidget::HandleZScaleChanged);

  QObject::connect(direction_x_spinbox_,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &ObjectControlWidget::HandleDirectionXChanged);
  QObject::connect(direction_y_spinbox_,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &ObjectControlWidget::HandleDirectionYChanged);
  QObject::connect(direction_z_spinbox_,
                   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
                   &ObjectControlWidget::HandleDirectionZChanged);

  QObject::connect(ambient_button_, &QPushButton::clicked, this,
                   &ObjectControlWidget::HandleAmbientChanged);
  QObject::connect(diffuse_button_, &QPushButton::clicked, this,
                   &ObjectControlWidget::HandleDiffuseChanged);
  QObject::connect(specular_button_, &QPushButton::clicked, this,
                   &ObjectControlWidget::HandleSpecularChanged);

  QObject::connect(reset_button_, &QPushButton::clicked, this,
                   &ObjectControlWidget::ResetSliders);
}

QSlider *ObjectControlWidget::CreateSlider(int min, int max, int initial_value,
                                           float step) {
  QSlider *slider = new QSlider(Qt::Horizontal, this);
  slider->setRange(min, max);
  slider->setValue(initial_value);
  slider->setSingleStep(step);
  slider->setPageStep(10);
  return slider;
}

QLabel *ObjectControlWidget::CreateLabel(const QString &text) {
  QLabel *label = new QLabel(text, this);
  return label;
}

QGroupBox *
ObjectControlWidget::CreateGroupBox(const QString &title,
                                    const QVector<QWidget *> &widgets) {
  QGroupBox *group_box = new QGroupBox(title, this);
  QVBoxLayout *group_layout = new QVBoxLayout(group_box);

  for (QWidget *widget : widgets) {
    group_layout->addWidget(widget);
  }
  group_box->setLayout(group_layout);

  return group_box;
}

void ObjectControlWidget::HandleXRotationChanged(const int value) {
  float rotation_value = static_cast<float>(value);
  x_rotation_label_->setText(QString("X: %1°").arg(rotation_value, 0, 'f', 1));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 rotation = model->GetRotation();
    rotation.x = rotation_value;
    model->SetRotation(rotation);
  }
}

void ObjectControlWidget::HandleYRotationChanged(const int value) {
  float rotation_value = static_cast<float>(value);
  y_rotation_label_->setText(QString("Y: %1°").arg(rotation_value, 0, 'f', 1));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 rotation = model->GetRotation();
    rotation.y = rotation_value;
    model->SetRotation(rotation);
  }
}

void ObjectControlWidget::HandleZRotationChanged(const int value) {
  float rotation_value = static_cast<float>(value);
  z_rotation_label_->setText(QString("Z: %1°").arg(rotation_value, 0, 'f', 1));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 rotation = model->GetRotation();
    rotation.z = rotation_value;
    model->SetRotation(rotation);
  }
}

void ObjectControlWidget::HandleXTranslationChanged(const int value) {
  float translated_value = value * 0.01f;
  x_translation_label_->setText(
      QString("X: %1").arg(translated_value, 0, 'f', 2));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 translate = model->GetTranslation();
    translate.x = translated_value;
    model->SetTranslation(translate);
  }
}

void ObjectControlWidget::HandleYTranslationChanged(const int value) {
  float translated_value = value * 0.01f;
  y_translation_label_->setText(
      QString("Y: %1").arg(translated_value, 0, 'f', 2));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 translate = model->GetTranslation();
    translate.y = translated_value;
    model->SetTranslation(translate);
  }
}

void ObjectControlWidget::HandleZTranslationChanged(const int value) {
  float translated_value = value * 0.01f;
  z_translation_label_->setText(
      QString("Z: %1").arg(translated_value, 0, 'f', 2));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 translate = model->GetTranslation();
    translate.z = translated_value;
    model->SetTranslation(translate);
  }
}

void ObjectControlWidget::HandleXScaleChanged(const int value) {
  float scaled_value = value * 0.01f;
  x_scale_label_->setText(QString("X: %1").arg(scaled_value, 0, 'f', 3));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 scale = model->GetScale();
    scale.x = scaled_value;
    model->SetScale(scale);
  }
}

void ObjectControlWidget::HandleYScaleChanged(const int value) {
  float scaled_value = value * 0.01f;
  y_scale_label_->setText(QString("Y: %1").arg(scaled_value, 0, 'f', 3));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 scale = model->GetScale();
    scale.y = scaled_value;
    model->SetScale(scale);
  }
}

void ObjectControlWidget::HandleZScaleChanged(const int value) {
  float scaled_value = value * 0.01f;
  z_scale_label_->setText(QString("Z: %1").arg(scaled_value, 0, 'f', 3));

  auto models = core::ModelManager::Instance().GetAllModels();
  for (auto &model : models) {
    glm::vec3 scale = model->GetScale();
    scale.z = scaled_value;
    model->SetScale(scale);
  }
}

void ObjectControlWidget::HandleDirectionXChanged(const double value) {}
void ObjectControlWidget::HandleDirectionYChanged(const double value) {}
void ObjectControlWidget::HandleDirectionZChanged(const double value) {}

void ObjectControlWidget::HandleAmbientChanged() {
  QColor color = QColorDialog::getColor(ambient_color_, this, "Ambient Color");
  if (color.isValid()) {
    ambient_color_ = color;
    ambient_color_label_->setText(QString("Ambient: (%1, %2, %3)")
                                      .arg(color.red())
                                      .arg(color.green())
                                      .arg(color.blue()));
  }
}

void ObjectControlWidget::HandleDiffuseChanged() {
  QColor color = QColorDialog::getColor(diffuse_color_, this, "Diffuse Color");
  if (color.isValid()) {
    diffuse_color_ = color;
    diffuse_color_label_->setText(QString("Ambient: (%1, %2, %3)")
                                      .arg(color.red())
                                      .arg(color.green())
                                      .arg(color.blue()));
  }
}

void ObjectControlWidget::HandleSpecularChanged() {
  QColor color =
      QColorDialog::getColor(specular_color_, this, "Specular Color");
  if (color.isValid()) {
    specular_color_ = color;
    specular_color_label_->setText(QString("Ambient: (%1, %2, %3)")
                                       .arg(color.red())
                                       .arg(color.green())
                                       .arg(color.blue()));
  }
}

void ObjectControlWidget::ResetSliders() {
  x_rotation_slider_->setValue(0);
  y_rotation_slider_->setValue(0);
  z_rotation_slider_->setValue(0);

  x_translation_slider_->setValue(0);
  y_translation_slider_->setValue(0);
  z_translation_slider_->setValue(0);

  x_scale_slider_->setValue(100);
  y_scale_slider_->setValue(100);
  z_scale_slider_->setValue(100);
}

} // namespace widgets
} // namespace ui
} // namespace mini_creator
