#include "user.h"

#include "conversation.h"

User::User() {}

User::User(const std::string& name, const std::string& phone_number)
    : name_(name), phone_number_(phone_number) {}

std::string User::GetName() const {
  return name_;
}

std::string User::GetPhoneNumber() const {
  return phone_number_;
}

std::string User::GetCompinedDescription() const {
  return name_ + "(" + phone_number_ + ")";
}

bool User::operator==(const User& rhs) const noexcept {
  return phone_number_ == rhs.phone_number_
      && name_ == rhs.name_;
}

bool User::operator<(const User& rhs) const noexcept {
  return phone_number_ < rhs.phone_number_;
}
