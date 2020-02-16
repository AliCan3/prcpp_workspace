#include "message.h"

#include <sstream>

Message::Message()
    : Message(User(), "") {}

Message::Message(const User& sender, const std::string& text, const TimePoint& timestamp)
    : text_(text), sender_(sender), timestamp_(timestamp) {}

std::string Message::GetText() const {
  return text_;
}

std::string Message::GetFormattedText() const {
  std::stringstream stream;
  stream << "(" << GetTimestampString() << ")[" << sender_.GetCompinedDescription() << "] " << GetText();
  return stream.str();
}

User Message::GetSender() const {
  return sender_;
}

Message::TimePoint Message::GetTimestamp() const {
  return timestamp_;
}

std::string Message::GetTimestampString() const {
  auto tp = std::chrono::system_clock::to_time_t(timestamp_);
  std::tm ptm;
  localtime_r(&tp, &ptm);
  constexpr std::size_t kBufferSize = 32;
  char buffer[kBufferSize];
  std::strftime(buffer, kBufferSize, "%H:%M:%S", &ptm);
  return buffer;
}

bool Message::operator==(const Message& rhs) const noexcept {
  return text_ == rhs.text_
      && sender_ == rhs.sender_
      && timestamp_ == rhs.timestamp_;
}

bool Message::operator<(const Message& rhs) const noexcept {
  if (timestamp_ != rhs.timestamp_) {
    return timestamp_ < rhs.timestamp_;
  }
  return text_ < rhs.text_;
}
