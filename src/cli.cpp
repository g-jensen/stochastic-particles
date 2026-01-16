#include "../headers/cli.h"
#include <string>
#include <cstring>

float arg_float(int argc, char* argv[], const char* flag, float default_val) {
  for (int i = 1; i < argc - 1; i++) {
    if (strcmp(argv[i], flag) == 0) {
      return std::stof(argv[i + 1]);
    }
  }
  return default_val;
}

int arg_int(int argc, char* argv[], const char* flag, int default_val) {
  for (int i = 1; i < argc - 1; i++) {
    if (strcmp(argv[i], flag) == 0) {
      return std::stoi(argv[i + 1]);
    }
  }
  return default_val;
}
