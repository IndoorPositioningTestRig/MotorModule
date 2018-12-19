#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "../Communication/Communicator.hpp"

namespace Test {
  // 8kb total RAM
  // Keeping 2kb for other stuff, leaves us with 6kb

// 8 bytes
struct DataPoint {
  int16_t setpoint; // 2 b
  int16_t output; // 2 b
  int16_t encoder; // 2 b
  int16_t deltatime; //ms 2b
};

// 6000 / 8 = 750 maximum datapoints
// 750 * 4 = 3000 needed length.
#define MAX_LEN 3000

class Debug {
public:
  Debug(Communication::Communicator * communicator);
  ~Debug() = default;

  void log(double setpoint, double output, double encoder, long deltatime);
  void print();
private:
  Communication::Communicator * _communicator;

  int16_t _data[MAX_LEN];
  unsigned int _position = 0;
};

} // namespace Test

#endif // DEBUG_HPP