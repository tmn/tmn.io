#include "tmnio.h"

int main(int argc, char* argv[])
{
  tmnio * parser = new tmnio();

  std::cout << "Program: " << argv[ 0 ]
            << "\nInput file:\n";

  for (int n = 1; n < argc; n++) {
    std::cout << std::setw( 2 ) << n << ": " << argv[ n ] << '\n';
    parser->create_article(argv[n]);
  }

  parser->create_index_file();

  return 0;
}
