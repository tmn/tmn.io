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
    article->InsertEndChild(n);
  }

  // Move meta field to top
  tinyxml2::XMLElement *el = article->FirstChildElement("p");
  el->SetAttribute("class", "article-meta");
  article->InsertFirstChild(el);


  // Fix code blocks containing markup
  tinyxml2::XMLElement *pre = article->FirstChildElement("pre");

  for (tinyxml2::XMLNode *pre_node = article->FirstChildElement("pre"); pre_node; pre_node = pre_node->NextSiblingElement("pre")) {
    if (pre_node) {
      tinyxml2::XMLElement *code = pre_node->FirstChildElement("code");

      if (code) {
        tinyxml2::XMLNode *el = code->FirstChild();

        if (el) {
          tinyxml2::XMLPrinter p;
          el->Accept(&p);
          code->DeleteChildren();
          code->SetText(p.CStr());
        }
      }
    }
  }
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
