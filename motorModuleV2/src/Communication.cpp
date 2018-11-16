namespace std
{
void __throw_length_error(char const *)
{
}
} // namespace std

#include "Communication.hpp"
#include "Pins.hpp"
#include <Arduino.h>
//#include <vector.h>
#include "Message.hpp"

Communication::Communication() : _mode(RS485_UNINITIALIZED)
{
}

void Communication::init(int mode)
{
  Serial.begin(9600);
  pinMode(PIN_RS485_READ_WRITE, OUTPUT);
  setMode(RS485_READ);
  while (!Serial);
}

bool Communication::receive(Message& message)
{
  setMode(RS485_READ);

  while (Serial.available())
  {
    byte input = Serial.read();
    if (input == 0x80)
    {
      Message recMessage = decodeMessage();
      message = recMessage;
      return true;
    }
    return false;
  }
  return false;
}

void Communication::setMode(int mode)
{
  if (mode == RS485_WRITE)
  {
    digitalWrite(PIN_RS485_READ_WRITE, RS485_WRITE);
    _mode = RS485_WRITE;
  }
  else
  {
    digitalWrite(PIN_RS485_READ_WRITE, RS485_READ);
    _mode = RS485_READ;
  }
}

Message Communication::decodeMessage()
{
  uint8_t headerBuff[4] = {};
  Serial.readBytes(headerBuff, 4);
  Message message(headerBuff[0], headerBuff[1], headerBuff[2], headerBuff[3]);

  Serial.readBytes(message.data, message.length - 5);

  return message;
}

void Communication::write_c(uint8_t sender, uint8_t target, uint8_t type, uint8_t *message, size_t messageLength)
{
  setMode(RS485_WRITE);

  uint8_t *frame = (uint8_t *)calloc(messageLength + 6, sizeof(uint8_t));
  frame[0] = 0x80;
  frame[1] = sender;
  frame[2] = target;
  frame[3] = type;
  frame[4] = messageLength + 5;

  memcpy(&frame[5], message, messageLength);
  frame[messageLength + 5] = '\0';

  Serial.write((char *)frame);
  free(frame);
}