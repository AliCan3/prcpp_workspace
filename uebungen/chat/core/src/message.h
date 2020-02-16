#pragma once

#include <chrono>
#include <string>
#include <ctime>

#include "user.h"

class Serializer;

class Message {
 public:
  using TimePoint = std::chrono::system_clock::time_point;

  Message();

  Message(const Message& other) = default;
  Message& operator=(const Message& other) = default;

  Message(const User& sender, const std::string& text, const TimePoint& timestamp = std::chrono::system_clock::now());

  std::string GetText() const;
  std::string GetFormattedText() const;
  User GetSender() const;
  TimePoint GetTimestamp() const;
  std::string GetTimestampString() const;

  bool operator==(const Message& rhs) const noexcept;
  bool operator!=(const Message& rhs) const noexcept { return !(*this == rhs); };
  bool operator<(const Message& rhs) const noexcept;

 private:
  std::string text_;
  User sender_;
  TimePoint timestamp_;
};
