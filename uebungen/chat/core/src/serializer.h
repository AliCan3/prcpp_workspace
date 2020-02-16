#pragma once

#include <string>

#include "user.h"
#include "conversation.h"

class Serializer {
 public:
  Serializer() = delete;
  ~Serializer() = delete;

  enum class MessageType {
    kUnknown,
    kUser,
    kConversationUpdate,
  };

  static constexpr char kTokenSeparator = '|';

  static std::string GetTypeString(MessageType type);
  static MessageType EvaluateMessageType(const std::string& input);

  static std::string SerializeUserMessage(const User& user);
  static bool ParseUserMessage(const std::string& input, User* user);

  static std::string SerializeConversationUpdateMessage(const Conversation& conversation);
  static bool ParseConversationUpdateMessage(const std::string& input, Conversation* conversation);

 private:
};
