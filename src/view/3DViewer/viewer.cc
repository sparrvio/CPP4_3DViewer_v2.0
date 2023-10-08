#include "viewer.h"

viewer::viewer(QWidget *parent) : QOpenGLWidget(parent) {
  setWindowTitle("The View");
  setGeometry(600, 600, 600, 600);
}

void viewer::initializeGL() {
  glLoadIdentity();  // загружаем единичную матрицу для корректной работы
                     // glOrtho
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);  // буфер глубины - хранит расстояние от камеры до
  glTranslatef(0, 0,
               -4);  // сдвигаем систему координат по оси z видимую область
}

void viewer::resizeGL(int w, int h) {}

void viewer::paintGL() {
  if (random_move_ == false) {
    glLoadIdentity();  // загружаем единичную матрицу
  } else {
    int Point_Box = 1;

    if (line_color_r_ < 90) {
      QThread::msleep(50);
      line_color_r_ += 1;
    } else {
      line_color_r_ = 15;
    }
    if (point_color_b_ < 90) {
      point_color_b_ += 1;
    } else {
      point_color_b_ = 10;
    }
    if (line_width_ < 15) {
      line_width_ += 1;
    } else {
      line_width_ = 1;
    }
    if (point_width_ < 15) {
      point_width_ += 1;
    } else {
      point_width_ = 1;
    }
  }

  glClearColor(backgroud_color_r_ / 100, backgroud_color_g_ / 100,
               backgroud_color_b_ / 100, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // очищаем буфер цвета и буфер глубины
  glEnableClientState(GL_VERTEX_ARRAY);  // включаем массив вершин для рисования

  if (DrawFlag == 1) {
    if (line_box_ == 1) {
      glEnable(GL_LINE_STIPPLE);  // включаем рисование пунктиром
      glLineStipple(1, 0x0101);  // задаем маску для пунктира
    } else if (line_box_ == 2) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00F0);
    } else if (line_box_ == 3) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x1C47);
    }
    update();

    glColor3d(line_color_r_ / 100, line_color_g_ / 100,
              line_color_b_ / 100);  // применяем цвет линий

    glMatrixMode(GL_MODELVIEW);
    glLineWidth(line_width_);  // толщина линий

    if (random_move_ == false) {
      glLoadIdentity();
    }

    change_projection();

    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);

    glVertexPointer(3, GL_DOUBLE, 0,
                    ver_cub);  // определяем массив данных вершин

    glDrawElements(GL_LINES, indexes * 2, GL_UNSIGNED_INT,
                   ver_indexes);  // рисуем линии

    glPointSize(point_width_);  // изменение размера отображения для точек;

    if (point_box_ == 0) {
      glPointSize(0);
    } else if (point_box_ == 1) {
      glColor3d(point_color_r_ / 100, point_color_g_ / 100,
                point_color_b_ / 100);
      glEnable(GL_POINT_SMOOTH);  // включаем сглаживание
      glDrawElements(GL_POINTS, indexes * 2, GL_UNSIGNED_INT,
                     ver_indexes);  // рисуем точки круглые после сглаживания
    } else if (point_box_ == 2) {
      glColor3d(point_color_r_ / 100, point_color_g_ / 100,
                point_color_b_ / 100);
      glDrawElements(GL_POINTS, indexes * 2, GL_UNSIGNED_INT,
                     ver_indexes);  // рисуем квадратные точки
    }
    update();

    glDisableClientState(GL_VERTEX_ARRAY);  // отключаем массив вершин
    glDisable(GL_LINE_STIPPLE);  // отключаем рисование пунктиром
    glDisable(GL_POINT_SMOOTH);  // отключаем сглаживание
  }
}

void viewer::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void viewer::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 1 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 1 / M_PI * (mo->pos().x() - mPos.x());
  update();
}

void viewer::change_projection() {
  if (projection_type == 0) {
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  }
}
