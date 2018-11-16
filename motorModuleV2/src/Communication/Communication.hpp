#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include "../Pins.hpp"
#include <Arduino.h>
#include "Message.hpp"

class Communication {
public:
  Communication();
  void init(int mode = RS485_READ);
  bool receive(Message& message);
  void write_c(uint8_t sender, uint8_t target, uint8_t type, uint8_t * message, size_t messageLength);
private:
  int _mode;

  Message decodeMessage();
  void setMode(int mode = RS485_READ);
};

#endif // COMMUNICATION_HPP
