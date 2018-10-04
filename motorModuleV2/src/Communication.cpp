#include "Communication.hpp"

#include <SoftwareSerial.h>
#include "Pins.hpp"

Communication::Communication() :
  _rsSerial(PIN_RS485_A, PIN_RS485_B),
  _isInitialised(false)
{
  _buffer = {};
}

void Communication::init() {
  _rsSerial.begin(9600);
  _isInitialised = true;
}

void Communication::listen() {
  if (!_isInitialised) {
    init();
  }

  while(_rsSerial.available()) {
    int32_t command = _rsSerial.read();
    _buffer.emplace_back(command);
  }
  printBuffer();
}

void Communication::printBuffer() {
  // int32 buffer
  Serial.println("Buffer - int32_t: [");
  for (int32_t i : _buffer) {
    Serial.print(i);
    Serial.print(" ");
  }
  Serial.print("]\n");
  
  // Char buffer
  Serial.println("Buffer - char: [");  
  for (int32_t i : _buffer) {
    Serial.print((char)i);
    Serial.print(" ");
  }
  Serial.print("]\n");
}
