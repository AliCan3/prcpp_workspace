#include <catch2/catch.hpp>

#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <vector>

#include "utils/stopwatch.h"
#include "utils/chrono_io.h"
#include "matrix.h"

using namespace std::chrono_literals;   // NOLINT[build/namespaces]

static void CheckContent(const Matrix& m, std::vector<double> expected) {
  CHECK(m.Size() == expected.size());
  for (size_t i = 0; i < expected.size(); ++i) {
    INFO("CheckContent [i=" << i << "]: value=" << m.Data()[i] << " expected=" << expected[i]);
    CHECK(m.Data()[i] == Approx(expected[i]));
  }
}

static void FillWithContent(const std::vector<double>& content, Matrix* matrix) {
  REQUIRE(matrix->Size() == content.size());
  std::copy(content.begin(), content.end(), matrix->Data());
}

#ifdef OPERATIONS_POWER
static void CheckPower(size_t k, std::vector<double> values, std::vector<double> expected) {
  Matrix m(2, 2);
  FillWithContent(values, &m);
  const auto result = m.Power(k);
  CheckContent(result, expected);
}
#endif

#ifdef OPERATIONS_POWER_FAST
static void CheckPowerFast(size_t k, std::vector<double> values, std::vector<double> expected) {
  Matrix m(2, 2);
  FillWithContent(values, &m);
  const auto result = m.PowerFast(k);
  CheckContent(result, expected);
}
#endif

