/// \file
#ifndef CPP4_3DVIEWER_V2_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_MODEL_MODEL_H_

#include "affine_transformations_strategy.h"
#include "facade.h"
#include "save_settings.h"

/**
 * @file model.h
 * @author
 * @brief Файл model.cc model.h является обобщенным модулем методов и классов,
 * реализованных как часть паттерна MVC приложения 3DViewer v2.0
 *
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */

namespace s21 {
/**
 * @brief Класс Model для реализация паттерна MVC
 */
class Model {
 public:
  Model();
  Facade *GetPointerFacade();
  AffineTransformContext *context;
  ColorSettings *color_control;

 private:
  Facade *facade_;
  AffineTransformContext *context_;
  ColorSettings *color_control_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_MODEL_H_
