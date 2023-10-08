/// \file
#include "facade.h"

class ICounter {
 public:
  virtual int Сalculate(const char *NameOfFile) = 0;
};

int s21::CounterVertex::Сalculate(const char *NameOfFile) {
  vertex_ = CountVertex(NameOfFile);
  return this->vertex_;
}

/**
 * @brief Считает координаты.
 * @param NameOfFile имя файла .obj.
 * @return V_fields количество координат - количество точек умноженное на 3
 */

int s21::CounterVertex::CountVertex(const char *NameOfFile) {
  char *str = NULL;
  unsigned int V_Fields = 0;
  size_t len = 0;
  FILE *file;
  ssize_t read;
  if ((file = fopen(NameOfFile, "r")) == NULL || file == NULL) {
    throw std::runtime_error("Error opening file");
  }
  while ((read = getline(&str, &len, file)) != -1) {
    if (str[0] == 'v' && str[1] == ' ') V_Fields += 3;
  }
  free(str);
  fclose(file);
  return V_Fields;
}

int s21::CounterFacet::Сalculate(const char *NameOfFile) {
  facet_ = CountFacet(NameOfFile);
  return this->facet_;
}
/**
 * @brief Считает ребра.
 * @param Размерность вектора.
 * @param NameOfFile имя файла .obj.
 * @return F_fields количество ребер
 */

int s21::CounterFacet::CountFacet(const char *NameOfFile) {
  char *str = NULL;
  int F_fields = 0;
  size_t len = 0;
  FILE *file;
  ssize_t read;
  if ((file = fopen(NameOfFile, "r")) == NULL || file == NULL) {
    throw std::runtime_error("Error opening file");
  }
  while ((read = getline(&str, &len, file)) != -1) {
    for (int i = 0; str[i] != '\n'; i++) {
      if (str[0] == 'f' && str[1] == ' ' && str[i] == ' ') F_fields++;
    }
  }
  free(str);
  fclose(file);
  return F_fields;
}

int s21::Facade::GetVertex(const char *NameOfFile) {
  s21::CounterVertex obj_for_calcvertex_;
  vertex_ = obj_for_calcvertex_.Сalculate(NameOfFile);
  return this->vertex_;
}

int s21::Facade::GetFacet(const char *NameOfFile) {
  s21::CounterFacet obj_for_calcfacet_;
  facet_ = obj_for_calcfacet_.Сalculate(NameOfFile);
  return facet_;
}

void s21::Facade::ParseFile(const char *NameOfFile, int *v_num, int *f_num,
                            double **vert, int **facets) {
  *v_num = this->GetVertex(NameOfFile);
  *f_num = this->GetFacet(NameOfFile);

  if (*v_num != -1 && *f_num != -1) {
    Parser(NameOfFile, vert, *v_num, facets, *f_num);
  } else {
    throw std::runtime_error("Error opening file");
  }
}

/**
 *
 @brief извлекает 3 координаты одной точки и записывает их в массив вершин
 @param[in,out] vertex_arr массив вершин
 @param[in] temp строка откуда извлекаются числа
 @param[in,out] i индекс следующего элемента вершин
 @param[in,out] big_vert   наибольшая координата
*/

void s21::Facade::GetDot(double **vertex_arr, char *temp, int *i,
                         double *big_vert) {
  char *end = NULL;
  int j = 0;
  while (*temp && *temp != '\n' && j < 3) {
    if (strtod(temp, &end) == 0.0) {
      if (*temp == '0' || (*temp == '-' && *(temp + 1) == '0')) {
        (*vertex_arr)[(*i)++] = 0;
        j++;
        temp = end;
      } else {
        temp++;
      }
    } else {
      (*vertex_arr)[*i] = strtod(temp, &end);
      j++;
      if (fabs((*vertex_arr)[*i]) > *big_vert) {
        *big_vert = fabs((*vertex_arr)[*i]);
      }
      (*i)++;
      temp = end;
    }
  }
}

/**
 @brief центрирует модель и приводит все координаты к диапазону [-1,1]
 @param[in] big_vert  наибольшая координата
 @param[in,out] vertex_arr массив координат
 @param[in] len длина массива координат
 (-1 )
*/

