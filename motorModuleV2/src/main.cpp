#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication/Communicator.hpp"
#include "Communication/Message.hpp"
#include "Id.hpp"
#include "Test/Debug.hpp"

MotorLogic::Logic logic;
Id id;
Communication::Communicator communicator;
Test::Debug debug(&communicator);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  //id.putId(3);

  logic.init();
  communicator.init();
}

void commLoop()
{
  Communication::Message message;
  bool success = communicator.receive(message);
  if (success)
  {
    //Serial.println("message received");
    // Message received!
    // Check if the arduino is the target
    Serial.print("got message with target: ");
    Serial.println(message.target);
    Serial.print("We are: ");
    Serial.println(id.getId());
    if (message.target == 0 || message.target == id.getId())
    {
      logic.message(message, &communicator, &debug);
    }
  }
}

void loop()
{
  logic.loop(&debug, &communicator, &id);
  commLoop(); 
}
