#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication.hpp"
#include "Test/Test.hpp"
//#include <vector>
//#include <string>
#include "Message.hpp"


static MotorLogic::Logic *logic;
static Communication *communication;
static TestNamespace::Test *test;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  while (!Serial || !Serial1);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.print("starting...");
  //logic = new MotorLogic::Logic();
  // test = new TestNamespace::Test();

  communication = new Communication();
  communication->init();

  // pinMode(10, INPUT);
  // digitalWrite(10, 0);
  // pinMode(11, INPUT);
  // digitalWrite(11, 0);

  // pinMode(6, OUTPUT);
  Serial.print("Done!\nlooping...\n");
}

void loop()
{
  //logic->loop();
  // test->manualPIDloop();
  //test->teabagging();
  //  bool test = false;
  //  Serial.print("test: ");
  //  Serial.println(test);
  //  if(!test){
  //    Serial.println("in if statement");
  //  } else {
  //    Serial.println("in else statement");
  //  }

  Message message;
  bool success = communication->receive(message);
  if (success) {
    // Debug stuff...
    Serial.print("read: ");
    for (uint8_t i = 0; i < message.length - 5; i++)
    {
      Serial.print((char)message.data[i]);
    }
    Serial.println("");
  }

  // communication->write_c(11, 22, 33, (uint8_t*)"Hello World", 11);
  // delay(2000);
}
