#include <catch2/catch.hpp>

#include "expression.h"
#include "expression_operations.h"
#include "vector_operations.h"

TEST_CASE("Expression Test") {
#ifdef EXPRESSION_BASE
  SECTION("Base") {
    SECTION("Size") {
      std::vector a = {2, 3, 4};
      std::vector b = {1, 2, 3};

      auto res = a + b;
      REQUIRE(res.size() == 3);
    }

    SECTION("Index Operator") {
      std::vector a = {2, 3, 4};
      std::vector b = {1, 2, 3};

      auto res = a + b;
      REQUIRE(res[0] == 3);
      REQUIRE(res[1] == 5);
      REQUIRE(res[2] == 7);
    }

    SECTION("Comparison") {
      std::vector a = {2, 4, 6};
      std::vector b = {1, 2, 3};

      SECTION("Expression == vector") {
        REQUIRE(b + b == a);
      }

      SECTION("vector == Expression") {
        REQUIRE(a == b + b);
      }

      SECTION("Expression == Expression") {
        REQUIRE(a + b == b + a);
      }
    }

    SECTION("Two Vectors") {
      std::vector a = {2};
      std::vector b = {1};

      SECTION("Add") {
        REQUIRE(a + b == std::vector{3});
      }

      SECTION("Sub") {
        REQUIRE(a - b == std::vector{1});
      }

      SECTION("Mul") {
        REQUIRE(a * b == std::vector{2});
      }

      SECTION("Div") {
        REQUIRE(a / b == std::vector{2});
      }
    }
  }

  SECTION("Expression base") {
    SECTION("Expression from left") {
      std::vector a = {2, 3, 4};
      std::vector b = {1, 2, 3};

      REQUIRE((a + b) + a == std::vector{5, 8, 11});
      REQUIRE((a + b + b) + a == std::vector{6, 10, 14});
    }

    SECTION("Expression from right") {
      std::vector a = {2, 3, 4};
      std::vector b = {1, 2, 3};

      REQUIRE(a + (a + b) == std::vector{5, 8, 11});
      REQUIRE(a + (a + b + b) == std::vector{6, 10, 14});
    }

    SECTION("Expression from both sides") {
      std::vector a = {2, 3, 4};
      std::vector b = {1, 2, 3};

      REQUIRE((a + a) + (b + b) == std::vector{6, 10, 14});
    }

    SECTION("Various") {
      std::vector a = {1, 2, 3, 4, 5};
      std::vector b = {1, 4, 9, 16, 25};
      std::vector c = {2, 6, 12, 20, 30};

      REQUIRE(a * b * c == c * b * a);
      REQUIRE(a * b * c == b * c * a);
      REQUIRE(a * b * c == b * a * c);

      REQUIRE(b * c / a == b / a * c);
      REQUIRE(c * b / a == b * c / a);

      REQUIRE((a + b) * a == c * a);
      REQUIRE(a * c == a * (b + a));
      REQUIRE(a * (a + b) / a == c);
      REQUIRE((c + b) / a == c / a + b / a);

      REQUIRE((a + b) - b == a);
      REQUIRE(a == (a - b) + b);
      REQUIRE((a + b) - (c - a) == a);
      REQUIRE(a + b + b + a == c + c - b + b - (a + a) + a + a);

      REQUIRE((a * b)[1] == (c / a)[4] + (c / a)[0]);
    }
  }
#endif

#ifdef SCALAR_FROM_RIGHT
  SECTION("Scalar from right") {
    std::vector<double> a = {1, 2, 3, 4, 5};
    std::vector<double> b = {0.5, 1.0, 1.5, 2.0, 2.5};
    std::vector<double> c = {2, 3, 4, 5, 6};

    REQUIRE(a * 0.5 == b);
    REQUIRE(b == a * 0.5);

    REQUIRE(a / 2.0 == b);
    REQUIRE(b == a / 2.0);

    REQUIRE(a + 1.0 == c);
    REQUIRE(c == a + 1.0);

    REQUIRE(c - 1.0 == a);
    REQUIRE(a == c - 1.0);
  }
#endif

#ifdef SCALAR_FROM_LEFT
  SECTION("Scalar from left") {
    std::vector<double> a = {1, 2, 3, 4, 5};
    std::vector<double> b = {0.5, 1.0, 1.5, 2.0, 2.5};
    std::vector<double> c = {2, 3, 4, 5, 6};

    REQUIRE(0.5 * a == b);
    REQUIRE(b == 0.5 * a);

    REQUIRE((2.0 / a)[3] == b[0]);
    REQUIRE(b[1] == (2.0 / a)[1]);

    REQUIRE(1.0 + a == c);
    REQUIRE(c == 1.0 + a);

    REQUIRE((5.0 - a)[1] == c[1]);
    REQUIRE(c[0] == (5.0 - a)[2]);
  }
#endif

#if defined(SCALAR_FROM_RIGHT) && defined(SCALAR_FROM_LEFT)
  SECTION("Scalar from right and left") {
    std::vector a = {1, 2, 3, 4, 5};
    std::vector b = {1, 4, 9, 16, 25};
    std::vector c = {2, 6, 12, 20, 30};

    REQUIRE((a + b + c) / 2 == c);

    REQUIRE(a + b + b + a == 2 * c);
    REQUIRE(c * 2 == (b + b) + (a + a));
    REQUIRE(3 * (a + b) - (b + a) * 2 == c);

    REQUIRE(3 + (a + b) - 3 == c);
    REQUIRE(2 * (c - b) / 2 + b == (a * 4 + 4 * b) / 4);

    REQUIRE((a + b) / c == std::vector{1, 1, 1, 1, 1});
    REQUIRE((((a + b) / c) * 9)[3] == b[2]);
    REQUIRE(b[4] == (25 * ((c + b) / a) / 11)[4]);
  }
#endif

#ifdef DOT_PRODUCT
  SECTION("Dot product") {
    std::vector a = {1, 2, 3, 4, 5};
    std::vector b = {1, 4, 9, 16, 25};
    std::vector c = {2, 6, 12, 20, 30};

    SECTION("Cast to scalar") {
      REQUIRE(static_cast<int>(a ** b) == 225);
    }

    SECTION("Simple") {
      REQUIRE(a ** b == b ** a);
      REQUIRE(static_cast<int>(a ** b) == b ** a);
      REQUIRE(a ** b == static_cast<int>(b ** a));
    }

    SECTION("As external Expression") {
      REQUIRE(a ** (a + b) == (b + a) ** a);
      REQUIRE(a ** (a + b) == static_cast<int>((b + a) ** a));
      REQUIRE(static_cast<int>(a ** (a + b)) == (b + a) ** a);
    }

    SECTION("As internal Expression") {
      REQUIRE(a + (a ** b) == (b ** a) + a);
    }

    SECTION("Internal and external") {
      REQUIRE(a ** (b * (a ** b)) == 50625);
      REQUIRE((a ** b) * (a ** b) == 50625);
    }

    SECTION("Combined with scalar") {
      REQUIRE(a ** b * 2 == 2 * b ** a);
      REQUIRE(static_cast<int>(a ** b * 2) == 2 * b ** a);
      REQUIRE(2 * b ** a == static_cast<int>(2 * b ** a));
    }

    SECTION("Various") {
      REQUIRE((a ** b) * (a + b) / (b ** a) == c);
      REQUIRE((a ** b) * c - b * (b ** a) == a * (a ** b));
      REQUIRE((a * a) ** (b * b) == (a * b) ** (b * a));
      REQUIRE(a ** b * 2 == 2 * b ** a);
      REQUIRE(static_cast<int>(2 + a ** b - 2) == b ** a);
    }
  }
#endif
}
