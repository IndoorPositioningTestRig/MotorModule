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
  digitalWrite(9, HIGH);

  while(_rsSerial.available()) {
    //int32_t command = _rsSerial.read();
    char * buffer;
    Serial1.readBytesUntil('\n', buffer, 100);
    //_buffer.emplace_back(command);
    //Serial.println(command);
    Serial.println(buffer);
  }
  if(_buffer.size() > 0){
    printBuffer();
  }
}

void Communication::write(){
  _rsSerial.write(HIGH);
 // _rsSerial.flush();
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
