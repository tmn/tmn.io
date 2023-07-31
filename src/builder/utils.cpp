#import "utils.h"


std::vector<std::string> utils::split(const char* s, char delimiter)
{
  std::vector<std::string> tmp;
  std::vector<std::string> r;
  std::stringstream ss(s);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    tmp.push_back(token);
  }

  r = { tmp.end() -4, tmp.end() };

  return r;
}
