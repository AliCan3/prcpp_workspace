#pragma once

#include <set>
#include <string>
#include <memory>
#include <vector>

#include "connection.h"
#include "conversation.h"
#include "user.h"

class ChatClient {
 public:
  ChatClient(User myself, std::shared_ptr<Connection> connection);

  bool MessageHandler(const User& user, std::string* message);

  std::vector<User> GetAllConversationPartner() const;
  const Conversation& GetConversationFrom(const User& partner) const;
  bool SendMessage(const User& partner, const std::string& text);

 private:
};