TEST_CASE("Matrix Test", "[Matrix]") {
  const size_t d1 = 25;
  const size_t d2 = 50;
  const auto size = d1 * d2;

  SECTION("SetAll") {
    SECTION("Set all to 0.0") {
      std::vector<double> expected(size, 0);
      Matrix m(d1, d2);
      m.SetAll();
      CheckContent(m, expected);
    }

    SECTION("Set all to 3.1415") {
      std::vector<double> expected(size, 3.1415);
      Matrix m(d1, d2);
      m.SetAll(3.1415);
      CheckContent(m, expected);
    }
  }

  SECTION("SetIdentity") {
    SECTION("quadratic") {
      std::vector<double> expected = {1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1};
      Matrix m(4, 4);
      m.SetIdentity();
      CheckContent(m, expected);
    }

    SECTION("d1 bigger") {
      std::vector<double> expected = {1, 0,
                                      0, 1,
                                      0, 0};
      Matrix m(3, 2);
      m.SetIdentity();
      CheckContent(m, expected);
    }

    SECTION("d2 bigger") {
      std::vector<double> expected = {1, 0, 0, 0, 0,
                                      0, 1, 0, 0, 0,
                                      0, 0, 1, 0, 0};
      Matrix m(3, 5);
      m.SetIdentity();
      CheckContent(m, expected);
    }
  }

  SECTION("SetRandom") {
    Matrix m(d1, d2);
    m.SetRandom();

    SECTION("Random interval [0,1) correct") {
      bool in_interval = true;
      for (size_t i = 0; i < size; ++i) {
        if (m.Data()[i] < 0 || m.Data()[i] >= 1) {
          in_interval = false;
          break;
        }
      }
      REQUIRE(in_interval);
    }

    SECTION("Random is not consecutive") {
      bool consecutive = true;
      const double diff = m.Data()[1] - m.Data()[0];
      double running_value = m.Data()[1] + diff;
      for (size_t i = 2; i < size; ++i) {
        if (Math::AlmostEquals(m.Data()[i], running_value) == false) {
          consecutive = false;
          break;
        }
        running_value += diff;
      }
      REQUIRE(consecutive == false);
    }

    SECTION("Random has not more then 1% not unique values") {
      std::unordered_map<double, size_t> value_count;
      for (size_t i = 0; i < size; ++i) {
        value_count[m.Data()[i]] = 0;
      }
      for (size_t i = 0; i < size; ++i) {
        value_count[m.Data()[i]] += 1;
      }

      size_t to_many_count = 0;
      for (const auto&[value, count] : value_count) {
        if (count != 0) {
          to_many_count += 1;
        }
      }
      REQUIRE(to_many_count > static_cast<size_t>(size * 0.01));
    }
  }

  SECTION("Equals") {
    SECTION("d1 does not match") {
      Matrix m1(2, 2);
      Matrix m2(1, 2);

      m1.SetAll(1);
      m2.SetAll(1);

      REQUIRE(m1.Equals(m2) == false);
      REQUIRE(m2.Equals(m1) == false);
    }

    SECTION("d2 does not match") {
      Matrix m1(2, 2);
      Matrix m2(2, 1);

      m1.SetAll(1);
      m2.SetAll(1);

      REQUIRE(m1.Equals(m2) == false);
      REQUIRE(m2.Equals(m1) == false);
    }

    SECTION("first value does not match") {
      Matrix m1(2, 2);
      Matrix m2(2, 2);

      m1.SetAll(1);
      m2.SetAll(1);

      m1.Data()[0] = 2;

      REQUIRE(m1.Equals(m2) == false);
      REQUIRE(m2.Equals(m1) == false);
    }

    SECTION("last value does not match") {
      Matrix m1(2, 2);
      Matrix m2(2, 2);

      m1.SetAll(1);
      m2.SetAll(1);

      m1.Data()[3] = 2;

      REQUIRE(m1.Equals(m2) == false);
      REQUIRE(m2.Equals(m1) == false);
    }

    SECTION("middle value does not match") {
      Matrix m1(2, 2);
      Matrix m2(2, 2);

      m1.SetAll(1);
      m2.SetAll(1);

      m1.Data()[1] = 2;

      REQUIRE(m1.Equals(m2) == false);
      REQUIRE(m2.Equals(m1) == false);
    }

    SECTION("do match with value 1") {
      Matrix m1(100, 500);
      Matrix m2(100, 500);

      m1.SetAll(1);
      m2.SetAll(1);

      REQUIRE(m1.Equals(m2));
      REQUIRE(m2.Equals(m1));
    }

    SECTION("do not match with really small double value") {
      Matrix m1(100, 500);
      Matrix m2(100, 500);

      m1.SetAll(0.09999999999999928335);
      m2.SetAll(0.10000000000000001110);

      REQUIRE(m1.Equals(m2) == false);
      REQUIRE(m2.Equals(m1) == false);
    }

    SECTION("do match with really small double value") {
      Matrix m1(100, 500);
      Matrix m2(100, 500);

      m1.SetAll(0.09999999999999998335);
      m2.SetAll(0.10000000000000001110);

      REQUIRE(m1.Equals(m2));
      REQUIRE(m2.Equals(m1));
    }

    SECTION("do not match with really big double value") {
      Matrix m1(100, 500);
      Matrix m2(100, 500);

      m1.SetAll(250136459204794336937574840524253447676819276986470729425920054053641632352836091947993431017557012156994500047041514968745759369806124943730387259218366236804690052218038165476081471062016.0);   // NOLINT[whitespace/line_length]
      m2.SetAll(250136459204792275104974472248119932551189022074673220643082778750681653837072068723687154384590219577894234736280267569327902865771290105889128682530563744918151276744746186324388433887232.0);   // NOLINT[whitespace/line_length]

      REQUIRE(m1.Equals(m2) == false);
      REQUIRE(m2.Equals(m1) == false);
    }

    SECTION("do match with really big double value") {
      Matrix m1(100, 500);
      Matrix m2(100, 500);

      m1.SetAll(235674758496856121888102396122812523256814314258569356046939449753538225665096752820722709793386261034116549640417430274900403121892930645799081960891983361028980268234076922566358834610176.0);   // NOLINT[whitespace/line_length]
      m2.SetAll(235674758496856276469603316813146311070889951538063128004032638010938171954506810881488401375803242481867212917320548773445044381980017740402228402611489590745327206917306870445591427547136.0);   // NOLINT[whitespace/line_length]

      REQUIRE(m1.Equals(m2));
      REQUIRE(m2.Equals(m1));
    }
  }

  SECTION("Copy Constructor") {
    SECTION("Same values") {
      Matrix matrix(3, 2);
      matrix.SetRandom();
      Matrix copy(matrix);

      REQUIRE(matrix.Equals(copy));
    }

    SECTION("Has its own memory") {
      Matrix matrix(3, 2);
      Matrix copy(matrix);

      REQUIRE(matrix.Data() != copy.Data());
    }
  }

#ifdef OPERATIONS_MULTIPLY
  SECTION("Multiply") {
    SECTION("1x1 x 1x1") {
      Matrix m1(1, 1);
      FillWithContent({2}, &m1);
      Matrix m2(1, 1);
      FillWithContent({5}, &m2);

      const auto result = m1.Multiply(m2);
      CheckContent(result, {10});
    }

    SECTION("3x3 x 3x3") {
      std::vector<double> values1 = {1, 1, 1,
                                     2, 2, 2,
                                     3, 3, 3};
      Matrix m1(3, 3);
      FillWithContent(values1, &m1);

      std::vector<double> values2 = {2, 3, 4,
                                     2, 3, 4,
                                     2, 3, 4};
      Matrix m2(3, 3);
      FillWithContent(values2, &m2);

      std::vector<double> expected = {6, 9, 12,
                                      12, 18, 24,
                                      18, 27, 36};

      const auto result = m1.Multiply(m2);
      CheckContent(result, expected);
    }

    SECTION("3x4 x 4x2") {
      std::vector<double> values1 = {1, 2, 3, 4,
                                     5, 6, 7, 8,
                                     9, 10, 11, 12};
      Matrix m1(3, 4);
      FillWithContent(values1, &m1);

      std::vector<double> values2 = {4, 3,
                                     4, 3,
                                     4, 3,
                                     4, 3};
      Matrix m2(4, 2);
      FillWithContent(values2, &m2);

      std::vector<double> expected = {40, 30,
                                      104, 78,
                                      168, 126};

      const auto result = m1.Multiply(m2);
      CheckContent(result, expected);
    }
  }
#endif

#ifdef OPERATIONS_POWER
  SECTION("Power") {
    SECTION("1x1 k=2") {
      Matrix m(1, 1);
      FillWithContent({2}, &m);

      const auto result = m.Power(2);
      CheckContent(result, {4});
    }

    SECTION("1x1 k=10") {
      Matrix m(1, 1);
      FillWithContent({2}, &m);

      const auto result = m.Power(10);
      CheckContent(result, {1024});
    }

    SECTION("2x2 k=3") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {116, 153,
                                      204, 269};
      CheckPower(3, values, expected);
    }

    SECTION("2x2 k=4") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {844, 1113,
                                      1484, 1957};
      CheckPower(4, values, expected);
    }

    SECTION("2x2 k=5") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {6140, 8097,
                                      10796, 14237};
      CheckPower(5, values, expected);
    }

    SECTION("2x2 k=6") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {44668, 58905,
                                      78540, 103573};
      CheckPower(6, values, expected);
    }

    SECTION("2x2 k=7") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {324956, 428529,
                                      571372, 753485};
      CheckPower(7, values, expected);
    }

    SECTION("2x2 k=8") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {2364028, 3117513,
                                      4156684, 5481541};
      CheckPower(8, values, expected);
    }

    SECTION("2x2 k=9") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {17198108, 22679649,
                                      30239532, 39877757};
      CheckPower(9, values, expected);
    }
  }
