/// \file
#ifndef CPP4_3DVIEWER_V2_MODEL_FACADE_H_
#define CPP4_3DVIEWER_V2_MODEL_FACADE_H_

#include <math.h>

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @file facade.h
 * @author sparrvio
 * @brief В файле facade.cc facade.h реализован паттерн facade and singleton.
 * Данный паттерн использован для реализации парсера файлов для отрисовки 3D
 * изображений.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */

namespace s21 {
/**
 * @brief Класс ICounter Виртуальный класс для реализации шаблона Фасад
 */
class ICounter {
 public:
  virtual int Сalculate(const char *NameOfFile) = 0;
};

/**
 * @brief Класс CounterVertex считаем ребра
 */
class CounterVertex : public ICounter {
 public:
  int Сalculate(const char *NameOfFile) override;

 private:
  int CountVertex(const char *NameOfFile);
  int vertex_;
};

/**
 * @brief Класс CounterFacet считаем вершины
 */
class CounterFacet : public ICounter {
 public:
  int Сalculate(const char *NameOfFile) override;

 private:
  int CountFacet(const char *NameOfFile);
  int facet_;
};

/**
 * @brief Класс Facade реализация шаблона Фасад
 */
class Facade {
 public:
  static Facade *GetInstance() {
    static s21::Facade *p_instance;
    if (!p_instance) {
      p_instance = new Facade();
    }
    return p_instance;
  }
  ~Facade() { delete p_instance; }

  int GetVertex(const char *NameOfFile);
  int GetFacet(const char *NameOfFile);
  void ParseFile(const char *NameOfFile, int *v_num, int *f_num, double **vert,
                 int **facets);

 private:
  Facade(){};
  static Facade *p_instance;
  Facade(const Facade &) = delete;
  Facade &operator=(const Facade &) = delete;

  void GetDot(double **vertex_arr, char *temp, int *i, double *big_vert);
  void Center(double big_vert, double **vertex_arr, int len);
  void Parser(const char *NameOfFile, double **vertex_arr, int V_field_number,
              int **facet_arr, int F_field_number);
  void GetFacet(char *str, int **facets, int *i, int count_dot);
  void DelSpace(const char *NameOfFile);

  int vertex_;
  int facet_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_FACADE_H_