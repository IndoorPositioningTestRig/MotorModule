#ifndef COMMUNICATION_HPP
#define COMMUNICATION_HPP

#include <SoftwareSerial.h>
//#include <vector>

class Communication {
public:
  Communication();
  void init();
  void listen();
  void write();

  void printBuffer();
private:
  //std::vector<int32_t> _buffer;
  SoftwareSerial _rsSerial;
  bool _isInitialised;
};

#endif // COMMUNICATION_HPP
