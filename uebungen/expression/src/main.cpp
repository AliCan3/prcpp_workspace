#include <iostream>

#include "expression.h"
#include "expression_operations.h"
#include "element_operations.h"
#include "vector_operations.h"

int main() {
  {
    std::vector a = {1, 2, 3, 4};
    std::vector b = {2, 1, 0, 1};
    const auto e = (a - b) * (a + b);
    std::cout << e << std::endl;        // [-3,3,9,15]
    std::cout << e[0] << std::endl;     // -3
  }

  {
    std::vector a = {1, 2, 3, 4, 5};
    std::vector b = {1, 4, 9, 16, 25};
    std::vector c = {2, 6, 12, 20, 30};

    std::cout << (a * b * c) << std::endl;  // [2,48,324,1280,3750]
    std::cout << (c * b * a) << std::endl;  // [2,48,324,1280,3750]
  }
}
