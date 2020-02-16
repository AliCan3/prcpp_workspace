#pragma once

#include "server_base.h"

#include <memory>
#include <string>
#include <set>
#include <vector>

#include "connection.h"
#include "conversation.h"
#include "user.h"

class ChatServer : public ServerBase {
 public:
  ChatServer();

  void OpenHandler(ConnectionHandle hdl) override;
  void ConnectionHandler(ConnectionHandle hdl, const std::string& message) override;
  bool MessageHandler(const User& user, std::string* message);
  void DisconnectUser(const User& user);

  std::vector<Conversation> GetAllConversationsOf(const User& requester) const;

 private:
  void SubscribeUser(const User& user);
  void SendSubscriberListUpdate();
  void SendConversationUpdate(const User& sender, const Conversation& updated_conversation);
  void UpdateConversation(const User& sender, const Conversation& updated_conversation);

  using ConnectionPtr = std::shared_ptr<Connection>;
  std::vector<ConnectionPtr> connections_;
  std::set<User> users_;
  std::vector<Conversation> conversations_;
};
