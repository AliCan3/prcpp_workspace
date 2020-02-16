#include "conversation.h"

#include <cassert>
#include <algorithm>
#include <iterator>

Conversation::Conversation() {}
Conversation::Conversation(const User& myself, const User& partner)
    : myself_(myself), partner_(partner) {}

void Conversation::AddMessage(const std::string& text) {
  messages_.emplace(myself_, text);
}

void Conversation::AddMessage(const Message& message) {
  messages_.insert(message);
}

Message Conversation::GetNewestMessage() const {
  return *messages_.rbegin();
}

bool Conversation::HasSameParticipants(const Conversation& conversation) const {
  const auto conv_myself_phone = conversation.GetMyself().GetPhoneNumber();
  const auto conv_partner_phone = conversation.GetPartner().GetPhoneNumber();
  const auto myself_phone = myself_.GetPhoneNumber();
  const auto partner_phone = partner_.GetPhoneNumber();
  return (conv_myself_phone == myself_phone && conv_partner_phone == partner_phone)
      || (conv_myself_phone == partner_phone && conv_partner_phone == myself_phone);
}

bool Conversation::IsParticipant(const User& user) const {
  return myself_.GetPhoneNumber() == user.GetPhoneNumber()
      || partner_.GetPhoneNumber() == user.GetPhoneNumber();
}

void Conversation::EnsureCorrectMyself(const User& myself) {
  if (myself.GetPhoneNumber() != myself_.GetPhoneNumber()) {
    assert(myself.GetPhoneNumber() == partner_.GetPhoneNumber());
    SwapUsers();
    myself_ = myself;
  }
}

User Conversation::GetMyself() const {
  return myself_;
}

User Conversation::GetPartner() const {
  return partner_;
}

bool Conversation::operator==(const Conversation& rhs) const noexcept {
  if (messages_ != rhs.messages_) {
    return false;
  }

  return (myself_ == rhs.myself_ && partner_ == rhs.partner_)
      || (myself_ == rhs.partner_ && partner_ == rhs.myself_);
}

void Conversation::SwapUsers() {
  std::swap(myself_, partner_);
}
