#include "Communicator.hpp"
#include "../Pins.hpp"
#include <Arduino.h>
#include "Message.hpp"
#include "SerialWrapper.hpp"

using namespace Communication;

Communicator::Communicator() : _mode(RS485_UNINITIALIZED)
{}

void Communicator::init(int mode)
{
  SerialWrapper::begin(9600);
  pinMode(PIN_RS485_READ_WRITE, OUTPUT);
  setMode(RS485_READ);
#ifdef WAIT_SERIAL
  SerialWrapper::waitReady();
#endif
}

bool Communicator::receive(Message& message)
{
  setMode(RS485_READ);

  while (SerialWrapper::available())
  {
    byte input = SerialWrapper::read();
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

void Communicator::setMode(int mode)
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

Message Communicator::decodeMessage()
{
  uint8_t headerBuff[4] = {};
  SerialWrapper::readBytes(headerBuff, 4);
  Message message(headerBuff[0], headerBuff[1], headerBuff[2], headerBuff[3]);

  SerialWrapper::readBytes(message.data, message.length - 5);

  return message;
}

void Communicator::write_c(uint8_t sender, uint8_t target, uint8_t type, uint8_t *message, size_t messageLength)
{
  setMode(RS485_WRITE);

  uint8_t *frame = (uint8_t *)calloc(messageLength + 6, sizeof(uint8_t));
  frame[0] = 0x80;
  frame[1] = sender;
  frame[2] = target;
  frame[3] = type;
  frame[4] = messageLength + 5;

  memcpy(&frame[5], message, messageLength);
  Serial.print("sending: ");
  Serial.println((char*)frame);
  frame[messageLength + 5] = '\0';

  SerialWrapper::write((char *)frame);
  free(frame);
}
