/// \file
#ifndef CPP4_3DVIEWER_V2_MODEL_AFFINE_TRANSFORMATIONS_STRATEGY_H_
#define CPP4_3DVIEWER_V2_MODEL_AFFINE_TRANSFORMATIONS_STRATEGY_H_

#include <cmath>

#include "affine_rotate_adapter.h"

/**
 * @file affine_transformations_strategy.h
 * @author morfinpo
 * @brief В файле affine_transformations_strategy.cc
 * affine_transformations_strategy.h реализован паттерн strategy. Данный паттерн
 * реализует базовый класс для стратегий аффинных преобразований .
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
namespace s21 {
/**
 * @brief Базовый класс для стратегий аффинных преобразований.
 */
class AffineTransformStrategy {
 public:
  /**
   * @brief Применяет аффинное преобразование.
   *
   * @param l Размерность вектора.
   * @param v Указатель на массив векторов.
   * @param parameters Параметры преобразования.
   */
  virtual void apply(int l, double** v, double* parameters) = 0;

  /**
   * @brief Виртуальный деструктор для базового класса.
   */
  virtual ~AffineTransformStrategy() {}
};

/**
 * @brief Класс стратегии аффинного сдвига.
 */
class AffineShiftStrategy : public AffineTransformStrategy {
 public:
  void apply(int l, double** v, double* shift);
};

/**
 * @brief Класс стратегии аффинного изменения размера.
 */
class AffineSizeStrategy : public AffineTransformStrategy {
 public:
  void apply(int l, double** v, double* size);
};

/**
 * @brief Класс стратегии аффинного вращения.
 */
class AffineRotateStrategy : public AffineTransformStrategy {
 public:
  void apply(int l, double** v, double* rotate);
};

/**
 * @brief Класс контекста для аффинных преобразований.
 */
class AffineTransformContext {
 private:
  AffineTransformStrategy* strategy_; /**< Указатель на текущую стратегию. */

 public:
  /**
   * @brief Устанавливает стратегию для аффинного преобразования.
   *
   * @param newStrategy Указатель на новую стратегию.
   */
  void setStrategy(AffineTransformStrategy* newStrategy);

  /**
   * @brief Применяет выбранное аффинное преобразование.
   */
  void applyTransformation(int l, double** v, double* parameters);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_AFFINE_TRANSFORMATIONS_STRATEGY_H_
