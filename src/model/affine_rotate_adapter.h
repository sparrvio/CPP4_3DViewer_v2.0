/// \file
#ifndef CPP4_3DVIEWER_V2_MODEL_AFFINE_ROTATE_ADAPTER_H_
#define CPP4_3DVIEWER_V2_MODEL_AFFINE_ROTATE_ADAPTER_H_

#include <cmath>

/**
 * @file affine_rotate_adapter.h
 * @author elmersha
 * @brief В файле affine_rotate_adapter.cc affine_rotate_adapter.h реализован
 * паттерн adapter. Используя данный паттерн мы конвертируем входящие в радианах
 * данные конвертировать в градусы для вычислений угла поворота.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
namespace s21 {
/**
 * @brief  класс-адаптер для преобразования радиан в градусы.
 */
class AffineRotate {
 public:
  /**
   * @brief Применяет аффинное преобразование.
   *
   * @param l Размерность вектора.
   * @param v Указатель на массив векторов.
   * @param rotate Параметр изменения угла вращения.
   */
  void Rotate(int l, double **v, double *rotate);
  // private:
};
/**
 * @brief Абстрактный класс для класса-адаптера.
 */
class RadianToDegree {
 public:
  /**
   * @brief Виртуальный деструктор для класса-адаптера.
   */
  virtual ~RadianToDegree() {}
  virtual void Rotate(int l, double **v, double *rotate) = 0;
};
/**
 * @brief Виртуальный класс-адаптер, наследующий от абстракного.
 */
class Adapter : public RadianToDegree {
 public:
  /**
   * @brief конструктор для передачи в приватное поле-указатель на объект класса
   * AffineRotate.
   */
  Adapter(AffineRotate *adaptee) : adaptee_RadianToDegree_(adaptee) {}
  ~Adapter() { delete adaptee_RadianToDegree_; }
  /**
   * @brief Функция которая переводит из радиан в градусы.
   */
  void Rotate(int l, double **v, double *rotate);

 private:
  AffineRotate *adaptee_RadianToDegree_;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_MODEL_AFFINE_ROTATE_ADAPTER_H_
