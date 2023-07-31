#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <filesystem>

#include "maddy/parser.h"
#include "tinyxml2.h"

class tmnio
{
 public:
  tmnio();
  ~tmnio();

  void create_dist_directory();

  void create_article(const char* file);
  void create_index_file();
  void create_article_file(std::string path, tinyxml2::XMLNode *article);

  void parse_code_block(tinyxml2::XMLNode *src);
  void parse_meta_field(tinyxml2::XMLNode *src, tinyxml2::XMLNode *dest, std::string path);

  static std::string read_file(const char* file);
  static std::string parse_markdown_to_html(std::string content);

  tinyxml2::XMLDocument * getDocument() { return this->document; }

 private:
  tinyxml2::XMLDocument *document = nullptr;
};
