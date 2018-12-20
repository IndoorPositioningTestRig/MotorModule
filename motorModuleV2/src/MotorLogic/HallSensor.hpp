#include "../Pins.hpp"

#ifndef HALL_SENSOR_HPP
#define HALL_SENSOR_HPP

namespace MotorLogic
{
class HallSensor {
public:
  HallSensor() = default;
  void init();

  bool isActive() const;
private:
  static int state;
};
} // namespace MotorLogic

#endif // HALL_SENSOR_HPP