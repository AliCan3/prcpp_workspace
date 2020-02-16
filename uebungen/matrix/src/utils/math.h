#pragma once

#include <cstdint>
#include <cmath>

#include <limits>
#include <type_traits>

class Math {
 public:
  Math() = delete;

  /// \brief Calculates the mathematical power using the given base and exponent at compile time.
  /// \tparam Base Base of the mathematical power
  /// \tparam Exp Exponent of the mathematical power
  template<int Base, std::size_t Exp>
  struct Power {
    static constexpr double value = Base * Power<Base, Exp - 1>::value;
  };

  template<int Base>
  struct Power<Base, 0> {
    static constexpr double value = 1.0;
  };

  /// \brief Evaluates the mathematical greatest common divisor.
  template<std::intmax_t A, std::intmax_t B>
  struct Gcd {
    static constexpr std::intmax_t value = Gcd<B, A % B>::value;
  };

  template< std::intmax_t A >
  struct Gcd<A, 0> {
    static constexpr std::intmax_t value = A;
  };

  /// Rounds the given input value with the given precision and casts the result to the given output value.
  /// \tparam OutputType Type of the output value to return
  /// \tparam InputType Type of the given input value
  /// \tparam Precision Precision of the rounded value in number of decimal digits
  /// \param value Value to be rounded
  /// \return the rounded and casted value with the given precision.
  template<typename OutputType, std::size_t Precision = 0>
  static OutputType Round(const double value) {
    // perform rounding to the specified precision
    constexpr double precision = Power<10, Precision>::value;
    return static_cast<OutputType>(std::round(value * precision) / precision);
  }

  /// Rounds the given input value and casts the result to the given output value. The output value is limited
  /// to the given min / max bounds. By default these values are set to the numeric limits and simply prevent
  /// over- / underflows.
  /// \tparam OutputType Type of the output value to return (must be integral)
  /// \param value Value to be rounded
  /// \param min The result will be at least min
  /// \param max The result will be at most max
  /// \return the rounded and casted value
  template<typename OutputType, class = typename std::enable_if<std::is_integral<OutputType>::value>::type>
  static OutputType RoundAndLimit(const double value,
                                  OutputType min = std::numeric_limits<OutputType>::min(),
                                  OutputType max = std::numeric_limits<OutputType>::max()) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    } else {
      return Round<OutputType>(value);
    }
  }

  /// \see https://en.cppreference.com/w/cpp/types/numeric_limits/epsilon
  /// \param ulp Units in the last place
  template <typename T, typename = std::enable_if_t<std::numeric_limits<T>::is_integer == false>>
  static bool AlmostEquals(T a, T b, double ulp = 10.0) {
    const auto diff = std::abs(a - b);
    return diff <= std::numeric_limits<T>::epsilon() * std::abs(a + b) * ulp || diff < std::numeric_limits<T>::min();
  }
};
