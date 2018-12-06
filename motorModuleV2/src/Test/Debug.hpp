#ifndef DEBUG_HPP
#define DEBUG_HPP

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

class Debug {
public:
  Debug();
  ~Debug() = default;

  void log(DataPoint data);
private:
  DataPoint _data[150];
};

} // namespace Test

#endif // DEBUG_HPP