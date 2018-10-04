#ifndef ENCODER_HPP
#define ENCODER_HPP

#include "RotaryEncoder.hpp"

namespace MotorLogic
{

class Counter
{
public:
  Counter();
  long getCount();
  static RotaryEncoder *encoder;

private:
};
} // namespace MotorLogic

#endif // ENCODER_HPP