void s21::Facade::Center(double big_vert, double **vertex_arr, int len) {
  double big_v = -100.0;
  double small_v = 100.0;
  if (big_vert > 1.0) {
    for (int j = 0; j < len; j++) {
      (*vertex_arr)[j] = (*vertex_arr)[j] / big_vert;
      if (j % 3 == 1) {
        if ((*vertex_arr)[j] > big_v) big_v = (*vertex_arr)[j];
        if ((*vertex_arr)[j] < small_v) small_v = (*vertex_arr)[j];
      }
    }
  }
  double coef = (big_v + small_v) / 2;
  for (int j = 0; j < len; j++) {
    if (j % 3 == 1) (*vertex_arr)[j] -= coef;
  }
}

/**
 @brief Extracts all vertexes and facets
 @param[in] NameOfFile .obj filename
 @param[in,out] vertex_arr array to write vertex coordinates in
 @param[in] V_field_number length of vertex array
 @param[in,out] facet_arr array to write facet points in
 @param[in] F_field_number length of facet array
*/

void s21::Facade::Parser(const char *NameOfFile, double **vertex_arr,
                         int V_field_number, int **facet_arr,
                         int F_field_number) {
  DelSpace(NameOfFile);
  char *str = NULL;
  double big_vert = 0.0;
  *facet_arr = (int *)malloc((F_field_number * sizeof(int)) * 2);
  *vertex_arr = (double *)malloc(V_field_number * sizeof(double));

  if (!(*facet_arr) || !(*vertex_arr)) {
    free(*facet_arr);
    free(*vertex_arr);
    throw std::runtime_error("Error opening file");
  } else {
    int count_dot = 0;
    int i = 0;
    int j = 0;
    size_t len = 0;
    FILE *file;
    ssize_t read;
    if ((file = fopen(NameOfFile, "r")) != NULL && file != NULL) {
      while ((read = getline(&str, &len, file)) != -1) {
        char *temp = str;
        if (*temp && temp[0] == 'v' && temp[1] == ' ') {
          GetDot(vertex_arr, temp, &j, &big_vert);
          count_dot += 1;
        } else if (*temp && temp[0] == 'f' && temp[1] == ' ') {
          GetFacet(temp, facet_arr, &i, count_dot);
        }
      }
      Center(big_vert, vertex_arr, j);
    } else {
      throw std::runtime_error("Error opening file");
    }
    free(str);
    fclose(file);
  }
}
/**
 * Gets facet points
 \param[in] str string to extract numbers from
 \param[in,out] facets array to write facet points in
 \param[in,out] i index of next facets array element
*/

void s21::Facade::GetFacet(char *str, int **facets, int *i, int count_dot) {
  char *end = NULL;
  end = str;
  int currentfacet_;
  int flag = 0;
  int oneValue = 0;
  while (*str && *str != '\n') {
    if (*str == ' ') {
      currentfacet_ = ((int)strtod(str, &end) - 1);
      if (currentfacet_ < 0) currentfacet_ = count_dot + currentfacet_ + 1;
      (*facets)[*i] = currentfacet_;
      if (flag == 0) {
        flag = 1;
        oneValue = currentfacet_;
      } else {
        (*facets)[(*i) + 1] = currentfacet_;
        (*i)++;
      }
      (*i)++;
    } else {
      while ((*end != ' ') && (*end != '\0') && (*end != '\n')) end++;
    }
    str = end;
  }
  flag = 0;
  (*facets)[*i] = oneValue;
  (*i)++;
}

void s21::Facade::DelSpace(const char *NameOfFile) {
  std::ifstream inputFile(NameOfFile);
  if (!inputFile) {
    throw std::runtime_error("Error opening file");
  }

  std::string tempFileName = std::string(NameOfFile) + ".temp";

  std::ofstream outputFile(tempFileName);
  if (!outputFile) {
    throw std::runtime_error("Error creating temporary file");
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    line.erase(std::find_if(line.rbegin(), line.rend(),
                            [](int ch) { return !std::isspace(ch); })
                   .base(),
               line.end());
    outputFile << line << std::endl;
  }

  inputFile.close();
  outputFile.close();

  if (std::rename(tempFileName.c_str(), NameOfFile) != 0) {
    throw std::runtime_error("File replacement error");
  }
}

s21::Facade *s21::Facade::p_instance = nullptr;