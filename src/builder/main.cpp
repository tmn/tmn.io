#include "tmnio.h"
#include "utils.h"

int main(int argc, char* argv[])
{
  tmnio * www = new tmnio();

  www->create_dist_directory();

  std::cout << "Program: " << argv[ 0 ]
            << "\nInput file:\n";

  for (int n = 1; n < argc; n++) {
    std::cout << std::setw( 2 ) << n << ": " << argv[ n ] << '\n';
    www->create_article(argv[n]);
  }

  www->create_index_file();

  return 0;
}
