#pragma once

#include <cstdint>

#include <memory>
#include <string>
#include <thread>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/client.hpp>

#include "connection.h"

class ClientEndpoint {
 public:
  using AsioClient = websocketpp::client<websocketpp::config::asio>;
  using MessagePtr = AsioClient::message_ptr;
  using ConnectionPtr = AsioClient::connection_ptr;
  using ConnectionHandle = websocketpp::connection_hdl;

  ClientEndpoint();
  virtual ~ClientEndpoint();

  std::shared_ptr<Connection> Connect(const std::string& uri);

 protected:
  AsioClient endpoint_;
  std::thread thread_;
};
