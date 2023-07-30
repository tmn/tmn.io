#include "mdparser.h"

int main(int argc, char* argv[])
{
  MDParser * parser = new MDParser();

  std::cout << "Program: " << argv[ 0 ]
            << "\nInput file:\n";

  for (int n = 1; n < argc; n++) {
    std::cout << std::setw( 2 ) << n << ": " << argv[ n ] << '\n';
    parser->create_article(parser->parse_markdown_to_html(parser->read_file(argv[n])));
  }

  parser->create_index_file();

  delete parser;

  return 0;
}
