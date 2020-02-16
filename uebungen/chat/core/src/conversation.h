#pragma once

#include <set>

#include "message.h"
#include "user.h"

class Serializer;

class Conversation {
 public:
  using MessageList = std::set<Message>;

  Conversation();
  Conversation(const User& myself, const User& partner);

  void AddMessage(const std::string& text);
  void AddMessage(const Message& message);

  size_t size() const { return messages_.size(); }
  auto begin() { return messages_.begin(); }
  auto end() { return messages_.end(); }
  auto begin() const { return messages_.cbegin(); }
  auto end() const { return messages_.cend(); }
  auto cbegin() const { return messages_.cbegin(); }
  auto cend() const { return messages_.cend(); }

  Message GetNewestMessage() const;

  bool HasSameParticipants(const Conversation& conversation) const;
  bool IsParticipant(const User& user) const;
  void EnsureCorrectMyself(const User& myself);
  User GetMyself() const;
  User GetPartner() const;

  bool operator==(const Conversation& rhs) const noexcept;
  bool operator!=(const Conversation& rhs) const noexcept { return !(*this == rhs); };

 private:
  void SwapUsers();

  std::set<Message> messages_;
  User myself_;
  User partner_;
};
