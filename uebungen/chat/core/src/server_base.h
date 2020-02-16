#pragma once

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include <string>

class ServerBase {
 public:
  using AsioServer = websocketpp::server<websocketpp::config::asio>;
  using MessagePtr = AsioServer::message_ptr;
  using ConnectionHandle = websocketpp::connection_hdl;

  ServerBase();
  virtual ~ServerBase();

  /// \brief This method starts internal processing and blocks forever.
  /// \param port The port to listen for incoming messages.
  void Run(std::uint16_t port);

  void Stop();

  virtual void OpenHandler(ConnectionHandle hdl) = 0;
  virtual void ConnectionHandler(ConnectionHandle hdl, const std::string& message) = 0;

 protected:
  AsioServer endpoint_;
};
