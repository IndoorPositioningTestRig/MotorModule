#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "../Communication/Communicator.hpp";

namespace Test {
  // Setpoint
  // Output
  // Encoder value

  // 8kb total RAM

// 6 bytes
struct DataPoint {
  uint16_t setpoint; // 4 b
  uint16_t output; // 4 b
  uint16_t encoder; // 4 b
};

// 6000 / 12 = 500,

#define MAX_LEN 100

class Debug {
public:
  Debug() = default;
  ~Debug() = default;

  void log(double setpoint, double output, double encoder);
  void print(Communication::Communicator communicator);
private:
  uint16_t _data[MAX_LEN];
  unsigned int _position = 0;
};

} // namespace Test

#endif // DEBUG_HPP