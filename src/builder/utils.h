#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

class utils
{
 public:
  utils() {};
  ~utils() {};

  static std::vector<std::string> split(const char* s, char delimiter);
};
