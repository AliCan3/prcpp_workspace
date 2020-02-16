#pragma once

#include <string>

class User {
 public:
  User();
  User(const std::string& name, const std::string& phone_number);

  std::string GetName() const;
  std::string GetPhoneNumber() const;
  std::string GetCompinedDescription() const;

  bool operator==(const User& rhs) const noexcept;
  bool operator!=(const User& rhs) const noexcept { return !(*this == rhs); };
  bool operator<(const User& rhs) const noexcept;

 private:
  std::string name_;
  std::string phone_number_;
};
