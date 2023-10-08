#include <gtest/gtest.h>

#include <cmath>

#include "../controller/controller.h"
#include "../model/affine_rotate_adapter.h"
#include "../model/affine_transformations_strategy.h"
#include "../model/facade.h"
#include "../model/model.h"
#include "../model/save_settings.h"

namespace s21 {

const double EPSILON = 1e-6;

s21::Controller controller;

TEST(getvertex, test001) {
  const char* NameOfFile = "cube.obj";
  int f_num = controller.GetVertex(NameOfFile);
  EXPECT_EQ(f_num, 24);
}

TEST(getvertex, testtest2) {
  s21::Controller controller;
  const char* NameOfFile = "cube.obj";
  int f_num = controller.GetFacet(NameOfFile);
  EXPECT_EQ(f_num, 24);
}

TEST(FacadeTest, Test) {
  s21::Model model;
  const char* NameOfFile = "cube.obj";

  int vert = controller.GetVertex(NameOfFile);
  int facets = controller.GetFacet(NameOfFile);
  double* vertex_arr = NULL;
  int* facet_arr = NULL;
  model.GetPointerFacade()->ParseFile(NameOfFile, &vert, &facets, &vertex_arr,
                                      &facet_arr);
  double* vert_reference;
  vert_reference = (double*)calloc(24, sizeof(double));
  vert_reference[0] = -1.0;
  vert_reference[1] = -1.0;
  vert_reference[2] = -1.0;
  vert_reference[3] = -1.0;
  vert_reference[4] = -1.0;
  vert_reference[5] = 1.0;
  vert_reference[6] = -1.0;
  vert_reference[7] = 1.0;
  vert_reference[8] = -1.0;
  vert_reference[9] = -1.0;
  vert_reference[10] = 1.0;
  vert_reference[11] = 1.0;
  vert_reference[12] = 1.0;
  vert_reference[13] = -1.0;
  vert_reference[14] = -1.0;
  vert_reference[15] = 1.0;
  vert_reference[16] = -1.0;
  vert_reference[17] = 1.0;
  vert_reference[18] = 1.0;
  vert_reference[19] = 1.0;
  vert_reference[20] = -1.0;
  vert_reference[21] = 1.0;
  vert_reference[22] = 1.0;
  vert_reference[23] = 1.0;

  double res_vert = 0.0;
  for (int i = 0; i < 24; i++) {
    res_vert += vertex_arr[i] - vert_reference[i];
  }
  int res_facests = 24;
  int facest_reference[] = {1, 5, 5, 6, 6, 2, 2, 1, 2, 4, 4, 3, 3, 1, 1, 2, 2,
                            6, 6, 8, 8, 4, 4, 2, 3, 7, 7, 5, 5, 1, 1, 3, 4, 8,
                            8, 7, 7, 3, 3, 4, 5, 7, 7, 8, 8, 6, 6, 5, 1};
  for (int i = 0; i < 24; i++) {
    res_facests += facet_arr[i] - facest_reference[i];
  }
  EXPECT_DOUBLE_EQ(res_facests, 0);
  free(vert_reference);
  EXPECT_NEAR(res_vert, 0.0, 1e-2);
  free(vertex_arr);
  free(facet_arr);
}

TEST(AffineShiftStrategyTest, Test0) {
  AffineTransformStrategy* strategy = new AffineShiftStrategy;
  controller.ContSetStrategy(strategy);

  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double shift[3] = {0.1, 0.2, 0.3};

  double* verticesPtr[6] = {&vertices[0], &vertices[1], &vertices[2],
                            &vertices[3], &vertices[4], &vertices[5]};
  controller.ContApplyTransformation(6, verticesPtr, shift);

  EXPECT_DOUBLE_EQ(vertices[0], 1.1);
  EXPECT_DOUBLE_EQ(vertices[1], 2.2);
  EXPECT_DOUBLE_EQ(vertices[2], 3.3);
  EXPECT_DOUBLE_EQ(vertices[3], 4.1);
  EXPECT_DOUBLE_EQ(vertices[4], 5.2);
  EXPECT_DOUBLE_EQ(vertices[5], 6.3);

  delete strategy;
}

TEST(AffineShiftStrategyTest, Test1) {
  AffineTransformStrategy* strategy = new AffineShiftStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {5.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double shift[3] = {0.1, 0.2, 3.0};

  double* verticesPtr[6] = {&vertices[0], &vertices[1], &vertices[2],
                            &vertices[3], &vertices[4], &vertices[5]};
  controller.ContApplyTransformation(6, verticesPtr, shift);

  EXPECT_DOUBLE_EQ(vertices[0], 5.1);
  EXPECT_DOUBLE_EQ(vertices[1], 2.2);
  EXPECT_DOUBLE_EQ(vertices[2], 6.0);
  EXPECT_DOUBLE_EQ(vertices[3], 4.1);
  EXPECT_DOUBLE_EQ(vertices[4], 5.2);
  EXPECT_DOUBLE_EQ(vertices[5], 9.0);

  delete strategy;
}

TEST(AffineShiftStrategyTest, Test2) {
  AffineTransformStrategy* strategy = new AffineShiftStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double shift[3] = {0.1, 0.2, 0.3};

  double* verticesPtr[6] = {&vertices[0], &vertices[1], &vertices[2],
                            &vertices[3], &vertices[4], &vertices[5]};

  controller.ContApplyTransformation(6, verticesPtr, shift);

  EXPECT_DOUBLE_EQ(vertices[0], 1.1);
  EXPECT_DOUBLE_EQ(vertices[1], 2.2);
  EXPECT_DOUBLE_EQ(vertices[2], 3.3);
  EXPECT_DOUBLE_EQ(vertices[3], 4.1);
  EXPECT_DOUBLE_EQ(vertices[4], 5.2);
  EXPECT_DOUBLE_EQ(vertices[5], 6.3);

  delete strategy;
}

TEST(AffineShiftStrategyTest, Test3) {
  AffineTransformStrategy* strategy = new AffineShiftStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double shift[3] = {0.0, 0.0, 0.0};

  double* verticesPtr[5] = {&vertices[0], &vertices[1], &vertices[2],
                            &vertices[3], &vertices[4]};

  controller.ContApplyTransformation(6, verticesPtr, shift);

  for (int i = 0; i < 6; i++) {
    EXPECT_DOUBLE_EQ(vertices[i], i + 1);
  }
  delete strategy;
}

TEST(AffineShiftStrategyTest, Test4) {
  AffineTransformStrategy* strategy = new AffineShiftStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double shift[3] = {-0.1, -0.2, -0.3};

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }
  controller.ContApplyTransformation(6, verticesPtr, shift);

  EXPECT_DOUBLE_EQ(vertices[0], 0.9);
  EXPECT_DOUBLE_EQ(vertices[1], 1.8);
  EXPECT_DOUBLE_EQ(vertices[2], 2.7);
  EXPECT_DOUBLE_EQ(vertices[3], 3.9);
  EXPECT_DOUBLE_EQ(vertices[4], 4.8);
  EXPECT_DOUBLE_EQ(vertices[5], 5.7);

  delete strategy;
}

TEST(AffineShiftStrategyTest, Test5) {
  AffineTransformStrategy* strategy = new AffineShiftStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double shift[3] = {0.1, -0.2, 0.3};

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }
  controller.ContApplyTransformation(6, verticesPtr, shift);

