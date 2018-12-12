#ifndef SERIAL_WRAPPER_HPP
#define SERIAL_WRAPPER_HPP

#include <Arduino.h>

namespace Communication {

class SerialWrapper {
public:
  static void begin(unsigned long baud);
  static void waitReady(); // while (!Serial);
  static int available();
  static int read();
  static size_t readBytes(char*buffer, size_t length);
  static size_t readBytes(uint8_t*buffer, size_t length);
  static size_t write(char* data);
  static size_t writeFrame(uint8_t * frame);
};

} // namespace Communication
#endif // SERIAL_WRAPPER_HPP
