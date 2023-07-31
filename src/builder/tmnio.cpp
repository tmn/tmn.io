#include "tmnio.h"

tmnio::tmnio()
{
  document = new tinyxml2::XMLDocument();

  tinyxml2::XMLElement *element = document->NewElement("section");
  element->SetAttribute("class", "container");
  element->SetAttribute("id", "blogContent");

  document->InsertFirstChild(element);
}

tmnio::~tmnio()
{
  delete document;
}

void tmnio::create_article(const char* file)
{
  std::string file_content = tmnio::read_file(file);
  std::string html_content = tmnio::parse_markdown_to_html(file_content);

  tinyxml2::XMLDocument article_content;
  article_content.Parse(html_content.c_str(), html_content.length());

  tinyxml2::XMLElement *article = document->NewElement("article");
  document->FirstChildElement("section")->InsertEndChild(article);

  for (tinyxml2::XMLNode *node = article_content.FirstChildElement(); node; node = node->NextSibling()) {
    tinyxml2::XMLNode *n = node->DeepClone(document);
    parse_code_block(n);
    article->InsertEndChild(n);
  }

  parse_meta_field(article);
}

void tmnio::create_index_file()
{
  std::ifstream html_file("src/www/index.html");
  std::ofstream outfile("_dist/index.html");

  std::string line;
  std::string old ("{{ARTICLES}}");

  while(std::getline(html_file, line)) {
    std::size_t found = line.find(old);

    if (found!=std::string::npos) {
      tinyxml2::XMLPrinter printer;
      document->Print(&printer);
      line.replace(found, sizeof(old), printer.CStr());
    }

    outfile << line << '\n';
  }

  outfile.close();
}

void tmnio::parse_code_block(tinyxml2::XMLNode *src)
{
  // Fix code blocks
  tinyxml2::XMLNode *code = src->FirstChildElement("code");
  if (code) {
    tinyxml2::XMLNode *el = code->FirstChild();

    if (el) {
      tinyxml2::XMLPrinter p;
      el->Accept(&p);
      code->DeleteChildren();
      code->ToElement()->SetText(p.CStr());
    }
  }
}

void tmnio::parse_meta_field(tinyxml2::XMLNode *src)
{
  tinyxml2::XMLElement *el = src->FirstChildElement("p");
  el->SetAttribute("class", "article-meta");
  src->InsertFirstChild(el);
}


//
// Static methods
//
std::string tmnio::read_file(const char* file)
{
  std::ifstream markdown_file(file);
  std::string markdown_content((std::istreambuf_iterator<char>(markdown_file)),
                 (std::istreambuf_iterator<char>()));

  return markdown_content;
}

std::string tmnio::parse_markdown_to_html(std::string content)
{
  std::stringstream markdownInput(content);

  std::shared_ptr<maddy::ParserConfig> config = std::make_shared<maddy::ParserConfig>();
  config->enabledParsers &= ~maddy::types::EMPHASIZED_PARSER;
  config->enabledParsers |= maddy::types::HTML_PARSER;

  std::shared_ptr<maddy::Parser> parser = std::make_shared<maddy::Parser>();
  std::string htmlOutput = parser->Parse(markdownInput);

  return htmlOutput;
}
