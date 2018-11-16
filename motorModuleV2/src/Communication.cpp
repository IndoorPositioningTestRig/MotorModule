namespace std {
  void __throw_length_error(char const*) {
  }
}

#include "Communication.hpp"
#include "Pins.hpp"
#include <Arduino.h>
//#include <vector.h>

Communication::Communication() : _isInitialised(false)
{
}

void Communication::init()
{
  Serial1.begin(9600);
  _isInitialised = true;

  pinMode(PIN_RS485_READ_WRITE, OUTPUT);
  digitalWrite(PIN_RS485_READ_WRITE, RS485_READ);
}

void Communication::listen()
{
  if (!_isInitialised)
  {
    init();
  }
  digitalWrite(PIN_RS485_READ_WRITE, RS485_READ);

  while (Serial1.available())
  {
    byte input = Serial1.read();
    if (input == 0x80)
    {
      decodeMessage();
    }
  }
}

void Communication::decodeMessage()
{
  int pos = 0;
  uint8_t sender = 0;
  uint8_t target = 0;
  uint8_t type = 0;
  size_t length = 0;
  bool loop = true;
  while (Serial1.available() && loop)
  {
    byte input = Serial1.read();
    switch (pos)
    {
    case 0:
      sender = input;
      break;
    case 1:
      target = input;
      break;
    case 2:
      type = input;
      break;
    case 3:
      length = input;

      Serial1.readBytes(_buffer, length - 5);
      loop = false;
      Serial.println("read!");

      for(size_t i = 0; i < length - 5; i++){
        Serial.print((char)_buffer[i]);
      }
      Serial.println("");

      break;
    }
    pos++;
  }
  if (pos != 0)
  {
    pos = 0;
  }
}

void Communication::write_c(uint8_t sender, uint8_t target, uint8_t type, uint8_t * message, size_t messageLength) {
  if (!_isInitialised)
  {
    init();
  }
  digitalWrite(PIN_RS485_READ_WRITE, RS485_WRITE);

  uint8_t * frame = (uint8_t*)calloc(messageLength + 5, sizeof(uint8_t));
  frame[0] = sender;
  frame[1] = target;
  frame[2] = type;
  frame[3] = messageLength + 5;

  memcpy(&frame[4], message, messageLength);

  Serial1.write((char*)frame);
  Serial.println((char*)frame);
}


// void Communication::write(uint8_t sender, uint8_t target, uint8_t type, std::vector<uint8_t> message)
// {
//   if (!_isInitialised)
//   {
//     init();
//   }
//   digitalWrite(PIN_RS485_READ_WRITE, RS485_WRITE);

//   uint8_t length = message.size()+5;
//   std::vector<uint8_t> full;

//   full.push_back(0x80);
//   full.push_back(sender);
//   full.push_back(target);
//   full.push_back(type);
//   full.push_back(length);
//   full.insert(full.end(), message.begin(), message.end());

//   // std::vector<uint8_t>::iterator it;
//   // message.insert(it, length);
//   // message.insert(it, type);
//   // message.insert(it, target);
//   // message.insert(it, sender);

//   Serial1.write((char*)full.data());
//   Serial.println((char*)full.data());
// }
