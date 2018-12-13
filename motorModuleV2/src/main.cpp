#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication/Communicator.hpp"
#include "Communication/Message.hpp"
#include "Id.hpp"
#include "Test/Debug.hpp"

MotorLogic::Logic *logic = nullptr;
Id *id = nullptr;
Communication::Communicator *communicator = nullptr;
//  Test::Debug *_debug = nullptr;


void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  //Serial.print("starting...");

  id = new Id();
  logic = new MotorLogic::Logic();

  communicator = new Communication::Communicator();
  communicator->init();


  // id->putId(2);

  // Serial.print("ID: ");
  // Serial.println(id->getId());


  //Serial.println("RS485 test print");
  communicator->write_c(1, 0, 2, (uint8_t*)"{\"command\":\"test\"}", 18);


  // Serial.print("Done!\nlooping...\n\n");
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
      logic->message(message, communicator);
    }
  }
}

void loop()
{
  // logic->loop();
  // commLoop();
  delay(100);
}
