#ifndef PINS_HPP
#define PINS_HPP

namespace MotorLogic {
  // Encoder    
  const int PIN_ENCODER_A = 2; // interrupt
  const int PIN_ENCODER_B = 8; // interrupt

  // Motor driver
  const int PIN_MOTOR_PWM = 3;
  const int PIN_MOTOR_COUNTER_CLOCKWISE = 4;
  const int PIN_MOTOR_CLOCKWISE = 7;
  
  // Force switches
  const int PIN_MAX_FORCE = 10; // interrupt
  const int PIN_MIN_FORCE = 11; // interrupt
}

// RS 485
const int PIN_RS485_A = 0;
const int PIN_RS485_B = 1;

#endif // PINS_HPP
