#pragma once

#include <iostream>
#include <sstream>

class Logger {
 public:
  static std::ostream& LogError();
  static std::ostream& LogInfo();
  static std::ostream& LogDebug();
  static void SetDebug(bool enable);

 private:
  static bool debug_enabled_;
  static std::ostream* dump_stream_;
};
