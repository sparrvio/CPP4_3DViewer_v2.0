/// \file
#include "model.h"

namespace s21 {

Model::Model() {
  facade_ = Facade::GetInstance();
  context_ = context;
  color_control_ = color_control;
}

Facade* Model::GetPointerFacade() { return facade_; }

}  // namespace s21
