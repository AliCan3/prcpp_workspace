#pragma once

#include <algorithm>
#include <chrono>

template<class Duration>
class Stopwatch {
  static_assert(std::chrono::__is_duration<Duration>::value);

 public:
  typedef std::chrono::high_resolution_clock Clock;

  Stopwatch()
      : elapsed_time_(0) {
    if (initialized_ == false) {
      overhead_ = CalculateOverhead();
      initialized_ = true;
    }

    Start();
  }

  void Start() {
    start_timestamp_ = Clock::now();
  }

  const Stopwatch& Stop() {
    const Clock::time_point current_timestamp = Clock::now();
    const Duration difference = std::chrono::duration_cast<Duration>(current_timestamp - start_timestamp_);
    elapsed_time_ = std::max(Duration(0), difference - overhead_);
    return *this;
  }

  Duration GetElapsedTime() const {
    return elapsed_time_;
  }

 private:
  Duration CalculateOverhead() {
    const size_t OverheadCalculationLoopCount = 1000;
    const Clock::time_point start_overhead_measuring = Clock::now();
    for (size_t i = 0; i < OverheadCalculationLoopCount; ++i) {
      Start();
      Stop();
    }
    const Duration overhead = std::chrono::duration_cast<Duration>(Clock::now() - start_overhead_measuring);
    return overhead / OverheadCalculationLoopCount;
  }

  static Duration overhead_;
  static bool initialized_;
  Clock::time_point start_timestamp_;
  Duration elapsed_time_;
};

template<class Duration>
Duration Stopwatch<Duration>::overhead_ = Duration(0);

template<class Duration>
bool Stopwatch<Duration>::initialized_ = false;
