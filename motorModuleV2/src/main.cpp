#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication/Communication.hpp"
#include "Test/Test.hpp"
#include "Communication/Message.hpp"
#include "Id.hpp"

static MotorLogic::Logic * logic;
static Communication* communication;
static TestNamespace::Test* test;
static Id* id;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
#ifdef WAIT_SERIAL
  while (!Serial);
#endif
  Serial.print("starting...");
  //logic = new MotorLogic::Logic();
  test = new TestNamespace::Test();
  id = new Id();
  logic = new MotorLogic::Logic();

  communication = new Communication();
  communication->init();

  Serial.print("ID: ");
  Serial.println(id->id);

  Serial.print("Done!\nlooping...\n");
}

void pidLoop()
{
  // logic->loop();
  test->manualPIDloop();
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
    
    // Check if the arduino is the target
    if (message.target == 0 || message.target == id->id) {
      logic->message(message);
    }
  }

  // communication->write_c(11, 22, 33, (uint8_t*)"Hello World", 11);
  // delay(2000);
}

void loop()
{
  logic->loop();
  commLoop();
  //pidLoop();
}
