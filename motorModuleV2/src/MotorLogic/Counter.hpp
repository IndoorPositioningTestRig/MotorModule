#ifndef ENCODER_HPP
#define ENCODER_HPP

#include "RotaryEncoder.hpp"

namespace MotorLogic
{

class Counter
{
public:
  Counter() = default;

  void init();
  long getCount();
  void reset();

  static RotaryEncoder *encoder;
private:
};
} // namespace MotorLogic

#endif // ENCODER_HPP
