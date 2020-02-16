#pragma once

#include <functional>
#include <string>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/connection.hpp>

#include "user.h"

class Connection {
 public:
  using ConnectionPtr = websocketpp::connection<websocketpp::config::asio>::ptr;
  using ConnectionHandle = websocketpp::connection_hdl;
  using ReceiveHandler = std::function<bool(const User&, std::string*)>;
  using CloseHandler = std::function<void(const User&)>;

  explicit Connection(ConnectionPtr ptr);
  Connection(const User& user, ConnectionPtr ptr);
  Connection(const User& user, ConnectionPtr ptr, ReceiveHandler handler);
  ~Connection();

  void SetReceiveHandler(ReceiveHandler handler);
  void SetCloseHandler(CloseHandler handler);

  bool Send(const std::string& message);

  const User& GetUser() const;

 private:
  User user_;
  ConnectionPtr connection_ptr_;
};
