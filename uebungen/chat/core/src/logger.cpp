#include "logger.h"

#include <cassert>

bool Logger::debug_enabled_;
std::ostream* Logger::dump_stream_;

std::ostream& Logger::LogError() {
  return std::cerr;
}

std::ostream& Logger::LogInfo() {
  return std::cout;
}

std::ostream& Logger::LogDebug() {
  if (dump_stream_ == nullptr) {
    dump_stream_ = new std::stringstream(std::ios_base::out);
    assert(dump_stream_);
  }
  if (debug_enabled_) {
    return std::cout;
  } else {
    dump_stream_->clear();
    return *dump_stream_;
  }
}

void Logger::SetDebug(bool enable) {
  debug_enabled_ = enable;
}
