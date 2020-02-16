#include <catch2/catch.hpp>

#include "set.h"

TEST_CASE("Set Test", "[Set]") {
  SECTION("Creation") {
    SECTION("Default Constructor") {
      Set s;
    }

    SECTION("Allocate memory but still 'empty'") {
      Set s(5);
      REQUIRE(s.empty());
    }

    SECTION("From implicit initializer_list") {
      Set s{1, 2, 3};
    }

    SECTION("From explicit initializer_list") {
      Set s = {1, 2, 3};
    }

    SECTION("From copy") {
      Set s = {1, 2, 3};
      Set copy(s);
      REQUIRE(copy.begin() >= s.begin());
      REQUIRE(copy.end() <= s.end());
    }

    SECTION("From implicit move") {
      Set move(Set{1, 2, 3});
    }

    SECTION("From explicit move") {
      Set s = {1, 2, 3};
      Set move(std::move(s));
      REQUIRE(s.begin() == nullptr);
      REQUIRE(s.empty());
    }

    SECTION("With duplicate values") {
      Set s = {4, 5, 5, 6};
    }

    SECTION("With not ordered values") {
      Set s = {1, 5, 4, 3, 2};
    }
  }

  SECTION("Contains") {
    SECTION("Empty Set contains nothing") {
      Set s;
      REQUIRE(s.Contains(1) == false);
    }

    SECTION("Filled Set contains exact values") {
      Set s1 = {1, 2, 3};
      REQUIRE(s1.Contains(0) == false);
      REQUIRE(s1.Contains(1));
      REQUIRE(s1.Contains(2));
      REQUIRE(s1.Contains(3));
      REQUIRE(s1.Contains(5) == false);
    }
  }

  SECTION("ContainsAll") {
    Set more = {1, 2, 3};
    Set less = {2, 1};
    Set empty;

    SECTION("more contains less") {
      REQUIRE(more.ContainsAll(less));
    }

    SECTION("less contains not more") {
      REQUIRE(less.ContainsAll(more) == false);
    }

    SECTION("empty contains nothing") {
      REQUIRE(empty.ContainsAll(less) == false);
      REQUIRE(empty.ContainsAll(more) == false);
    }

    SECTION("more contains empty") {
      REQUIRE(more.ContainsAll(empty));
    }

    SECTION("less contains empty") {
      REQUIRE(less.ContainsAll(empty));
    }
  }

  SECTION("Equality") {
    Set more = {1, 2, 3};
    Set other = {3, 1, 2};
    Set less = {2, 1};
    Set empty;

    SECTION("more not equals less") {
      REQUIRE(more != less);
      REQUIRE((more == less) == false);
    }

    SECTION("less not equals more") {
      REQUIRE(less != more);
      REQUIRE((less == more) == false);
    }

    SECTION("more not equals empty") {
      REQUIRE(more != empty);
      REQUIRE((more == empty) == false);
    }

    SECTION("more equals other") {
      REQUIRE(more == other);
      REQUIRE((more != other) == false);
    }

    SECTION("more equals copy") {
      Set copy(more);
      REQUIRE(more == copy);
      REQUIRE((more != copy) == false);
    }

    SECTION("more equals more") {
      REQUIRE(more == more);
      REQUIRE((more != more) == false);
    }
  }

  SECTION("empty") {
    SECTION("empty is true") {
      REQUIRE(Set{}.empty());
    }

    SECTION("not empty is false") {
      REQUIRE(Set{1}.empty() == false);
    }
  }

  SECTION("size") {
    SECTION("empty") {
      REQUIRE(Set{}.size() == 0);
    }

    SECTION("not empty") {
      REQUIRE(Set{1, 2, 3}.size() == 3);
    }
  }

#ifdef OPERATION_MERGE
  SECTION("Merge") {
    Set s1 = {2, 1, 3};

    SECTION("rhs empty") {
      REQUIRE(Set::Merge(s1, Set{}) == s1);
    }

    SECTION("lhs empty") {
      REQUIRE(Set::Merge(Set{}, s1) == s1);
    }

    SECTION("same instance") {
      const auto expected = s1;
      REQUIRE(Set::Merge(s1, s1) == expected);
    }

    SECTION("identical") {
      REQUIRE(Set::Merge({3, 1, 2}, {3, 1, 2}) == s1);
    }

    SECTION("not identical") {
      Set result = {1, 2, 3, 4};
      REQUIRE(Set::Merge(s1, {3, 2, 4}) == result);
    }
  }
#endif

#ifdef OPERATION_INTERSECTION
  SECTION("Intersection") {
    Set s1 = {1, 2, 3};

    SECTION("rhs empty") {
      REQUIRE(Set::Intersection(s1, Set{}) == Set{});
    }

    SECTION("lhs empty") {
      REQUIRE(Set::Intersection(Set{}, s1) == Set{});
    }

    SECTION("same instance") {
      const auto expected = s1;
      REQUIRE(Set::Intersection(s1, s1) == expected);
    }

    SECTION("identical") {
      REQUIRE(Set::Intersection({3, 1, 2}, {3, 1, 2}) == Set{3, 1, 2});
    }

    SECTION("not identical") {
      Set s2 = {3, 2, 4};
      REQUIRE(Set::Intersection(s1, s2) == Set{3, 2});
      REQUIRE(Set::Intersection(s2, s1) == Set{3, 2});
    }

    SECTION("no intersection") {
      REQUIRE(Set::Intersection(s1, Set{4, 5}) == Set{});
    }
  }
#endif

#ifdef OPERATION_DIFFERENCE
  SECTION("Difference") {
    Set s1 = {1, 2, 3};

    SECTION("rhs empty") {
      REQUIRE(Set::Difference(s1, Set{}) == s1);
    }

    SECTION("lhs empty") {
      REQUIRE(Set::Difference(Set{}, s1) == Set{});
    }

    SECTION("same instance") {
      REQUIRE(Set::Difference(s1, s1) == Set{});
    }

    SECTION("identical") {
      REQUIRE(Set::Difference({3, 1, 2}, {3, 1, 2}) == Set{});
    }

    SECTION("not identical") {
      Set s2 = {3, 2, 4};
      REQUIRE(Set::Difference(s1, s2) == Set{1});
      REQUIRE(Set::Difference(s2, s1) == Set{4});
    }
  }
#endif

#ifdef OPERATION_INTERSECTION_MOVE
  SECTION("Move Intersection") {
    Set s1 = {1, 2, 3};
    Set s2 = {3, 2, 4};
    Set res = {2, 3};

    SECTION("lhs is rvalue") {
      REQUIRE(Set::Intersection(Set(s1), s2) == res);
    }

    SECTION("rhs is rvalue") {
      REQUIRE(Set::Intersection(s1, Set(s2)) == res);
    }

    SECTION("both are rvalue") {
      REQUIRE(Set::Intersection(Set(s1), Set(s2)) == res);
    }

    SECTION("lhs is manually moved") {
      REQUIRE(Set::Intersection(std::move(s1), s2) == res);
      REQUIRE(s1.empty());
    }

    SECTION("rhs is manually moved") {
      REQUIRE(Set::Intersection(s1, std::move(s2)) == res);
      REQUIRE(s2.empty());
    }

    SECTION("both are manually moved") {
      REQUIRE(Set::Intersection(std::move(s1), std::move(s2)) == res);
      REQUIRE((s1.empty() || s2.empty()));
    }

    SECTION("do not move if memory is used multiple times") {
      auto copy = s2;
      REQUIRE(Set::Intersection(s1, std::move(s2)) == res);
      REQUIRE((s1 != res && s2 != res));
    }
  }
#endif

#ifdef OPERATION_DIFFERENCE_MOVE
  SECTION("Move Difference") {
    Set s1 = {1, 2, 3};
    Set s2 = {2, 3};
    Set res = {1};

    SECTION("lhs is rvalue") {
      REQUIRE(Set::Difference(Set(s1), s2) == res);
    }

    SECTION("rhs is rvalue") {
      REQUIRE(Set::Difference(s1, Set(s2)) == res);
    }

    SECTION("both are rvalue") {
      REQUIRE(Set::Difference(Set(s1), Set(s2)) == res);
    }

    SECTION("lhs is manually moved") {
      REQUIRE(Set::Difference(std::move(s1), s2) == res);
      REQUIRE(s1.empty());
    }

    // to move rhs makes no sense because its not guaranteed that the result would fit into rhs memory

    SECTION("both are manually moved") {
      REQUIRE(Set::Difference(std::move(s1), std::move(s2)) == res);
      REQUIRE(s1.empty());
    }

    SECTION("do not move if memory is used multiple times") {
      auto copy = s1;
      REQUIRE(Set::Difference(std::move(s1), s2) == res);
      REQUIRE((s1 != res && s2 != res));
    }
  }
#endif
}
