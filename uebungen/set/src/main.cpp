#include "set.h"
#include "ordered_set.h"

#include <iostream>

int main() {
  {
    Set s = Set::Difference(Set({1, 2, 3}), Set({2, 3, 4}));
    std::cout << s << std::endl;
  }

  return EXIT_SUCCESS;
}
