#include "tmnio.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
  // Create base directories
  if (!fs::exists("_dist")) {
    if (fs::create_directory("_dist"))
      std::cout << "Successfully created _dist directory" << '\n';
  }

  if (!fs::exists("_dist/read")) {
    if (fs::create_directory("_dist/read"))
      std::cout << "Successfully created _dist/read directory" << '\n';
  }

  const auto copyOptions = fs::copy_options::overwrite_existing
                         | fs::copy_options::recursive
                         ;

  fs::copy("src/www/img",      "_dist/img",        copyOptions);
  fs::copy("src/www/assets",   "_dist/assets",     copyOptions);

  // Start parsing work from here ...
  tmnio * www = new tmnio();

  std::cout << "Program: " << argv[ 0 ]
            << "\nInput file:\n";

  for (int n = 1; n < argc; n++) {
    std::cout << std::setw( 2 ) << n << ": " << argv[ n ] << '\n';
    www->create_article(argv[n]);
  }

  www->create_index_file();

  return 0;
}
