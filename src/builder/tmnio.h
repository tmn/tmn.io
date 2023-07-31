#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

#include "maddy/parser.h"
#include "tinyxml2.h"

class tmnio
{
 public:
  tmnio();
  ~tmnio();

  void create_article(const char* file);
  void create_index_file();

  void parse_code_block(tinyxml2::XMLNode *src);
  void parse_meta_field(tinyxml2::XMLNode *src);

  static std::string read_file(const char* file);
  static std::string parse_markdown_to_html(std::string content);

  tinyxml2::XMLDocument * getDocument() { return this->document; }

 private:
  tinyxml2::XMLDocument *document = nullptr;
};
