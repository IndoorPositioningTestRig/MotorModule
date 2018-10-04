#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "MotorLogic/Counter.hpp"
#include "MotorLogic/ForceDetector.hpp"
#include "Communication.hpp"

static MotorLogic::Logic *logic;
static MotorLogic::Counter *counter;
static Communication *communication;

void setup()
{
  Serial.begin(9600);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.println("starting...");
  logic = new MotorLogic::Logic(255);
  counter = new MotorLogic::Counter();

  communication = new Communication();

  pinMode(10, INPUT);
  digitalWrite(10, 0);
  pinMode(11, INPUT);
  digitalWrite(11, 0);
}

void move(int len)
{
  Serial.print("len: ");
  Serial.println(len);
  int target = counter->getCount() + len;
  Serial.print("target: ");
  Serial.println(target);

  if (len > 0)
  {
    while (counter->getCount() < target)
    {
      // Serial.print("done: ");
      // Serial.println((target - counter->getCount()));
      // Serial.print("count: ");
      // Serial.println(counter->getCount());
      // if((target - counter->getCount()) < len/2){ö
      //     logic->setSpeed(128);
      // }
      logic->move(10);
      Serial.println(counter->getCount());
    }
  }
  else if (len < 0)
  {
    while (counter->getCount() > target)
    {
      logic->move(-10);
      Serial.println(counter->getCount());
    }
  }
}

void loop()
{
  communication->listen();

  //logic->loop();
  // logic->move(1000);
  // logic->move(-1000);

  // logic->move(1000);
  // logic->move(-1000);
  // delay(5000);
  // Serial.print(logic->isForceMin());
  // Serial.print(", ");
  // Serial.println(logic->isForceMax());
  // delay(100);

  // if(Serial.available()){
  //     char input = Serial.read();
  //     Serial.println(input);
  //     if(input == 'r'){
  //         move(-100);
  //     } else if (input == 'f') {
  //         move(100);
  //     }
  // }
}