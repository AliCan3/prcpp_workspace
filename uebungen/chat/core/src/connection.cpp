#include "connection.h"

#include "serializer.h"
#include "logger.h"

using MessagePtr = websocketpp::config::asio::message_type::ptr;

Connection::Connection(ConnectionPtr ptr)
    : Connection(User("Client", ""), ptr) {}

Connection::Connection(const User& user, ConnectionPtr ptr)
    : user_(user), connection_ptr_(ptr) {
  connection_ptr_->set_message_handler([user](ConnectionHandle hdl, MessagePtr message) {
    const auto opcode = message->get_opcode();
    Logger::LogError() << "[" << user.GetCompinedDescription() << "] Got message without registered handler: "
                       << opcode << std::endl;
  });
  connection_ptr_->set_close_handler([user](ConnectionHandle hdl) {
    Logger::LogDebug() << "[" << user.GetCompinedDescription() << "] Closed from remote" << std::endl;
  });
}

Connection::Connection(const User& user, ConnectionPtr ptr, ReceiveHandler handler)
    : Connection(user, ptr) {
  SetReceiveHandler(handler);
}

Connection::~Connection() {
  using WebSockState = websocketpp::session::state::value;
  if (connection_ptr_->get_state() == WebSockState::open || connection_ptr_->get_state() == WebSockState::connecting) {
    connection_ptr_->close(websocketpp::close::status::normal, "closing client");
  }
}

void Connection::SetReceiveHandler(ReceiveHandler handler) {
  connection_ptr_->set_message_handler([this, handler](ConnectionHandle hdl, MessagePtr message) {
    const auto opcode = message->get_opcode();
    if (opcode != websocketpp::frame::opcode::binary) {
      Logger::LogError() << "[" << user_.GetCompinedDescription() << "] Got unexpected message type: " << opcode
                         << std::endl;
      return;
    }

    std::string payload = message->get_payload();
    const auto type = Serializer::EvaluateMessageType(payload);

    Logger::LogDebug() << "[" << user_.GetCompinedDescription() << "] Received telegram: "
                       << Serializer::GetTypeString(type) << std::endl;
    const bool response = handler(user_, &payload);

    if (response) {
      if (Send(payload) == false) {
        Logger::LogError() << "[" << user_.GetCompinedDescription() << "] Error sending response: "
                           << Serializer::GetTypeString(type) << std::endl;
      }
      Logger::LogDebug() << "[" << user_.GetCompinedDescription() << "] Sent response: "
                         << Serializer::GetTypeString(type) << std::endl;
    }
  });
}

void Connection::SetCloseHandler(CloseHandler handler) {
  const auto user = user_;
  connection_ptr_->set_close_handler([user, handler](ConnectionHandle hdl) {
    Logger::LogDebug() << "[" << user.GetCompinedDescription() << "] Connection closed. Calling handler" << std::endl;
    handler(user);
  });
}

bool Connection::Send(const std::string& message) {
  const auto error_code = connection_ptr_->send(message, websocketpp::frame::opcode::binary);
  if (error_code) {
    Logger::LogError() << "[" << user_.GetCompinedDescription() << "] Error sending message: " << error_code.message()
                       << std::endl;
    return false;
  }
  return true;
}

const User& Connection::GetUser() const {
  return user_;
}
