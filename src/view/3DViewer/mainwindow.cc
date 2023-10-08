#include "mainwindow.h"

#include <math.h>

#include <QDebug>

#include "../3rdParty/giflib/gif_hash.h"
#include "../3rdParty/giflib/gif_lib.h"
#include "../3rdParty/giflib/gif_lib_private.h"
#include "../gifimage/qgifglobal.h"
#include "../gifimage/qgifimage.h"
#include "../gifimage/qgifimage_p.h"
#include "./ui_mainwindow.h"
#include "gif.h"

namespace s21 {

MainWindow::MainWindow(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller_(controller) {
  setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

  ui->setupUi(this);
  timer = new QTimer(this);
  connect(ui->Perspective, SIGNAL(clicked()), this, SLOT(set_projection()));
  connect(ui->Ortho, SIGNAL(clicked()), this, SLOT(set_projection()));

  ui->Draw->hide();
  ui->Clean->hide();
  ui->Random_Move->hide();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_OpenFile_clicked()

{
  ui->Error_message->clear();
  QString defaultPath = QDir::homePath();
  QString folder1 = "Desktop";
  QString folder2 = "File_obj";
  defaultPath = QDir::cleanPath(defaultPath + QDir::separator() + folder1 +
                                QDir::separator() + folder2);
  filename = QFileDialog::getOpenFileName(this, "Open file", defaultPath,
                                          "OBJ Files (*.obj)");

  if (!filename.isEmpty()) {
    ui->FilePath->setText(filename);

    QByteArray str = filename.toLocal8Bit();
    char *filename_str = str.data();

    ui->widget->vertexes = controller_->GetVertex(filename_str);
    ui->widget->indexes = controller_->GetFacet(filename_str);

    int i_vertexes = controller_->GetVertex(filename_str) / 3;
    int i_indexes = controller_->GetFacet(filename_str) / 2;

    controller_->StartFacade(filename_str, &ui->widget->vertexes,
                             &ui->widget->indexes, &ui->widget->ver_cub,
                             &ui->widget->ver_indexes);

    ui->win_Vertex->setText(QString::number(i_vertexes));
    ui->win_Facet->setText(QString::number(i_indexes));
    if (ui->widget->DrawFlag == 0) {
      ui->Slider_Color_R->setValue(100);
      ui->Point_Color_G->setValue(100);
      ui->Background_B->setValue(50);
      ui->Point_Box->setCurrentIndex(1);
      ui->dial_Point_Width->setValue(5);
      ui->dial_Line_Width->setValue(1);
      on_Draw_clicked();
      ui->widget->DrawFlag = 1;
    }
  }
}

void MainWindow::on_Draw_clicked() {
  if (ui->FilePath->text().size() == 0) {
    ui->Error_message->setText("No file chosen");
  } else {
    ui->widget->DrawFlag = 1;
    ui->widget->update();
  }
}

void MainWindow::on_ROTATE_clicked() {
  if (filename.isEmpty()) {
    ui->Error_message->setText("No file chosen");
  } else {
    bool res_x = false;
    bool res_y = false;
    bool res_z = false;
    QString ANGLE_X = ui->Angle_X->toPlainText();
    double ANGLE_X_A = ANGLE_X.toDouble(&res_x);
    QString ANGLE_Y = ui->Angle_Y->toPlainText();
    double ANGLE_Y_A = ANGLE_Y.toDouble(&res_y);
    QString ANGLE_Z = ui->Angle_Z->toPlainText();
    double ANGLE_Z_A = ANGLE_Z.toDouble(&res_z);

    if (res_x && res_y && res_z) {
      ui->Error_message->clear();
      double turn[3] = {ANGLE_X_A, ANGLE_Y_A, ANGLE_Z_A};

      AffineTransformStrategy *strategy = new AffineRotateStrategy();
      controller_->ContSetStrategy(strategy);
      controller_->ContApplyTransformation(ui->widget->vertexes,
                                           &ui->widget->ver_cub, turn);

      delete strategy;

      ui->widget->update();
    } else {
      ui->Angle_X->setText("0");
      ui->Angle_Y->setText("0");
      ui->Angle_Z->setText("0");
      ui->Error_message->setText("Incorrect Input");
    }
  }
}

void MainWindow::on_MOVE_clicked() {
  if (filename.isEmpty()) {
    ui->Error_message->setText("No file chosen");
  } else {
    bool res_x = false;
    bool res_y = false;
    bool res_z = false;
    QString MOVE_X = ui->Move_X->toPlainText();
    double MOVE_X_A = MOVE_X.toDouble(&res_x);
    QString MOVE_Y = ui->Move_Y->toPlainText();
    double MOVE_Y_A = MOVE_Y.toDouble(&res_y);
    QString MOVE_Z = ui->Move_Z->toPlainText();
    double MOVE_Z_A = MOVE_Z.toDouble(&res_z);

    if (res_x && res_y && res_z) {
      ui->Error_message->clear();
      double turn[3] = {MOVE_X_A, MOVE_Y_A, MOVE_Z_A};

      AffineTransformStrategy *strategy = new AffineShiftStrategy();

      controller_->ContSetStrategy(strategy);
      controller_->ContApplyTransformation(ui->widget->vertexes,
                                           &ui->widget->ver_cub, turn);

      delete strategy;
      ui->widget->update();
    } else {
      ui->Move_X->setText("0");
      ui->Move_Y->setText("0");
      ui->Move_Z->setText("0");
      ui->Error_message->setText("Incorrect Input");
    }
  }
}

void MainWindow::on_sliderScale_valueChanged(int value) {
  ui->scale_win->setText(QString::number(value));
  ui->widget->update();
}

void MainWindow::on_RESIZE_clicked() {
  if (filename.isEmpty()) {
    ui->Error_message->setText("No file chosen");
  } else {
    bool res = false;
    QString str_scale_win = ui->scale_win->text();
    double d_scale_win = str_scale_win.toDouble(&res);
    if (res == true) {
      ui->Error_message->clear();
      AffineTransformStrategy *strategy = new AffineSizeStrategy();

      controller_->ContSetStrategy(strategy);
      controller_->ContApplyTransformation(ui->widget->vertexes,
                                           &ui->widget->ver_cub, &d_scale_win);
      delete strategy;

      ui->widget->update();
    } else {
      ui->scale_win->clear();
      ui->Error_message->setText("Incorrect Input");
    }
  }
}

void MainWindow::on_Slider_Color_R_valueChanged(int value) {
  ui->widget->line_color_r_ = value;
  ui->widget->update();
}

void MainWindow::on_Slider_Color_G_valueChanged(int value) {
  ui->widget->line_color_g_ = value;
  ui->widget->update();
}

void MainWindow::on_Slider_Color_B_valueChanged(int value) {
  ui->widget->line_color_b_ = value;
  ui->widget->update();
}

void MainWindow::on_Background_R_valueChanged(int value) {
  ui->widget->backgroud_color_r_ = value;
  ui->widget->update();
}

void MainWindow::on_Background_G_valueChanged(int value) {
  ui->widget->backgroud_color_g_ = value;
  ui->widget->update();
}

void MainWindow::on_Background_B_valueChanged(int value) {
  ui->widget->backgroud_color_b_ = value;
  ui->widget->update();
}

void MainWindow::on_Point_Color_R_valueChanged(int value) {
  ui->widget->point_color_r_ = value;
  ui->widget->update();
}

void MainWindow::on_Point_Color_G_valueChanged(int value) {
  ui->widget->point_color_g_ = value;
  ui->widget->update();
}

void MainWindow::on_Point_Color_B_valueChanged(int value) {
  ui->widget->point_color_b_ = value;
  ui->widget->update();
}

void MainWindow::on_dial_Line_Width_valueChanged(int value) {
  ui->widget->line_width_ = value;
  ui->widget->update();
}

void MainWindow::on_Line_Box_activated(int index) {
  ui->widget->line_box_ = index;
  ui->widget->update();
}

void MainWindow::on_dial_Point_Width_valueChanged(int value) {
  ui->widget->point_width_ = value;
  ui->widget->update();
}

void MainWindow::on_Point_Box_currentIndexChanged(int index) {
  ui->widget->point_box_ = index;
  ui->widget->update();
}

void MainWindow::on_OFF_clicked() { QApplication::quit(); }

void MainWindow::on_SAVE_clicked() {
  QString SavePath = NULL;
  SavePath = QFileDialog::getSaveFileName(this, NULL, NULL,
                                          "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!SavePath.isNull())
    ui->widget->grabFramebuffer().save(SavePath, NULL, 100);
}

void MainWindow::on_SAVE_settings_clicked() {
  s21::ColorSettings current_color_setting;

  QString settings_path = QDir::homePath();

  current_color_setting.background_color_r = ui->Background_R->value();
  current_color_setting.background_color_g = ui->Background_G->value();
  current_color_setting.background_color_b = ui->Background_B->value();
  current_color_setting.line_color_r = ui->Slider_Color_R->value();
  current_color_setting.line_color_g = ui->Slider_Color_G->value();
  current_color_setting.line_color_b = ui->Slider_Color_B->value();
  current_color_setting.point_color_r = ui->Point_Color_R->value();
  current_color_setting.point_color_g = ui->Point_Color_G->value();
  current_color_setting.point_color_b = ui->Point_Color_B->value();
  current_color_setting.line_form = ui->Line_Box->currentIndex();
  current_color_setting.point_form = ui->Point_Box->currentIndex();
  current_color_setting.line_width = ui->dial_Line_Width->value();
  current_color_setting.point_width = ui->dial_Point_Width->value();
  current_color_setting.projection_type = ui->widget->projection_type;

  controller_->SaveColorSettings(current_color_setting,
                                 settings_path.toStdString());

  settings = new QSettings("settings.ini", QSettings::IniFormat, this);

  settings->setValue(
      "save_rotate_X",
      ui->Angle_X->toPlainText());  // save text from the window for rotate
  settings->setValue("save_rotate_Y", ui->Angle_Y->toPlainText());
  settings->setValue("save_rotate_Z", ui->Angle_Z->toPlainText());

  settings->setValue(
      "save_move_X",
      ui->Move_X->toPlainText());  // save text from the window for move
  settings->setValue("save_move_Y", ui->Move_Y->toPlainText());
  settings->setValue("save_move_Z", ui->Move_Z->toPlainText());

  settings->setValue("save_slider_scale",
                     ui->sliderScale->value());  // save scale

  settings->setValue("save_random_move_checked", ui->Random_Move->isChecked());
  settings->setValue("save_scale_win", ui->scale_win->text());

  settings->setValue("save_FilePath", ui->FilePath->text());  // save file path
}

void MainWindow::on_Load_settings_clicked() {
  s21::ColorSettings loading_color_setting;

  QString settings_path = QDir::homePath();
  loading_color_setting =
      controller_->LoadColorSettings(settings_path.toStdString());

  ui->Background_R->setValue(loading_color_setting.background_color_r);
  ui->Background_G->setValue(loading_color_setting.background_color_g);
  ui->Background_B->setValue(loading_color_setting.background_color_b);

  ui->Point_Color_R->setValue(loading_color_setting.point_color_r);
  ui->Point_Color_G->setValue(loading_color_setting.point_color_g);
  ui->Point_Color_B->setValue(loading_color_setting.point_color_b);

  ui->Slider_Color_R->setValue(loading_color_setting.line_color_r);
  ui->Slider_Color_G->setValue(loading_color_setting.line_color_g);
  ui->Slider_Color_B->setValue(loading_color_setting.line_color_b);

  ui->Line_Box->setCurrentIndex(loading_color_setting.line_form);
  ui->Point_Box->setCurrentIndex(loading_color_setting.point_form);

  ui->dial_Line_Width->setValue(loading_color_setting.line_width);
  ui->dial_Point_Width->setValue(loading_color_setting.point_width);

  if (loading_color_setting.projection_type == 1) {
    ui->Ortho->setChecked(true);
  } else {
    ui->Perspective->setChecked(true);
  }

  ui->widget->update();
  settings = new QSettings("settings.ini", QSettings::IniFormat, this);

  ui->Angle_X->setText(
      settings->value("save_rotate_X").toString());  // load text for rotate
  ui->Angle_Y->setText(settings->value("save_rotate_Y").toString());
  ui->Angle_Z->setText(settings->value("save_rotate_Z").toString());

  ui->Move_X->setText(
      settings->value("save_move_X").toString());  // load text for move
  ui->Move_Y->setText(settings->value("save_move_Y").toString());
  ui->Move_Z->setText(settings->value("save_move_Z").toString());

  ui->sliderScale->setValue(
      settings->value("save_slider_scale").toInt());  // load scale
  ui->widget->update();
}

void SetPixel(int xx, int yy, uint8_t red, uint8_t grn, uint8_t blu) {
  int width = 640;
  int height = 480;
  uint8_t image[width * height * 4];

  uint8_t *pixel = &image[(yy * width + xx) * 4];
  pixel[0] = red;
  pixel[1] = blu;
  pixel[2] = grn;
  pixel[3] = 255;
}

void SetPixelFloat(int xx, int yy, float fred, float fgrn, float fblu) {
  int width = 640;
  int height = 480;
  uint8_t image[width * height * 4];
  uint8_t red = (uint8_t)roundf(255.0f * fred);
  uint8_t grn = (uint8_t)roundf(255.0f * fgrn);
  uint8_t blu = (uint8_t)roundf(255.0f * fblu);

  SetPixel(xx, yy, red, grn, blu);
}

void MainWindow::on_GIF_clicked() {
  connect(timer, SIGNAL(timeout()), this, SLOT(AddFrameWhenTimeout()));
  timer->start(100);
  counter = 0;
}

void MainWindow::AddFrameWhenTimeout() {
  if (counter <= 50) {
    gif.push_back(ui->widget->grabFramebuffer());

    counter++;
  } else {
    timer->stop();
  }
}

void MainWindow::save_gif() {
  QString filename = NULL;
  filename = QFileDialog::getSaveFileName(this, NULL, GIF_PATH, "GIF (*.gif) ");
  if (!filename.isNull()) {
    QGifImage gif_file(
        QSize(ui->widget->width() * 2, ui->widget->height() * 2));
    gif_file.setDefaultDelay(100);
    for (QVector<QImage>::Iterator frames = gif.begin(); frames != gif.end();
         frames++) {
      gif_file.addFrame(*frames);
    }
    gif_file.save(filename);
  }
  gif.clear();
  counter = 0;
}

void MainWindow::on_GIF_2_clicked() { save_gif(); }

void MainWindow::on_Random_Move_clicked(bool checked) {
  ui->Random_Move->show();
  if (checked == true) {
    ui->widget->random_move_ = true;
  } else {
    ui->widget->random_move_ = false;
  }
}

void MainWindow::set_projection() {
  if (ui->Perspective->isChecked()) {
    ui->widget->projection_type = 1;
  } else if (ui->Ortho->isChecked()) {
    ui->widget->projection_type = 0;
  }
  ui->widget->update();
}

void MainWindow::on_random_Hide_clicked() {
  ui->Random_Move->show();
  ui->random_Hide->hide();
  ui->Perspective->setChecked(true);
}

void MainWindow::on_random_Show_clicked() {
  ui->Random_Move->hide();
  ui->random_Hide->show();
}

};  // namespace s21