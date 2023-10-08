/// \file
#include "controller.h"

void s21::Controller::StartFacade(const char *NameOfFile, int *v_num,
                                  int *f_num, double **vert, int **facets) {
  model_.GetPointerFacade()->ParseFile(NameOfFile, v_num, f_num, vert, facets);
}

int s21::Controller::GetVertex(const char *NameOfFile) {
  return this->model_.GetPointerFacade()->GetVertex(NameOfFile);
}

int s21::Controller::GetFacet(const char *NameOfFile) {
  return this->model_.GetPointerFacade()->GetFacet(NameOfFile);
}

void s21::Controller::SaveColorSettings(
    const s21::ColorSettings &current_color_settings,
    std::string settings_path) {
  s21::SettingsOriginator current_originator;
  current_originator.set_color_settings(current_color_settings);
  current_originator.save_color_settings(settings_path);
}

const s21::ColorSettings s21::Controller::LoadColorSettings(
    std::string settings_path) {
  s21::SettingsOriginator current_originator;
  return current_originator.RestoreColorSettings(settings_path);
}

void s21::Controller::ContSetStrategy(AffineTransformStrategy *newStrategy) {
  model_.context->setStrategy(newStrategy);
}

void s21::Controller::ContApplyTransformation(int l, double **v,
                                              double *parameters) {
  model_.context->applyTransformation(l, v, parameters);
}
