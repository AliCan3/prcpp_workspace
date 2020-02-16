#include "chat_server.h"
#include "logger.h"

int main() {
  Logger::SetDebug(true);
  ChatServer server;
  server.Run(9002);
}
