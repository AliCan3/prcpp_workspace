#include <catch2/catch.hpp>

#include <string>
#include <vector>

#include "conversation.h"
#include "user.h"
#include "serializer.h"

TEST_CASE("Serializer Test") {
  SECTION("MessageTypeSerialize") {
    REQUIRE(Serializer::GetTypeString(Serializer::MessageType::kUnknown) == "kUnknown");
    REQUIRE(Serializer::GetTypeString(Serializer::MessageType::kUser) == "kUser");
    REQUIRE(Serializer::GetTypeString(Serializer::MessageType::kConversationUpdate) == "kConversationUpdate");
  }

  SECTION("MessageTypeParse") {
    REQUIRE(Serializer::EvaluateMessageType("kUnknown") == Serializer::MessageType::kUnknown);
    REQUIRE(Serializer::EvaluateMessageType("kUser") == Serializer::MessageType::kUser);
    REQUIRE(Serializer::EvaluateMessageType("kConversationUpdate") == Serializer::MessageType::kConversationUpdate);
    REQUIRE(Serializer::EvaluateMessageType("bla") == Serializer::MessageType::kUnknown);
  }

  SECTION("MessageTypeParseWithTrailingStuff") {
    REQUIRE(Serializer::EvaluateMessageType("kUnknown|bla") == Serializer::MessageType::kUnknown);
    REQUIRE(Serializer::EvaluateMessageType("kUser|bla") == Serializer::MessageType::kUser);
    REQUIRE(Serializer::EvaluateMessageType("kConversationUpdate|bla") == Serializer::MessageType::kConversationUpdate);
  }

  SECTION("UserMessageSerialize") {
    REQUIRE(Serializer::SerializeUserMessage(User("anna", "0791111111")) == "kUser|anna|0791111111|");
    REQUIRE(Serializer::SerializeUserMessage(User("anna", "1")) == "kUser|anna|1|");
    REQUIRE(Serializer::SerializeUserMessage(User("anna", "")) == "kUser|anna||");
    REQUIRE(Serializer::SerializeUserMessage(User("", "")) == "kUser|||");
    REQUIRE(Serializer::SerializeUserMessage(User("", "0791111111")) == "kUser||0791111111|");
  }

  SECTION("UserMessageParse") {
    User expected;
    User parsed;

    expected = User("anna", "0791111111");
    REQUIRE(Serializer::ParseUserMessage("kUser|anna|0791111111|", &parsed));
    REQUIRE(expected == parsed);

    expected = User("anna", "1");
    REQUIRE(Serializer::ParseUserMessage("kUser|anna|1|", &parsed));
    REQUIRE(expected == parsed);

    expected = User("anna", "");
    REQUIRE(Serializer::ParseUserMessage("kUser|anna||", &parsed));
    REQUIRE(expected == parsed);

    expected = User("", "");
    REQUIRE(Serializer::ParseUserMessage("kUser|||", &parsed));
    REQUIRE(expected == parsed);

    expected = User("", "0791111111");
    REQUIRE(Serializer::ParseUserMessage("kUser||0791111111|", &parsed));
    REQUIRE(expected == parsed);
  }

  SECTION("UserMessageParseFails") {
    User parsed;
    REQUIRE(Serializer::ParseUserMessage("kUser|anna|0791111111", &parsed) == false);
    REQUIRE(Serializer::ParseUserMessage("kConversationUpdate|anna|0791111111|", &parsed) == false);
  }

  SECTION("UserMessageParseWithTrailingStuff") {
    User parsed;
    REQUIRE(Serializer::ParseUserMessage("kUser|anna|0791111111|stuff", &parsed));
    REQUIRE(User("anna", "0791111111") == parsed);
  }

  SECTION("UserMessageSerializeAndParse") {
    User output("Ich", "0023451");

    const auto message = Serializer::SerializeUserMessage(output);
    REQUIRE(Serializer::EvaluateMessageType(message) == Serializer::MessageType::kUser);

    User input;
    REQUIRE(Serializer::ParseUserMessage(message, &input));
    REQUIRE(output == input);
  }

  SECTION("ConversationUpdateMessageSerialize") {
    User a("a", "1");
    User b("b", "2");
    Conversation output(a, b);

    REQUIRE(Serializer::SerializeConversationUpdateMessage(output) == "kConversationUpdate|a|1|b|2|");

    output.AddMessage("text_a");
    const auto first_message = *output.begin();
    const auto count1 = first_message.GetTimestamp().time_since_epoch().count();
    const auto conversation1 = std::string("text_a|a|1|") + std::to_string(count1) + "|";
    const auto result1 = Serializer::SerializeConversationUpdateMessage(output);
    REQUIRE(result1 == std::string("kConversationUpdate|a|1|b|2|") + conversation1);

    output.EnsureCorrectMyself(b);
    output.AddMessage("text_b");
    const auto second_message = *(++(output.begin()));
    const auto count2 = second_message.GetTimestamp().time_since_epoch().count();
    const auto conversation2 = std::string("text_b|b|2|") + std::to_string(count2) + "|";
    const auto result2 = Serializer::SerializeConversationUpdateMessage(output);
    const auto expected2a = std::string("kConversationUpdate|b|2|a|1|")
        + conversation1 + conversation2;
    const auto expected2b = std::string("kConversationUpdate|b|2|a|1|")
        + conversation2 + conversation1;
    REQUIRE((result2 == expected2a || result2 == expected2b));
  }

  SECTION("ConversationUpdateMessageParse") {
    User a("a", "1");
    User b("b", "2");

    Conversation parsed;

    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|", &parsed));
    REQUIRE(parsed.GetMyself() == a);
    REQUIRE(parsed.GetPartner() == b);
    REQUIRE(parsed.size() == 0);

    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10|", &parsed));
    REQUIRE(parsed.GetMyself() == a);
    REQUIRE(parsed.GetPartner() == b);
    REQUIRE(parsed.size() == 1);
    const auto message1 = *parsed.begin();
    REQUIRE(message1.GetSender() == a);
    REQUIRE(message1.GetText() == "text_a");
    REQUIRE(message1.GetTimestamp().time_since_epoch().count() == 10);

    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10|text_b|b|2|20|",
                                                       &parsed));
    REQUIRE(parsed.GetMyself() == a);
    REQUIRE(parsed.GetPartner() == b);
    REQUIRE(parsed.size() == 2);
    const auto message2 = *(++parsed.begin());
    REQUIRE(message2.GetSender() == b);
    REQUIRE(message2.GetText() == "text_b");
    REQUIRE(message2.GetTimestamp().time_since_epoch().count() == 20);
  }

  SECTION("ConversationUpdateMessageParseFails") {
    Conversation parsed;
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|", &parsed) == false);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2", &parsed) == false);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kUser|a|1|b|2|", &parsed) == false);

    // not parseble timestamp
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10|text_b|b|2|aasd|",
                                                       &parsed) == false);
  }

  SECTION("ConversationUpdateMessageParseOnlyPartialMessages") {
    Conversation parsed;

    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10", &parsed));
    REQUIRE(parsed.size() == 0);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|", &parsed));
    REQUIRE(parsed.size() == 0);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|", &parsed));
    REQUIRE(parsed.size() == 0);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|", &parsed));
    REQUIRE(parsed.size() == 0);

    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10|text_b|b|2|20",
                                                       &parsed));
    REQUIRE(parsed.size() == 1);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10|text_b|b|2|",
                                                       &parsed));
    REQUIRE(parsed.size() == 1);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10|text_b|b|", &parsed));
    REQUIRE(parsed.size() == 1);
    REQUIRE(Serializer::ParseConversationUpdateMessage("kConversationUpdate|a|1|b|2|text_a|a|1|10|text_b|", &parsed));
    REQUIRE(parsed.size() == 1);
  }

  SECTION("ConversationUpdateMessageSerializeAndParse") {
    Conversation output(User("Ich", "001"), User("James", "007"));
    output.AddMessage("first");
    output.AddMessage("second");
    output.AddMessage("third");

    const auto message = Serializer::SerializeConversationUpdateMessage(output);
    REQUIRE(Serializer::EvaluateMessageType(message) == Serializer::MessageType::kConversationUpdate);

    Conversation input;
    REQUIRE(Serializer::ParseConversationUpdateMessage(message, &input));
    REQUIRE(output == input);
  }
}
