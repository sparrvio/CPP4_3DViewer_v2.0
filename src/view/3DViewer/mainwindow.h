#ifndef CPP4_3DVIEWER_V2_VIEW_3DVIEWER_MAINWINDOW_H_
#define CPP4_3DVIEWER_V2_VIEW_3DVIEWER_MAINWINDOW_H_

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QMoveEvent>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QtOpenGL>
#include <QtWidgets/QWidget>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../../controller/controller.h"
#include "../../model/affine_transformations_strategy.h"
#include "../../model/model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr, s21::Controller *controller = nullptr);
  ~MainWindow();
  QString filename = NULL;
  QTimer *timer;
  QString GIF_PATH = QDir::homePath();
  QSettings *settings;

 private slots:
  void on_OpenFile_clicked();
  void on_Draw_clicked();
  void on_sliderScale_valueChanged(int value);
  void on_MOVE_clicked();
  void on_ROTATE_clicked();
  void on_RESIZE_clicked();
  void on_Slider_Color_R_valueChanged(int value);
  void on_Slider_Color_G_valueChanged(int value);
  void on_Slider_Color_B_valueChanged(int value);
  void on_Background_R_valueChanged(int value);
  void on_Background_G_valueChanged(int value);
  void on_Background_B_valueChanged(int value);
  void on_OFF_clicked();
  void on_Line_Box_activated(int index);
  void on_SAVE_clicked();
  void on_Point_Box_currentIndexChanged(int index);
  void on_Point_Color_R_valueChanged(int value);
  void on_Point_Color_G_valueChanged(int value);
  void on_Point_Color_B_valueChanged(int value);
  void on_dial_Line_Width_valueChanged(int value);
  void on_dial_Point_Width_valueChanged(int value);
  void on_SAVE_settings_clicked();
  void on_Load_settings_clicked();
  void on_GIF_clicked();
  void on_Random_Move_clicked(bool checked);
  void on_GIF_2_clicked();
  void save_gif();
  void AddFrameWhenTimeout();
  void set_projection();
  void on_random_Hide_clicked();
  void on_random_Show_clicked();

 private:
  Ui::MainWindow *ui;
  QVector<QImage> gif;
  int counter = 0;
  s21::Controller *controller_;
  // AffineTransformContext transformContext;
};
};  // namespace s21

#endif  // CPP4_3DVIEWER_V2_VIEW_3DVIEWER_MAINWINDOW_H_
