#include "chat_server.h"

#include <algorithm>
#include <iterator>

#include "serializer.h"
#include "logger.h"

ChatServer::ChatServer()
    : ServerBase() {
}

void ChatServer::OpenHandler(ConnectionHandle hdl) {
  Logger::LogDebug() << "[Server] Connection accepted" << std::endl;
}

void ChatServer::ConnectionHandler(ConnectionHandle hdl, const std::string& message) {
  const auto type = Serializer::EvaluateMessageType(message);
  if (type == Serializer::MessageType::kUser) {
    User new_user;
    if (Serializer::ParseUserMessage(message, &new_user) == false) {
      Logger::LogDebug() << "[Server] Failed to parse message: " << Serializer::GetTypeString(type) << std::endl;
      return;
    }

    SubscribeUser(new_user);
    DisconnectUser(new_user);

    auto connection = std::make_shared<Connection>(new_user, endpoint_.get_con_from_hdl(hdl));
    connection->SetReceiveHandler([this](const User& user, std::string* message) {
      return MessageHandler(user, message);
    });
    connection->SetCloseHandler([this](const User& user) { DisconnectUser(user); });
    connections_.emplace_back(std::move(connection));

    Logger::LogDebug() << "[Server] Connection successfull opened for user: " << new_user.GetCompinedDescription()
                       << std::endl;
    SendSubscriberListUpdate();
  } else {
    Logger::LogError() << "[Server] Unknown telegram" << std::endl;
  }
}

bool ChatServer::MessageHandler(const User& user, std::string* message) {
  const auto type = Serializer::EvaluateMessageType(*message);
  if (type == Serializer::MessageType::kConversationUpdate) {
    Conversation conversation;
    if (Serializer::ParseConversationUpdateMessage(*message, &conversation) == false) {
      Logger::LogError() << "[Server] Failed to parse message: " << Serializer::GetTypeString(type) << std::endl;
      return false;
    }
    Logger::LogDebug() << "[Server] Received conversation update from: " << user.GetCompinedDescription() << std::endl;
    UpdateConversation(user, conversation);
    return false;
  } else {
    Logger::LogError() << "[Server] Unknown telegram" << std::endl;
  }

  return false;
}

void ChatServer::DisconnectUser(const User& user) {
  const auto pred = [user](const ConnectionPtr& conn) {
    return conn->GetUser() == user;
  };
  connections_.erase(std::remove_if(connections_.begin(), connections_.end(), pred), connections_.end());
}

std::vector<Conversation> ChatServer::GetAllConversationsOf(const User& requester) const {
  std::vector<Conversation> result;
  std::copy_if(conversations_.cbegin(),
               conversations_.cend(),
               std::back_inserter(result),
               [requester](const auto& conversation) {
                 return conversation.IsParticipant(requester);
               });

  return result;
}

void ChatServer::SubscribeUser(const User& subscriber) {
  for (const auto& user : users_) {
    if (user.GetPhoneNumber() == subscriber.GetPhoneNumber()) {
      return;
    }
  }

  // add all possible new conversations
  for (const auto& partner : users_) {
    conversations_.emplace_back(subscriber, partner);
  }

  users_.insert(subscriber);
}

void ChatServer::SendSubscriberListUpdate() {
  for (auto connection : connections_) {
    for (const auto& conversation : GetAllConversationsOf(connection->GetUser())) {
      const auto message = Serializer::SerializeConversationUpdateMessage(conversation);
      if (connection->Send(message) == false) {
        Logger::LogError() << "[Server] Failed to send subscriber update to: "
                           << connection->GetUser().GetCompinedDescription() << std::endl;
        break;
      }
    }
    Logger::LogDebug() << "[Server] Sent subscriber list update to: " << connection->GetUser().GetCompinedDescription()
                       << std::endl;
  }
}

void ChatServer::SendConversationUpdate(const User& sender, const Conversation& updated_conversation) {
  for (auto connection : connections_) {
    if (updated_conversation.IsParticipant(connection->GetUser())
        && connection->GetUser().GetPhoneNumber() != sender.GetPhoneNumber()) {
      const auto message = Serializer::SerializeConversationUpdateMessage(updated_conversation);
      if (connection->Send(message)) {
        Logger::LogDebug() << "[Server] Sent conversation update to: " << connection->GetUser().GetCompinedDescription()
                           << std::endl;
      } else {
        Logger::LogError() << "[Server] Failed to send conversation update to: "
                           << connection->GetUser().GetCompinedDescription() << std::endl;
      }
    }
  }
}

void ChatServer::UpdateConversation(const User& sender, const Conversation& updated_conversation) {
  for (auto& conv : conversations_) {
    if (conv.HasSameParticipants(updated_conversation)) {
      conv = updated_conversation;
    }
  }
  SendConversationUpdate(sender, updated_conversation);
}