  EXPECT_DOUBLE_EQ(vertices[0], 1.1);
  EXPECT_DOUBLE_EQ(vertices[1], 1.8);
  EXPECT_DOUBLE_EQ(vertices[2], 3.3);
  EXPECT_DOUBLE_EQ(vertices[3], 4.1);
  EXPECT_DOUBLE_EQ(vertices[4], 4.8);
  EXPECT_DOUBLE_EQ(vertices[5], 6.3);

  delete strategy;
}

TEST(AffineSizeStrategyTest, Test55) {
  AffineTransformStrategy* strategy = new AffineSizeStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double size = -50.0;

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, &size);

  EXPECT_DOUBLE_EQ(vertices[0], 1);
  EXPECT_DOUBLE_EQ(vertices[1], 2);
  EXPECT_DOUBLE_EQ(vertices[2], 3);
  EXPECT_DOUBLE_EQ(vertices[3], 4);
  EXPECT_DOUBLE_EQ(vertices[4], 5);
  EXPECT_DOUBLE_EQ(vertices[5], 6);

  delete strategy;
}

TEST(AffineSizeStrategyTest, Test6) {
  AffineTransformStrategy* strategy = new AffineSizeStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double size = 50.0;

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, &size);

  EXPECT_DOUBLE_EQ(vertices[0], 0.5);
  EXPECT_DOUBLE_EQ(vertices[1], 1.0);
  EXPECT_DOUBLE_EQ(vertices[2], 1.5);
  EXPECT_DOUBLE_EQ(vertices[3], 2.0);
  EXPECT_DOUBLE_EQ(vertices[4], 2.5);
  EXPECT_DOUBLE_EQ(vertices[5], 3.0);

  delete strategy;
}

