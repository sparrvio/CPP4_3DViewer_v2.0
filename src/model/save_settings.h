/// \file
#ifndef CPP4_3DVIEWER_V2_MODEL_SAVE_SETTINGS_H_
#define CPP4_3DVIEWER_V2_MODEL_SAVE_SETTINGS_H_

/**
 * @file save_settings.h
 * @author qylenett
 * @brief В файлах save_settings.cc save_settings.h реализован паттерн
 * momento(снимок). Используя данный паттерно мы позволяем пользователю
 * сохранять настройки между выключениями программы. Паттерн состоит из трех
 * классов, а именно, класс SettingsOriginator создающий объект паттерна снимок,
 * при необходимости, класс Momento - класс который хранит объект с текущими
 * настройками и класс SettingsCaretaker - класс который сохраняет данные класса
 * Momento в текстовый файл. В файлк так же присутствует структура
 * ColorSettings. Данная структура необходима для передачи параметров из части
 * пользовательского интерфейса в часть с реализачией модели через контроллер.
 * @version 0.1
 * @date 2023-09-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

namespace s21 {

/**
 * @brief Структура ColorSettings, находящаяся в пространстве имен S21 служит
 * для передачи параметров настроек из части view в часть model через
 * controller. Имеет в себе два конструктора. Конструктор по умолчанию, создает
 * модель с нулевыми параметрами и конструктор с параметрами.
 */
struct ColorSettings {
  int background_color_r;
  int background_color_g;
  int background_color_b;

  int line_color_r;
  int line_color_g;
  int line_color_b;

  int point_color_r;
  int point_color_g;
  int point_color_b;

  int line_form;
  int point_form;

  int line_width;
  int point_width;

  int projection_type;

  ColorSettings() {
    this->background_color_r = 0;
    this->background_color_g = 0;
    this->background_color_b = 0;
    this->line_color_r = 0;
    this->line_color_g = 0;
    this->line_color_b = 0;
    this->point_color_r = 0;
    this->point_color_g = 0;
    this->point_color_b = 0;
    this->line_form = 0;
    this->point_form = 0;
    this->line_width = 0;
    this->point_width = 0;
    this->projection_type = 0;
  }

  ColorSettings(int back_r, int back_g, int back_b, int line_r, int line_g,
                int line_b, int point_r, int point_g, int point_b, int l_form,
                int p_form, int l_width, int p_width, int p_type)
      : background_color_r(back_r),
        background_color_g(back_g),
        background_color_b(back_b),
        line_color_r(line_r),
        line_color_g(line_g),
        line_color_b(line_b),
        point_color_r(point_r),
        point_color_g(point_g),
        point_color_b(point_b),
        line_form(l_form),
        point_form(p_form),
        line_width(l_width),
        point_width(p_width),
        projection_type(p_type) {}
};
}  // namespace s21

/**
 * @brief Класс SettingsOriginator необходим для создания объекта класса momento
 */
namespace s21 {
class SettingsOriginator {
 public:
  /**
   * @brief Устанавливает пришедшие извне настройки цвета в объект-член данных
   * класса current_
   */
  void set_color_settings(const s21::ColorSettings& current_color_settings);
  /**
   * @brief Геттер для получения значений приватного поля current_
   */
  const s21::ColorSettings& get_color_settings()
      const;  // отдает настройки цвета
  /**
   * @brief Создает объект класса momento
   */
  void save_color_settings(std::string settings_path);
  /**
   * @brief Возвращает данные настроек из файла созданного мептодами класса
   * SettingsCaretaker
   */
  s21::ColorSettings RestoreColorSettings(std::string settings_path);

 private:
  ColorSettings current_;
};
}  // namespace s21

/**
 * @brief ColorSettinsMomento - класс momento, создающий объек хранящий текущие
 * настройки
 */
namespace s21 {
class ColorSettinsMomento {
 public:
  ColorSettinsMomento(const s21::ColorSettings& current_color_settings)
      : momento_color_settings_(current_color_settings) {}
  /**
   * @brief Геттер для получения текущего состояния приватного поля
   * momento_color_settings_
   */
  const s21::ColorSettings& get_color_settings() const;

 private:
  s21::ColorSettings momento_color_settings_;
};

}  // namespace s21

/**
 * @brief Класс SettingsCaretaker производит сохранение данных объекта класса
 * ColorSettinsMomento в текстовый файл и получение данных из текстового файла.
 */
namespace s21 {
class SettingsCaretaker {
 public:
  /**
   * @brief Метод добавления данных ColorSettinsMomento в текстовый файл.
   */
  void AddSettingsToFile(const ColorSettinsMomento current_momento,
                         std::string settings_path);
  /**
   * @brief Метод получения данных ColorSettinsMomento из текстового файла.
   */
  s21::ColorSettings GetSettingsFromFile(std::string settings_path);
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_SAVE_SETTINGS_H_
