#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "../Communication/Communicator.hpp";

namespace Test {
  // Setpoint
  // Output
  // Encoder value

  // 8kb total RAM

// 12 bytes
struct DataPoint {
  double setpoint; // 4 b
  double output; // 4 b
  double encoder; // 4 b
};

// 6000 / 12 = 500,

#define MAX_LEN 1500

class Debug {
public:
  Debug() = default;
  ~Debug() = default;

  void log(double setpoint, double output, double encoder);
  void print(Communication::Communicator communicator);
private:
  int16_t _data[MAX_LEN];
  unsigned int _position = 0;
};

} // namespace Test

#endif // DEBUG_HPP