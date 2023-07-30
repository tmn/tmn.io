#include "mdparser.h"

int main(int argc, char* argv[])
{
  MDParser * parser = new MDParser();

  std::cout << "Program: " << argv[ 0 ]
            << "\nInput file:\n";

  for (int n = 1; n < argc; n++) {
    std::cout << std::setw( 2 ) << n << ": " << argv[ n ] << '\n';
  }

  std::cout << '\n';

  parser->create_article(parser->parse_markdown_to_html(parser->read_file(argv[1])));

  tinyxml2::XMLPrinter printer;
  parser->getDocument()->Print(&printer);

  std::cout << printer.CStr() << '\n';

  return 0;
}
