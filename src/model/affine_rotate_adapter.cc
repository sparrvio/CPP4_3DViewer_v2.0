/// \file
#include "affine_rotate_adapter.h"

namespace s21 {
void AffineRotate::Rotate(int l, double **v, double *rotate) {
  if (l % 3 == 0) {
    double v_temp[3];
    for (int i = 0; i < l; i += 3) {
      for (int j = 0; j < 3; j++) v_temp[j] = (*v)[i + j];
      (*v)[i + 1] = v_temp[1] * cos(rotate[0]) - v_temp[2] * sin(rotate[0]);
      (*v)[i + 2] = v_temp[1] * sin(rotate[0]) + v_temp[2] * cos(rotate[0]);
      for (int j = 0; j < 3; j++) v_temp[j] = (*v)[i + j];
      (*v)[i] = v_temp[0] * cos(rotate[1]) + v_temp[2] * sin(rotate[1]);
      (*v)[i + 2] = -v_temp[0] * sin(rotate[1]) + v_temp[2] * cos(rotate[1]);
      for (int j = 0; j < 3; j++) v_temp[j] = (*v)[i + j];
      (*v)[i] = v_temp[0] * cos(rotate[2]) - v_temp[1] * sin(rotate[2]);
      (*v)[i + 1] = v_temp[0] * sin(rotate[2]) + v_temp[1] * cos(rotate[2]);
    }
  }
}

void Adapter::Rotate(int l, double **v, double *rotate) {
  for (int i = 0; i < 3; i++) rotate[i] = rotate[i] * M_PI / 180;
  adaptee_RadianToDegree_->Rotate(l, v, rotate);
}
}  // namespace s21
