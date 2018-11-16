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
  while (!Serial || !Serial1)
    ;
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.print("starting...");
  //logic = new MotorLogic::Logic();
  test = new TestNamespace::Test();
  id = new Id();

  communication = new Communication();
  communication->init();

  Serial.print("ID: ");
  Serial.println(id->id);

  Serial.print("Done!\nlooping...\n");
}

void pidLoop()
{
  //logic->loop();
  //test->manualPIDloop();
  //test->teabagging();
  //  bool test = false;
  //  Serial.print("test: ");
  //  Serial.println(test);
  //  if(!test){
  //    Serial.println("in if statement");
  //  } else {
  //    Serial.println("in else statement");
  //  }
}

void commLoop()
{
  // Message message;
  // bool success = communication->receive(message);
  // if (success)
  // {
  //   // Debug stuff...
  //   Serial.print("read: ");
  //   for (uint8_t i = 0; i < message.length - 5; i++)
  //   {
  //     Serial.print((char)message.data[i]);
  //   }
  //   Serial.println("");
  // }

  communication->write_c(11, 22, 33, (uint8_t*)"Hello World", 11);
  delay(2000);
}

void loop()
{
  //commLoop();
  //pidLoop();


  delay(1000);
}
