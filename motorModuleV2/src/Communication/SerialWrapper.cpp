#include "SerialWrapper.hpp"

void SerialWrapper::begin(unsigned long baud) {
  #ifdef USE_SERIAL_1
    Serial1.begin(baud);
  #else
    Serial.begin(baud);
  #endif
}

void SerialWrapper::waitReady() {
  #ifdef USE_SERIAL_1
    while (!Serial1);
  #else
    while (!Serial);
  #endif
}

int SerialWrapper::available() {
  #ifdef USE_SERIAL_1
    return Serial1.available();
  #else
    return Serial.available();
  #endif
}

int SerialWrapper::read() {
  #ifdef USE_SERIAL_1
    return Serial1.read();
  #else
    return Serial.read();
  #endif
}

size_t SerialWrapper::readBytes(char*buffer, size_t length) {
  #ifdef USE_SERIAL_1
    return Serial1.readBytes(buffer, length);
  #else
    return Serial.readBytes(buffer, length);
  #endif
}

size_t SerialWrapper::readBytes(uint8_t*buffer, size_t length) {
  #ifdef USE_SERIAL_1
    return Serial1.readBytes(buffer, length);
  #else
    return Serial.readBytes(buffer, length);
  #endif
}

size_t SerialWrapper::write(char* data) {
  #ifdef USE_SERIAL_1
    return Serial1.write(data);
  #else
    return Serial.write(data);
  #endif
}
