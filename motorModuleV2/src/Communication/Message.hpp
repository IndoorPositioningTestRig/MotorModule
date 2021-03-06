#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <Arduino.h>
#include <ArduinoJson.h>

namespace Communication {

class Message {
public:
  Message(uint8_t sender, uint8_t target, uint8_t type, uint8_t length);
  Message() = default;

  uint8_t sender;
  uint8_t target;
  uint8_t type;
  uint8_t length;
  uint8_t data[255];
};

} // Communication
#endif // MESSAGE_HPP
