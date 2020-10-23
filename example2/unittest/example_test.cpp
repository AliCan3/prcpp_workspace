#include <catch2/catch.hpp>

TEST_CASE("Example Test", "[example_tag]") {
  SECTION("Top") {
    int var = 1;
    REQUIRE(var == 1);

    SECTION("Sub2") {
      var = 2;
      REQUIRE(var == 2);
    }

    SECTION("Sub1") {
      REQUIRE(var == 1);
    }
  }
}
