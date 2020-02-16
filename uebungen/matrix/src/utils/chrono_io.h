#pragma once

#include <chrono>
#include <iostream>

#include "utils/math.h"

namespace std {
namespace chrono {

constexpr inline const char* GetUnitString(std::chrono::nanoseconds) noexcept { return "ns"; }
constexpr inline const char* GetUnitString(std::chrono::microseconds) noexcept { return "us"; }
constexpr inline const char* GetUnitString(std::chrono::milliseconds) noexcept { return "ms"; }
constexpr inline const char* GetUnitString(std::chrono::seconds) noexcept { return "s"; }
constexpr inline const char* GetUnitString(std::chrono::minutes) noexcept { return "min"; }
constexpr inline const char* GetUnitString(std::chrono::hours) noexcept { return "h"; }

/// \brief Fallback if period is no well known ratio.
template<typename R, std::intmax_t N, std::intmax_t D>
std::string GetUnitString(std::chrono::duration<R, std::ratio<N, D>>) {
  constexpr auto gcd = Math::Gcd<N, D>::value;
  constexpr auto NN = N / gcd;
  constexpr auto DD = D / gcd;
  return "intervals of " + std::to_string(static_cast<double>(N) / D) +
      " (" + std::to_string(NN) + '/' + std::to_string(DD) + ") seconds each";
}

/// \brief Stream output operator for std::chrono::duration.
template<typename R, std::intmax_t N, std::intmax_t D>
std::ostream& operator<<(std::ostream& stm, std::chrono::duration<R, std::ratio<N, D>> d) {
  return stm << d.count() << GetUnitString(decltype(d){});
}

}   // namespace chrono
}   // namespace std
