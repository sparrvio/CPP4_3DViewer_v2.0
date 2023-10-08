/// \file
#ifndef CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H_

#include "../model/affine_transformations_strategy.h"
#include "../model/facade.h"
#include "../model/model.h"

/**
 * @file controller.h
 * @author
 * @brief В файле controller.cc controller.h  реализован контроллер паттерна
 * MVC. Контроллер - тонкий макрокомпонент, который осуществляет модификацию
 * модели. Через него формируются запросы на изменение модели. Тонким он
 * называется потому, что идеальный контроллер не содержит в себе никакой
 * дополнительной логики, кроме вызова одного или нескольких методов модели.
 * Контроллер выполняет функцию связующего элемента между интерфейсом и моделью.
 *  а.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */

namespace s21 {
/**
 * @brief Класс Controller паттерна MVC
 */
class Controller {
 public:
  Controller() {
    model_.context = new AffineTransformContext;
    model_.color_control = new s21::ColorSettings;
  }
  ~Controller() {
    delete model_.context;
    delete model_.color_control;
  }
  void StartFacade(const char *NameOfFile, int *v_num, int *f_num,
                   double **vert, int **facets);
  int GetVertex(const char *NameOfFile);
  int GetFacet(const char *NameOfFile);
  void SaveColorSettings(const s21::ColorSettings &current_color_settings,
                         std::string settings_path);
  const s21::ColorSettings LoadColorSettings(std::string settings_path);
  void ContSetStrategy(AffineTransformStrategy *newStrategy);
  void ContApplyTransformation(int l, double **v, double *parameters);

 private:
  Model model_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H_
