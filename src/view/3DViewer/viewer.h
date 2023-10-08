#ifndef CPP4_3DVIEWER_V2_VIEW_3DVIEWER_VIEWER_H_
#define CPP4_3DVIEWER_V2_VIEW_3DVIEWER_VIEWER_H_

#define GL_SILENCE_DEPRECATION

#include <mainwindow.h>

#include <QFileDialog>
#include <QOpenGLFunctions>
#include <QThread>
#include <QWidget>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "GlU32.lib")

class viewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  double line_color_r_ = 0;
  double line_color_g_ = 0;
  double line_color_b_ = 0;
  double point_color_r_ = 0;
  double point_color_g_ = 0;
  double point_color_b_ = 0;
  GLfloat backgroud_color_r_ = 0;
  GLfloat backgroud_color_g_ = 0;
  GLfloat backgroud_color_b_ = 0;
  double line_width_ = 0;
  int line_box_ = 0;
  double point_width_ = 0;
  int point_box_ = 0;
  bool random_move_ = false;
  void change_projection();
  int projection_type = 0;

  explicit viewer(QWidget *parent = nullptr);

  double *ver_cub = NULL;
  int *ver_indexes = NULL;
  int vertexes;
  int indexes;
  int DrawFlag = 0;
  double xRot, yRot, zRot;

 private:
  float z;
  QPoint mPos;
  QTimer tmr;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
};

#endif  // CPP4_3DVIEWER_V2_VIEW_3DVIEWER_VIEWER_H_
