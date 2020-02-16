#include <catch2/catch.hpp>

#include "ordered_set.h"

TEST_CASE("OrderedSet Test", "[OrderedSet]") {
#ifdef ORDERED_SET_BASE
  SECTION("Creation") {
    SECTION("Default Constructor") {
      OrderedSet s;
    }

    SECTION("From implicit initializer_list") {
      OrderedSet s{1, 2, 3};
    }

    SECTION("From explicit initializer_list") {
      OrderedSet s = {1, 2, 3};
    }

    SECTION("From copy") {
      OrderedSet s = {1, 2, 3};
      OrderedSet copy(s);
    }

    SECTION("From implicit move") {
      OrderedSet move(OrderedSet{1, 2, 3});
    }

    SECTION("From explicit move") {
      OrderedSet s{1, 2, 3};
      OrderedSet move(std::move(s));
      REQUIRE(s.empty());
    }

    SECTION("From explicit move from Set") {
      Set s{1, 2, 3};
      OrderedSet move(std::move(s));
      REQUIRE(s.empty());
    }

    SECTION("With duplicate values") {
      OrderedSet s = {4, 5, 5, 6};
    }

    SECTION("With not ordered values") {
      OrderedSet s = {1, 5, 4, 3, 2};
    }
  }

  SECTION("Size") {
    SECTION("empty") {
      REQUIRE(OrderedSet{}.size() == 0);
    }

    SECTION("not empty") {
      REQUIRE(OrderedSet{1, 2, 3}.size() == 3);
    }
  }
#endif

#ifdef ORDERED_SET_GET_SMALLER
  SECTION("GetSmaller") {
    OrderedSet s = {1, 2, 3, 20, 13, 9};

    SECTION("empty") {
      OrderedSet empty;
      REQUIRE(empty.GetSmaller(100) == OrderedSet{});
    }

    SECTION("single value") {
      OrderedSet single = {1};
      REQUIRE(single.GetSmaller(100) == single);
    }

    SECTION("x <") {
      REQUIRE(s.GetSmaller(0) == OrderedSet{});
    }

    SECTION("x <=") {
      REQUIRE(s.GetSmaller(1) == OrderedSet{});
    }

    SECTION("x >") {
      REQUIRE(s.GetSmaller(21) == s);
    }

    SECTION("matching between") {
      REQUIRE(s.GetSmaller(2) == OrderedSet{1});
      REQUIRE(s.GetSmaller(3) == OrderedSet{1, 2});
      REQUIRE(s.GetSmaller(9) == OrderedSet{1, 2, 3});
      REQUIRE(s.GetSmaller(13) == OrderedSet{1, 2, 3, 9});
      REQUIRE(s.GetSmaller(20) == OrderedSet{1, 2, 3, 9, 13});
    }

    SECTION("not matching between") {
      REQUIRE(s.GetSmaller(8) == OrderedSet{1, 2, 3});
      REQUIRE(s.GetSmaller(11) == OrderedSet{1, 2, 3, 9});
      REQUIRE(s.GetSmaller(18) == OrderedSet{1, 2, 3, 9, 13});
    }

    SECTION("Size with start offset from GetSmaller") {
      REQUIRE(OrderedSet{1, 2, 3}.GetSmaller(3).size() == 2);
    }

    SECTION("No new memory is allocated") {
      auto os = s.GetSmaller(8);
      REQUIRE(os.begin() >= s.begin());
      REQUIRE(os.end() <= s.end());
    }
  }
#endif

#ifdef ORDERED_SET_GET_LARGER
  SECTION("GetLarger") {
    OrderedSet s = {1, 2, 3, 20, 13, 9};

    SECTION("empty") {
      OrderedSet empty;
      REQUIRE(empty.GetLarger(0) == OrderedSet{});
    }

    SECTION("single value") {
      OrderedSet single = {100};
      REQUIRE(single.GetLarger(1) == single);
    }

    SECTION("x <") {
      REQUIRE(s.GetLarger(0) == s);
    }

    SECTION("x >") {
      REQUIRE(s.GetLarger(21) == OrderedSet{});
    }

    SECTION("x >=") {
      REQUIRE(s.GetLarger(20) == OrderedSet{});
    }

    SECTION("matching between") {
      REQUIRE(s.GetLarger(1) == Set{2, 3, 9, 13, 20});
      REQUIRE(s.GetLarger(2) == Set{3, 9, 13, 20});
      REQUIRE(s.GetLarger(3) == Set{9, 13, 20});
      REQUIRE(s.GetLarger(9) == Set{13, 20});
      REQUIRE(s.GetLarger(13) == Set{20});
    }

    SECTION("not matching between") {
      REQUIRE(s.GetLarger(5) == Set{9, 13, 20});
      REQUIRE(s.GetLarger(11) == Set{13, 20});
      REQUIRE(s.GetLarger(15) == Set{20});
    }

    SECTION("Size with start offset from GetLarger") {
      REQUIRE(OrderedSet{1, 2, 3}.GetLarger(1).size() == 2);
    }

    SECTION("No new memory is allocated") {
      auto os = s.GetLarger(5);
      REQUIRE(os.begin() >= s.begin());
      REQUIRE(os.end() <= s.end());
    }
  }
#endif

#ifdef ORDERED_SET_MERGE
  SECTION("Merge") {
    OrderedSet s1 = {3, 2, 1, 1, 2};

    SECTION("rhs empty") {
      REQUIRE(Set::Merge(s1, Set{}) == s1);
    }

    SECTION("lhs empty") {
      REQUIRE(Set::Merge(Set{}, s1) == s1);
    }

    SECTION("same instance") {
      REQUIRE(Set::Merge(s1, s1) == s1);
    }

    SECTION("identical") {
      REQUIRE(Set::Merge({3, 1, 2}, {3, 1, 2}) == s1);
    }

    SECTION("not identical") {
      REQUIRE(Set::Merge(Set{1, 2}, Set{3, 4}) == Set{1, 2, 3, 4});
    }

    SECTION("with duplicate values") {
      OrderedSet s2 = {3, 2, 4};
      OrderedSet s3 = {1, 2, 3, 4};
      REQUIRE(Set::Merge(s1, s2) == s3);
    }

    SECTION("check that ordered implementation is used") {
      OrderedSet s = {2, 1};
      const auto res = Set::Merge(s, s);
      REQUIRE(res[0] == 1);
      REQUIRE(res[1] == 2);
    }
  }
#endif
}
