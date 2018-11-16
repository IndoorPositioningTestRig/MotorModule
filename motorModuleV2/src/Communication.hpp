#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

//#include <vector>
#include <Arduino.h>

class Communication {
public:
  Communication();
  void init();
  void listen();
  // void write(uint8_t sender, uint8_t target, uint8_t type, std::vector<uint8_t> message);
  void write_c(uint8_t sender, uint8_t target, uint8_t type, uint8_t * message, size_t messageLength);
private:
  bool _isInitialised;
  uint8_t _buffer[256];
  void decodeMessage();
};

#endif // COMMUNICATION_HPP
