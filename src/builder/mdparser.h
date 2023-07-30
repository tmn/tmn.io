#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "maddy/parser.h"
#include "tinyxml2.h"

class MDParser
{
 public:
  MDParser();
  ~MDParser();

  std::string read_file(const char* file);
  std::string parse_markdown_to_html(std::string content);
  void create_article(std::string content);
  void create_index_file();

  tinyxml2::XMLDocument * getDocument() { return this->document; }
 private:
  tinyxml2::XMLDocument *document = nullptr;
};
