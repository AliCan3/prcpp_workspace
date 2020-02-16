#pragma once

#include <string>
#include <user.h>

enum class Mode {
  kMain = 0,
  kConversation = 1,
};

class Manager {
 public:
  Manager();

  void EnterConversation(const User& partner);
  void LeaveConversation();

  User GetCurrentPartner() const;

  Mode GetCurrentMode() const;

 private:
  Mode current_mode_;
  User current_partner_;
};


