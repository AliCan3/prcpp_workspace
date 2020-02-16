#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <client_endpoint.h>
#include <chat_client.h>
#include <user.h>
#include <logger.h>

#include "manager.h"

const std::vector<std::string> kMainCommands = {"chat", "exit", "users"};
const std::vector<std::string> kMainDescriptions = {"chat <id>   Start chatting with another user.",
                                                    "exit        Exit chat.",
                                                    "users       Show all available users and their <id>."};
const std::vector<std::string> kConversationCommands = {".show", ".stop"};
const std::vector<std::string> kConversationDescriptions = {".show   Show whole conversation.",
                                                            ".stop   Stop conversation and return to main menu."};

bool MainMode(const std::string& input, ChatClient* client, Manager* manager) {
  std::stringstream input_stream(input);
  std::string command;
  input_stream >> command;

  if (command == kMainCommands[0]) {
    size_t id;
    input_stream >> id;

    const auto list = client->GetAllConversationPartner();
    if (id >= list.size()) {
      Logger::LogError() << "No available conversation with <" << id << ">" << std::endl;
    } else {
      const auto partner = list[id];
      manager->EnterConversation(partner);
      Logger::LogInfo() << "Stop conversation mode by typing command " << kConversationCommands[1] << std::endl
                        << "or show all messages with " << kConversationCommands[0] << std::endl;
    }
  } else if (command == kMainCommands[1]) {
    Logger::LogInfo() << "I'm leaving. Good bye!" << std::endl;
    return true;
  } else if (command == kMainCommands[2]) {
    size_t index = 0;
    for (auto partner : client->GetAllConversationPartner()) {
      Logger::LogInfo() << index++ << ": " << partner.GetCompinedDescription() << std::endl;
    }
  } else if (command.empty() == false) {
    Logger::LogInfo() << "unknown command: " << command << std::endl;
    for (const std::string& s : kMainDescriptions) {
      Logger::LogInfo() << s << std::endl;
    }
  }

  return false;
}

void ConversionMode(const std::string& input, ChatClient* client, Manager* manager) {
  if (input == kConversationCommands[0]) {
    for (const auto& message : client->GetConversationFrom(manager->GetCurrentPartner())) {
      Logger::LogInfo() << message.GetFormattedText() << std::endl;
    }
  } else if (input == kConversationCommands[1]) {
    manager->LeaveConversation();
  } else if (input[0] == '.') {
    Logger::LogError() << "wrong command: " << input << std::endl;
    for (const std::string& s : kConversationDescriptions) {
      Logger::LogInfo() << s << std::endl;
    }
  } else if (input.empty() == false) {
    if (client->SendMessage(manager->GetCurrentPartner(), input) == false) {
      Logger::LogError() << "Failed to send message to: " << manager->GetCurrentPartner().GetCompinedDescription()
                         << std::endl;
    }
  }
}

int main() {
  // Logger::SetDebug(true);

  bool done = false;
  std::string input;

  Logger::LogInfo() << "Enter server IP [localhost]" << std::endl;
  std::getline(std::cin, input);
  auto ip_address = input;
  if (ip_address.empty()) {
    ip_address = "localhost";
  }

  Logger::LogInfo() << "Enter your name" << std::endl;
  std::getline(std::cin, input);
  auto name = input;
  if (name.empty()) {
    Logger::LogError() << "Name has to be non-empty" << std::endl;
    return EXIT_FAILURE;
  }

  Logger::LogInfo() << "Enter your phone number" << std::endl;
  std::getline(std::cin, input);
  auto phone = input;
  if (phone.empty()) {
    Logger::LogError() << "Phone number has to be non-empty" << std::endl;
    return EXIT_FAILURE;
  }

  User myself(name, phone);

  ClientEndpoint endpoint;
  auto connection = endpoint.Connect("ws://" + ip_address + ":9002");
  if (connection == nullptr) {
    Logger::LogError() << "Failed to connect" << std::endl;
    return EXIT_FAILURE;
  }

  ChatClient client(myself, connection);
  Manager manager;

  while (done == false) {
    switch (manager.GetCurrentMode()) {
      case Mode::kMain: Logger::LogInfo() << "[Main] ";
        std::getline(std::cin, input);
        done |= MainMode(input, &client, &manager);
        break;
      case Mode::kConversation:Logger::LogInfo() << "[" << manager.GetCurrentPartner().GetCompinedDescription() << "] ";
        std::getline(std::cin, input);
        ConversionMode(input, &client, &manager);
        break;
      default: Logger::LogInfo() << "[unknown_mode] ";
        assert(false);
        break;
    }
  }

  return EXIT_SUCCESS;
}
