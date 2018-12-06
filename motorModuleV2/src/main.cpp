#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication/Communicator.hpp"
#include "Test/Test.hpp"
#include "Communication/Message.hpp"
#include "Id.hpp"

static MotorLogic::Logic *logic;
static Id *id;
static Communication::Communicator *communicator;
static TestNamespace::Test *test;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.print("starting...");

  test = new TestNamespace::Test();
  id = new Id();
  logic = new MotorLogic::Logic();

  communicator = new Communication::Communicator();
  communicator->init();

  //id->putId(2);

  Serial.print("ID: ");
  Serial.println(id->getId());

  Serial.print("Done!\nlooping...\n\n");
}

void pidLoop()
{
  // logic->loop();
  //test->manualPIDloop();
  //test->teabagging();
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
  Communication::Message message;
  bool success = communicator->receive(message);
  if (success)
  {
    // Message received!
    // Check if the arduino is the target
    if (message.target == 0 || message.target == id->getId())
    {
      logic->message(message);
    }
  }

  // communication->write_c(11, 22, 33, (uint8_t*)"Hello World", 11);
  // delay(2000);
}

void loop()
{
  //pidLoop();
  logic->loop();
  commLoop();
}
