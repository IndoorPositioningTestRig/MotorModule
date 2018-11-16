#ifndef PINS_HPP
#define PINS_HPP

#include <Arduino.h>

namespace MotorLogic {
  // Encoder    
  const int PIN_ENCODER_A = 2; // interrupt
  const int PIN_ENCODER_B = 8; // interrupt //pin 3 for mega2560, pin 8 for genuino101

  // Motor driver
  const int PIN_MOTOR_PWM = 6;
  const int PIN_MOTOR_COUNTER_CLOCKWISE = 5;
  const int PIN_MOTOR_CLOCKWISE = 7;
  
  // Force switches
  const int PIN_MAX_FORCE = 18; // interrupt 
  const int PIN_MIN_FORCE = 19; // interrupt
}

// RS 485
const int PIN_RS485_A = 0;
const int PIN_RS485_B = 1;
const int PIN_RS485_READ_WRITE = 9;

const int RS485_READ = HIGH;
const int RS485_WRITE = LOW;
const int RS485_UNINITIALIZED = -1;


#endif // PINS_HPP
