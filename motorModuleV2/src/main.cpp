#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication/Communicator.hpp"
#include "Communication/Message.hpp"
#include "Id.hpp"
#include "Test/Debug.hpp"

static MotorLogic::Logic *logic;
static Id *id;
static Communication::Communicator *communicator;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.print("starting...");

  // test = new TestNamespace::Test();
  id = new Id();
  logic = new MotorLogic::Logic();

  communicator = new Communication::Communicator();
  communicator->init();

  //id->putId(2);
  // Test::Debug debug;
  // debug.log(12345.12345, 12345.12345, 12345.12345);
  // debug.print(*communicator);
  communicator->write_c(1, 0, 3, "hoi Stefan", 10);

  Serial.print("ID: ");
  Serial.println(id->getId());

  Serial.print("Done!\nlooping...\n\n");
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
}

void loop()
{
  logic->loop();
  commLoop();
}
