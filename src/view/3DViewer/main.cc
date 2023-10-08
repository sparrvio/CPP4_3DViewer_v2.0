#include <locale.h>

#include <QApplication>

#include "../../model/affine_transformations_strategy.h"
#include "../../model/model.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  setlocale(LC_ALL, "C");
  s21::Model model;
  s21::Controller controller;
  s21::MainWindow w(nullptr, &controller);

  w.setWindowTitle("3DViewer_v2");
  w.show();
  return a.exec();
}
