#include "tmnio.h"
#include "utils.h"

namespace fs = std::filesystem;

tmnio::tmnio(): document(new tinyxml2::XMLDocument()) {}
tmnio::~tmnio()
{
  delete document;
}

const std::string tmnio::ARTICLE_REPLACE_TAG = "{{ARTICLES}}";

void tmnio::create_article(const char* file)
{
  std::string file_content(tmnio::read_file(file));
  std::string html_content(tmnio::parse_markdown_to_html(file_content));

  // Parse article path
  std::vector<std::string> path_v(utils::split(file, '/'));
  std::ostringstream spath;
  std::copy(path_v.begin(), path_v.end(), std::ostream_iterator<std::string>(spath, "/"));

  std::string path("/read/" + spath.str());
  path.erase(path.end()-4, path.end());

  // Create article
  tinyxml2::XMLDocument article_content;
  article_content.Parse(html_content.c_str(), html_content.length());

  tinyxml2::XMLElement *article = document->NewElement("article");
  tinyxml2::XMLElement *header = document->NewElement("header");

  document->InsertEndChild(article);
  article->InsertFirstChild(header);

  for (tinyxml2::XMLNode *node = article_content.FirstChildElement(); node; node = node->NextSibling()) {
    tinyxml2::XMLNode *n = node->DeepClone(document);
    article->InsertEndChild(n);

    parse_code_block(n);
  }

  // Modify article element
  parse_meta_field(article, header, path);
  create_article_file(path, article);
}

void tmnio::create_index_file()
{
  std::ifstream html_file("src/www/index.html");
  std::ofstream outfile("_dist/index.html");
  std::string line;

  while(std::getline(html_file, line)) {
    std::size_t found = line.find(tmnio::ARTICLE_REPLACE_TAG);

    if (found!=std::string::npos) {
      tinyxml2::XMLPrinter printer;
      document->Print(&printer);
      line.replace(found, sizeof(tmnio::ARTICLE_REPLACE_TAG), printer.CStr());
    }

    outfile << line << '\n';
  }

  outfile.close();
}

void tmnio::create_article_file(std::string path, tinyxml2::XMLNode *article)
{
  fs::create_directories("_dist" + path);

  std::ifstream html_file("src/www/index.html");
  std::ofstream outfile("_dist" + path + "/index.html");
  std::string line;

  while(std::getline(html_file, line)) {
    std::size_t found = line.find(tmnio::ARTICLE_REPLACE_TAG);

    if (found!=std::string::npos) {
      tinyxml2::XMLPrinter printer;
      article->Accept(&printer);
      line.replace(found, sizeof(tmnio::ARTICLE_REPLACE_TAG), printer.CStr());
    }

    outfile << line << '\n';
  }

  outfile.close();
}

void tmnio::parse_code_block(tinyxml2::XMLNode *src)
{
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

void tmnio::parse_meta_field(tinyxml2::XMLNode *src, tinyxml2::XMLNode *dest, std::string path)
{
  tinyxml2::XMLElement *el = src->FirstChildElement("p");

  if (el) {
    el->SetAttribute("class", "article-meta");
    dest->InsertFirstChild(el);
  }

  tinyxml2::XMLElement *heading = src->FirstChildElement("h1");

  if (heading) {
    tinyxml2::XMLElement *anchor = document->NewElement("a");
    anchor->SetAttribute("href", path.c_str());
    anchor->SetText(heading->GetText());

    heading->DeleteChildren();
    heading->InsertEndChild(anchor);

    dest->InsertEndChild(heading);
  }
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
