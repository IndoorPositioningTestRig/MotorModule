#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include "../Pins.hpp"
#include <Arduino.h>
#include "Message.hpp"

namespace Communication {
  
class TYPES {
  static const uint8_t REQUEST = 1;
  static const uint8_t COMMAND = 2;
  static const uint8_t RESPONSE = 3;
};

class Communicator {
public:
  Communicator();
  void init(int mode = RS485_READ);
  bool receive(Message& message);
  void write_c(uint8_t sender, uint8_t target, uint8_t type, uint8_t * message, size_t messageLength);
private:
  int _mode;

  Message decodeMessage();
  void setMode(int mode = RS485_READ);
};

}; // namespace Communication

#endif // COMMUNICATOR_HPP
