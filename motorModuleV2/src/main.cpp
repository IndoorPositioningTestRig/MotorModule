#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication/Communication.hpp"
#include "Test/Test.hpp"
#include "Communication/Message.hpp"

static MotorLogic::Logic *logic;
static Communication *communication;
// static TestNamespace::Test *test;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
#ifdef WAIT_SERIAL
  while (!Serial);
#endif
  Serial.print("starting...");
  logic = new MotorLogic::Logic();

  communication = new Communication();
  communication->init();

  Serial.print("Done!\nlooping...\n");
}

void pidLoop()
{
  // logic->loop();
  // test->manualPIDloop();
  // test->teabagging();
  // bool test = false;
  // Serial.print("test: ");
  // Serial.println(test);
  // if (!test)
  // {
  //   Serial.println("in if statement");
  // }
  // else
  // {
  //   Serial.println("in else statement");
  // }
}

void commLoop()
{
  Message message;
  bool success = communication->receive(message);
  if (success)
  {
    // Message received!

  }

  // communication->write_c(11, 22, 33, (uint8_t*)"Hello World", 11);
  // delay(2000);
}

void loop()
{
  logic->loop();
  commLoop();
}