TEST(AffineSizeStrategyTest, Test7) {
  AffineTransformStrategy* strategy = new AffineSizeStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double size = -10.0;

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, &size);

  EXPECT_DOUBLE_EQ(vertices[0], 1.0);
  EXPECT_DOUBLE_EQ(vertices[1], 2.0);
  EXPECT_DOUBLE_EQ(vertices[2], 3.0);
  EXPECT_DOUBLE_EQ(vertices[3], 4.0);
  EXPECT_DOUBLE_EQ(vertices[4], 5.0);
  EXPECT_DOUBLE_EQ(vertices[5], 6.0);
  delete strategy;
}

TEST(AffineSizeStrategyTest, Test8) {
  AffineTransformStrategy* strategy = new AffineSizeStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
  double size = 0.001;

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, &size);

  EXPECT_DOUBLE_EQ(vertices[0], 0.00001);
  EXPECT_DOUBLE_EQ(vertices[1], 0.00002);
  EXPECT_DOUBLE_EQ(vertices[2], 0.00003);
  EXPECT_DOUBLE_EQ(vertices[3], 0.00004);
  EXPECT_DOUBLE_EQ(vertices[4], 0.00005);
  EXPECT_DOUBLE_EQ(vertices[5], 0.00006);
  delete strategy;
}

TEST(AffineRotateStrategyTest, Test9) {
  AffineTransformStrategy* strategy = new AffineRotateStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
  double rotation[3] = {90, 0.0, 0.0};

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, rotation);

  EXPECT_NEAR(vertices[0], 1.0, EPSILON);
  EXPECT_NEAR(vertices[1], 0.0, EPSILON);
  EXPECT_NEAR(vertices[2], 0.0, EPSILON);
  EXPECT_NEAR(vertices[3], 0.0, EPSILON);
  EXPECT_NEAR(vertices[4], 0.0, EPSILON);
  EXPECT_NEAR(vertices[5], 1.0, EPSILON);
  delete strategy;
}

TEST(AffineRotateStrategyTest, Test10) {
  AffineTransformStrategy* strategy = new AffineRotateStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
  double rotation[3] = {0.0, 90, 0.0};  // 90 degrees rotation around y-axis

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, rotation);

  EXPECT_NEAR(vertices[0], 0.0, EPSILON);
  EXPECT_NEAR(vertices[1], 0.0, EPSILON);
  EXPECT_NEAR(vertices[2], -1.0, EPSILON);
  EXPECT_NEAR(vertices[3], 0.0, EPSILON);
  EXPECT_NEAR(vertices[4], 1.0, EPSILON);
  EXPECT_NEAR(vertices[5], 0.0, EPSILON);
  delete strategy;
}

TEST(AffineRotateStrategyTest, Test11) {
  AffineTransformStrategy* strategy = new AffineRotateStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
  double rotation[3] = {0.0, 0.0, 90};

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, rotation);

  EXPECT_NEAR(vertices[0], 0.0, EPSILON);
  EXPECT_NEAR(vertices[1], 1.0, EPSILON);
  EXPECT_NEAR(vertices[2], 0.0, EPSILON);
  EXPECT_NEAR(vertices[3], -1.0, EPSILON);
  EXPECT_NEAR(vertices[4], 0.0, EPSILON);
  EXPECT_NEAR(vertices[5], 0.0, EPSILON);

  delete strategy;
}

TEST(AffineRotateStrategyTest, Test12) {
  AffineTransformStrategy* strategy = new AffineRotateStrategy;
  controller.ContSetStrategy(strategy);
  double vertices[6] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0};
  double rotation[3] = {90, 0.0, 0.0};

  double* verticesPtr[6];
  for (int i = 0; i < 6; i++) {
    verticesPtr[i] = &vertices[i];
  }

  controller.ContApplyTransformation(6, verticesPtr, rotation);

  EXPECT_NEAR(vertices[0], 1.0, EPSILON);
  EXPECT_NEAR(vertices[1], 0.0, EPSILON);
  EXPECT_NEAR(vertices[2], 0.0, EPSILON);
  EXPECT_NEAR(vertices[3], 0.0, EPSILON);
  EXPECT_NEAR(vertices[4], 0.0, EPSILON);
  EXPECT_NEAR(vertices[5], 1.0, EPSILON);

  delete strategy;
}

