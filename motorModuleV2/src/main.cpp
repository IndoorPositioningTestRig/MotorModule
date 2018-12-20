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
  Serial.print("double: ");
  double x = 24142.12412;
  Serial.println(sizeof x);


  logic.init();
  communicator.init();


  //communicator.write_c(1, 0, 2, (uint8_t*)"{\"command\":\"test\"}", 18);
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
    if (message.target == 0 || message.target == id.getId())
    {
      logic.message(message, &communicator, &debug);
    }
  }
}

void loop()
{
  logic.loop(&debug);
  commLoop(); 
}