#endif

#ifdef OPERATIONS_MULTIPLY_FAST
    SECTION("MultiplyFast") {
      SECTION("Build Type") {
#ifndef NDEBUG
        FAIL("You have to build in Release or RelWithDebInfo mode");
#endif
      }

    SECTION("1x1 x 1x1") {
      Matrix m1(1, 1);
      FillWithContent({2}, &m1);
      Matrix m2(1, 1);
      FillWithContent({5}, &m2);

      const auto result = m1.MultiplyFast(m2);
      CheckContent(result, {10});
    }

    SECTION("3x3 x 3x3") {
      std::vector<double> values1 = {1, 1, 1,
                                     2, 2, 2,
                                     3, 3, 3};
      Matrix m1(3, 3);
      FillWithContent(values1, &m1);

      std::vector<double> values2 = {2, 3, 4,
                                     2, 3, 4,
                                     2, 3, 4};
      Matrix m2(3, 3);
      FillWithContent(values2, &m2);

      std::vector<double> expected = {6, 9, 12,
                                      12, 18, 24,
                                      18, 27, 36};

      const auto result = m1.MultiplyFast(m2);
      CheckContent(result, expected);
    }

    SECTION("3x4 x 4x2") {
      std::vector<double> values1 = {1, 2, 3, 4,
                                     5, 6, 7, 8,
                                     9, 10, 11, 12};
      Matrix m1(3, 4);
      FillWithContent(values1, &m1);

      std::vector<double> values2 = {4, 3,
                                     4, 3,
                                     4, 3,
                                     4, 3};
      Matrix m2(4, 2);
      FillWithContent(values2, &m2);

      std::vector<double> expected = {40, 30,
                                      104, 78,
                                      168, 126};

      const auto result = m1.MultiplyFast(m2);
      CheckContent(result, expected);
    }

      SECTION("Time constraints") {
        Matrix m1(400, 3000);
        m1.SetRandom();
        Matrix m2(3000, 200);
        m2.SetRandom();

        Stopwatch<std::chrono::milliseconds> stopwatch_slow;
        const auto result_slow = m1.Multiply(m2);
        stopwatch_slow.Stop();
        WARN("MultiplySlow: " << stopwatch_slow.GetElapsedTime());

        Stopwatch<std::chrono::milliseconds> stopwatch_fast;
        const auto result_fast = m1.MultiplyFast(m2);
        stopwatch_fast.Stop();
        WARN("MultiplyFast: " << stopwatch_fast.GetElapsedTime());

        CHECK(result_slow.Equals(result_fast));
        REQUIRE(stopwatch_fast.GetElapsedTime() < 200ms);
      }
    }
