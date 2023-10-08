/// \file
#include "save_settings.h"

const s21::ColorSettings& s21::ColorSettinsMomento::get_color_settings() const {
  return momento_color_settings_;
}

void s21::SettingsOriginator::set_color_settings(
    const s21::ColorSettings& current_color_settings) {
  current_.background_color_r = current_color_settings.background_color_r;
  current_.background_color_g = current_color_settings.background_color_g;
  current_.background_color_b = current_color_settings.background_color_b;

  current_.line_color_r = current_color_settings.line_color_r;
  current_.line_color_g = current_color_settings.line_color_g;
  current_.line_color_b = current_color_settings.line_color_b;

  current_.point_color_r = current_color_settings.point_color_r;
  current_.point_color_g = current_color_settings.point_color_g;
  current_.point_color_b = current_color_settings.point_color_b;

  current_.line_form = current_color_settings.line_form;
  current_.point_form = current_color_settings.point_form;

  current_.line_width = current_color_settings.line_width;
  current_.point_width = current_color_settings.point_width;

  current_.projection_type = current_color_settings.projection_type;
}

const s21::ColorSettings& s21::SettingsOriginator::get_color_settings() const {
  return current_;
}

void s21::SettingsOriginator::save_color_settings(std::string settings_path) {
  ColorSettinsMomento current_momento(current_);
  SettingsCaretaker caretaker;
  caretaker.AddSettingsToFile(current_momento, settings_path);
}

s21::ColorSettings s21::SettingsOriginator::RestoreColorSettings(
    std::string settings_path) {
  s21::SettingsCaretaker care;
  return care.GetSettingsFromFile(settings_path);
}

void s21::SettingsCaretaker::AddSettingsToFile(
    const ColorSettinsMomento current_momento, std::string settings_path) {
  std::ofstream file;

  std::string current_settings_path = settings_path + "/colorsettings.txt";
  file.open(current_settings_path);
  if (file.is_open()) {
    file << current_momento.get_color_settings().background_color_r
         << std::endl;
    file << current_momento.get_color_settings().background_color_g
         << std::endl;
    file << current_momento.get_color_settings().background_color_b
         << std::endl;

    file << current_momento.get_color_settings().line_color_r << std::endl;
    file << current_momento.get_color_settings().line_color_g << std::endl;
    file << current_momento.get_color_settings().line_color_b << std::endl;

    file << current_momento.get_color_settings().point_color_r << std::endl;
    file << current_momento.get_color_settings().point_color_g << std::endl;
    file << current_momento.get_color_settings().point_color_b << std::endl;

    file << current_momento.get_color_settings().line_form << std::endl;
    file << current_momento.get_color_settings().point_form << std::endl;

    file << current_momento.get_color_settings().line_width << std::endl;
    file << current_momento.get_color_settings().point_width << std::endl;

    file << current_momento.get_color_settings().projection_type << std::endl;

    file.close();
  }
}

s21::ColorSettings s21::SettingsCaretaker::GetSettingsFromFile(
    std::string settings_path) {
  s21::ColorSettings cur_momento;
  std::ifstream file;
  std::string current_settings_path = settings_path + "/colorsettings.txt";
  file.open(current_settings_path);
  file >> cur_momento.background_color_r;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.background_color_g;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.background_color_b;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  file >> cur_momento.line_color_r;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.line_color_g;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.line_color_b;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  file >> cur_momento.point_color_r;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.point_color_g;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.point_color_b;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  file >> cur_momento.line_form;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.point_form;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  file >> cur_momento.line_width;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  file >> cur_momento.point_width;
  file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  file >> cur_momento.projection_type;

  file.close();

  return cur_momento;
}