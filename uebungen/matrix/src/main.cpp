
#include <iostream>

#include "utils/chrono_io.h"
#include "utils/stopwatch.h"

#include "matrix.h"

int main(int argc, char* argv[]) {
  Stopwatch<std::chrono::milliseconds> stopwatch;
  stopwatch.Start();

  Matrix a(400, 2000);
  a.SetIdentity();
  Matrix b(3000, 400);
  b.SetAll();

  std::cout << stopwatch.Stop().GetElapsedTime() << std::endl;

  if (a.Equals(b) == false) {
    std::cerr << "Not equals" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "Is Equals" << std::endl;
  return EXIT_SUCCESS;
}
