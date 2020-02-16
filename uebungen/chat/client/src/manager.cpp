#include "manager.h"

Manager::Manager()
    : current_mode_(Mode::kMain) {}

void Manager::EnterConversation(const User& partner) {
  current_partner_ = partner;
  current_mode_ = Mode::kConversation;
}

void Manager::LeaveConversation() {
  current_mode_ = Mode::kMain;
}

User Manager::GetCurrentPartner() const {
  return current_partner_;
}

Mode Manager::GetCurrentMode() const {
  return current_mode_;
}
