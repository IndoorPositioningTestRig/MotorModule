#include "Message.hpp"

Message::Message(uint8_t sender, uint8_t target, uint8_t type, uint8_t length) :
  sender(sender),
  target(target),
  type(type),
  length(length)
{
}