#endif

#ifdef OPERATIONS_POWER_FAST
  SECTION("PowerFast") {
    SECTION("Build Type") {
#ifndef NDEBUG
      FAIL("You have to build in Release or RelWithDebInfo mode");
#endif
    }

    SECTION("1x1 k=2") {
      Matrix m(1, 1);
      FillWithContent({2}, &m);

      const auto result = m.PowerFast(2);
      CheckContent(result, {4});
    }

    SECTION("1x1 k=10") {
      Matrix m(1, 1);
      FillWithContent({2}, &m);

      const auto result = m.PowerFast(10);
      CheckContent(result, {1024});
    }

    SECTION("2x2 k=3") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {116, 153,
                                      204, 269};
      CheckPowerFast(3, values, expected);
    }

    SECTION("2x2 k=4") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {844, 1113,
                                      1484, 1957};
      CheckPowerFast(4, values, expected);
    }

    SECTION("2x2 k=5") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {6140, 8097,
                                      10796, 14237};
      CheckPowerFast(5, values, expected);
    }

    SECTION("2x2 k=6") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {44668, 58905,
                                      78540, 103573};
      CheckPowerFast(6, values, expected);
    }

    SECTION("2x2 k=7") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {324956, 428529,
                                      571372, 753485};
      CheckPowerFast(7, values, expected);
    }

    SECTION("2x2 k=8") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {2364028, 3117513,
                                      4156684, 5481541};
      CheckPowerFast(8, values, expected);
    }

    SECTION("2x2 k=9") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {17198108, 22679649,
                                      30239532, 39877757};
      CheckPowerFast(9, values, expected);
    }

    SECTION("2x2 k=91") {
      std::vector<double> values = {2, 3,
                                    4, 5};
      std::vector<double> expected = {
          804231808793001680411190194138086785637902692149972699770045053858543078825564.0,
          1060564053793061304219206982568530228320401664698250865578159579876408458515921.0,
          1414085405057415072292275976758040304427202219597667820770879439835211278021228.0,
          1864795862586062984630397176706617013958304356848223565348204633734951537341485.0};
      CheckPowerFast(91, values, expected);
    }

    SECTION("Time constraints") {
      const size_t k = 91;

      Matrix m(250, 250);
      m.SetRandom();

      Stopwatch<std::chrono::milliseconds> stopwatch_slow;
      const auto result_slow = m.Power(k);
      stopwatch_slow.Stop();
      WARN("PowerSlow: " << stopwatch_slow.GetElapsedTime());

      Stopwatch<std::chrono::milliseconds> stopwatch_fast;
      const auto result_fast = m.PowerFast(k);
      stopwatch_fast.Stop();
      WARN("PowerFast: " << stopwatch_fast.GetElapsedTime());

      CHECK(result_slow.Equals(result_fast));
      REQUIRE(stopwatch_fast.GetElapsedTime() < 150ms);
    }
  }
#endif
}
