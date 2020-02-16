#include "client_endpoint.h"

#include <atomic>

#include "logger.h"

ClientEndpoint::ClientEndpoint() {
  endpoint_.clear_access_channels(websocketpp::log::alevel::all);
  endpoint_.clear_error_channels(websocketpp::log::elevel::all);
  endpoint_.init_asio();

  endpoint_.start_perpetual();
  thread_ = std::thread(&AsioClient::run, &endpoint_);
}

ClientEndpoint::~ClientEndpoint() {
  endpoint_.stop_perpetual();
  Logger::LogDebug() << "Closing ClientEndpoint. Trying to stop thread..." << std::endl;
  thread_.join();
}

std::shared_ptr<Connection> ClientEndpoint::Connect(const std::string& uri) {
  websocketpp::lib::error_code ec;
  auto connection = endpoint_.get_connection(uri, ec);
  if (ec) {
    Logger::LogError() << "[Client] Connect initialization error: " << ec.message() << std::endl;
    return nullptr;
  }

  std::atomic_bool connected = false;

  connection->set_open_handler([this, &connected, uri](ConnectionHandle hdl) {
    auto con = endpoint_.get_con_from_hdl(hdl);
    Logger::LogDebug() << "[Client] Connected to: " << uri << std::endl;
    connected = true;
  });
  connection->set_fail_handler([this](ConnectionHandle hdl) {
    auto con = endpoint_.get_con_from_hdl(hdl);
    Logger::LogError() << "[Client] Failed to connect: " << con->get_ec().message() << std::endl;
  });

  endpoint_.connect(connection);
  while (connected == false) {}

  return std::make_shared<Connection>(connection);
}
