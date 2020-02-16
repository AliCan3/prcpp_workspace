#include "server_base.h"

#include "logger.h"

ServerBase::ServerBase() {
  endpoint_.clear_error_channels(websocketpp::log::elevel::all);
  endpoint_.clear_access_channels(websocketpp::log::alevel::all);
  endpoint_.init_asio();

  endpoint_.set_open_handler([this](ConnectionHandle hdl) {
    OpenHandler(hdl);
  });
  endpoint_.set_message_handler([this](ConnectionHandle hdl, MessagePtr message) {
    const auto opcode = message->get_opcode();
    if (opcode != websocketpp::frame::opcode::binary) {
      Logger::LogError() << "[Server] Got unexpected message type: " << opcode << std::endl;
      return;
    }

    ConnectionHandler(hdl, message->get_payload());
  });
}

ServerBase::~ServerBase() {
  Stop();
}

void ServerBase::Run(std::uint16_t port) {
  endpoint_.listen(port);

  // queues a connection accept operation
  endpoint_.start_accept();

  // start the asio io_service run loop
  endpoint_.run();
}

void ServerBase::Stop() {
  endpoint_.stop();
}