TEST(SaveSettingsTest, Test111) {
  int background_r = 100;
  int background_g = 10;
  int background_b = 20;
  int line_r = 0;
  int line_g = 80;
  int line_b = 15;
  int point_r = 100;
  int point_g = 10;
  int point_b = 0;
  int l_form = 1;
  int p_form = 1;
  int l_width = 10;
  int p_width = 5;
  int proj_type = 1;

  std::string test_path = "tests/";

  s21::ColorSettings test_color(
      background_r, background_g, background_b, line_r, line_g, line_b, point_r,
      point_g, point_b, l_form, p_form, l_width, p_width, proj_type);

  s21::ColorSettings test_object;

  controller.SaveColorSettings(test_color, test_path);

  s21::SettingsOriginator test_or;

  test_or.get_color_settings();

  EXPECT_NEAR(test_color.background_color_r, 100, EPSILON);
  EXPECT_NEAR(test_color.background_color_g, 10, EPSILON);
  EXPECT_NEAR(test_color.background_color_b, 20, EPSILON);

  EXPECT_NEAR(test_color.line_color_r, 0, EPSILON);
  EXPECT_NEAR(test_color.line_color_g, 80, EPSILON);
  EXPECT_NEAR(test_color.line_color_b, 15, EPSILON);

  EXPECT_NEAR(test_color.point_color_r, 100, EPSILON);
  EXPECT_NEAR(test_color.point_color_g, 10, EPSILON);
  EXPECT_NEAR(test_color.point_color_b, 0, EPSILON);

  EXPECT_NEAR(test_color.line_form, 1, EPSILON);
  EXPECT_NEAR(test_color.point_form, 1, EPSILON);

  EXPECT_NEAR(test_color.line_width, 10, EPSILON);
  EXPECT_NEAR(test_color.point_width, 5, EPSILON);
  EXPECT_NEAR(test_color.projection_type, 1, EPSILON);

  s21::ColorSettings answer_color = controller.LoadColorSettings(test_path);

  EXPECT_NEAR(answer_color.background_color_r, 100, EPSILON);
  EXPECT_NEAR(answer_color.background_color_g, 10, EPSILON);
  EXPECT_NEAR(answer_color.background_color_b, 20, EPSILON);

  EXPECT_NEAR(answer_color.line_color_r, 0, EPSILON);
  EXPECT_NEAR(answer_color.line_color_g, 80, EPSILON);
  EXPECT_NEAR(answer_color.line_color_b, 15, EPSILON);

  EXPECT_NEAR(answer_color.point_color_r, 100, EPSILON);
  EXPECT_NEAR(answer_color.point_color_g, 10, EPSILON);
  EXPECT_NEAR(answer_color.point_color_b, 0, EPSILON);

  EXPECT_NEAR(answer_color.line_form, 1, EPSILON);
  EXPECT_NEAR(answer_color.point_form, 1, EPSILON);

  EXPECT_NEAR(answer_color.line_width, 10, EPSILON);
  EXPECT_NEAR(answer_color.point_width, 5, EPSILON);
  EXPECT_NEAR(answer_color.projection_type, 1, EPSILON);
}

TEST(FacadeTest, Test12) {
  const char* NameOfFile = "cube_no.obj";
  ASSERT_ANY_THROW({ controller.GetVertex(NameOfFile); });
}
TEST(FacadeTest, Test13) {
  const char* NameOfFile = "cube_no.obj";
  ASSERT_ANY_THROW({ controller.GetFacet(NameOfFile); });
}
TEST(FacadeTest, Test14) {
  s21::Facade* instance1 = s21::Facade::GetInstance();
  s21::Facade* instance2 = s21::Facade::GetInstance();
  EXPECT_EQ(instance1, instance2);
}

TEST(FacadeTest, Test15) {
  const char* NameOfFile = "cube.obj";
  ASSERT_NO_THROW({ controller.GetVertex(NameOfFile); });
}
}  // namespace s21


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
