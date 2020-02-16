#include <catch2/catch.hpp>

#include "element_operations.h"

TEST_CASE("Element Operations Test") {
  SECTION("Add") {
    SECTION("Integer") {
      REQUIRE(Add::Apply(23, 42) == 65);
    }
    SECTION("Float") {
      REQUIRE(Add::Apply(2.3, 4.2) == Approx(6.5));
    }
  }

  SECTION("Sub") {
    SECTION("Integer") {
      REQUIRE(Sub::Apply(23, 42) == -19);
    }
    SECTION("Float") {
      REQUIRE(Sub::Apply(2.3, 4.2) == Approx(-1.9));
    }
  }

  SECTION("Mul") {
    SECTION("Integer") {
      REQUIRE(Mul::Apply(23, 42) == 966);
    }
    SECTION("Float") {
      REQUIRE(Mul::Apply(2.3, 4.2) == Approx(9.66));
    }
  }

  SECTION("Div") {
    SECTION("Integer") {
      REQUIRE(Div::Apply(23, 2) == 11);
    }
    SECTION("Float") {
      REQUIRE(Div::Apply(4.2, 0.2) == Approx(21.0));
    }
  }

#ifdef ELEMENT_OPERATIONS_DOT
  SECTION("Dot") {
    SECTION("Integer") {
      std::vector a = {1, 2, 3};
      std::vector b = {2, 3, 4};
      REQUIRE(Dot::DotApply(a, b) == 20);
    }
    SECTION("Float") {
      std::vector a = {1.2, 2.3};
      std::vector b = {2.1, 3.2};
      REQUIRE(Dot::DotApply(a, b) == Approx(9.88));
    }
  }
#endif
}
