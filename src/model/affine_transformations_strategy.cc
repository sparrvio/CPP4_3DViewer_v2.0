/// \file
#include "affine_transformations_strategy.h"

namespace s21 {
void AffineShiftStrategy::apply(int l, double** v, double* shift) {
  if (l % 3 == 0) {
    for (int i = 0; i < l; i++) {
      (*v)[i] = (*v)[i] + shift[i % 3];
    }
  }
}

void AffineSizeStrategy::apply(int l, double** v, double* size) {
  if (*size > 0.0) {
    for (int i = 0; i < l; i++) {
      (*v)[i] = (*v)[i] * (*size) / 100;
    }
  }
}

void AffineRotateStrategy::apply(int l, double** v, double* rotate) {
  RadianToDegree* rotate_axis = new Adapter(new AffineRotate);
  rotate_axis->Rotate(l, v, rotate);
  delete rotate_axis;
}

void AffineTransformContext::setStrategy(AffineTransformStrategy* newStrategy) {
  strategy_ = newStrategy;
}

void AffineTransformContext::applyTransformation(int l, double** v,
                                                 double* parameters) {
  if (strategy_) {
    strategy_->apply(l, v, parameters);
  }
}
}  // namespace s21