#include "SerialWrapper.hpp"

using namespace Communication;

void SerialWrapper::begin(unsigned long baud)
{
#ifdef USE_SERIAL_1
  Serial1.begin(baud);
#else
  Serial.begin(baud);
#endif
}

void SerialWrapper::waitReady()
{
#ifdef USE_SERIAL_1
  while (!Serial1)
    ;
#else
  while (!Serial)
    ;
#endif
}

int SerialWrapper::available()
{
#ifdef USE_SERIAL_1
  return Serial1.available();
#else
  return Serial.available();
#endif
}

int SerialWrapper::read()
{
#ifdef USE_SERIAL_1
  return Serial1.read();
#else
  return Serial.read();
#endif
}

size_t SerialWrapper::readBytes(char *buffer, size_t length)
{
#ifdef USE_SERIAL_1
  return Serial1.readBytes(buffer, length);
#else
  return Serial.readBytes(buffer, length);
#endif
}

size_t SerialWrapper::readBytes(uint8_t *buffer, size_t length)
{
#ifdef USE_SERIAL_1
  return Serial1.readBytes(buffer, length);
#else
  return Serial.readBytes(buffer, length);
#endif
}

size_t SerialWrapper::write(char *data, bool flush)
{
#ifdef USE_SERIAL_1
  size_t ret = Serial1.write(data);
  if (flush)
  {
    Serial1.flush();
  }
  return
#else
  size_t ret = Serial.write(data);
  if (flush)
  {
    Serial.flush();
  }
  return ret;
#endif
}

size_t SerialWrapper::writeFrame(uint8_t *frame, bool flush)
{
  size_t length = frame[4];

#ifdef USE_SERIAL_1
  size_t ret = Serial1.write(frame, length);
  if (flush)
  {
    Serial1.flush();
  }
  return ret;
#else
  size_t ret = Serial.write(frame, length);
  if (flush)
  {
    Serial.flush();
  }
  return ret;
#endif
}

void SerialWrapper::flush()
{
  #ifdef USE_SERIAL_1
    Serial1.flush();
  #else
    Serial.flush();
  #endif
}
