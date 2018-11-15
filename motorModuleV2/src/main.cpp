#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication.hpp"
#include "Test/Test.hpp"

static MotorLogic::Logic *logic;
static Communication *communication;
static TestNamespace::Test *test;

void setup()
{
  Serial.begin(9600);
    while (!Serial);
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.println("starting...");
  //logic = new MotorLogic::Logic();
  test = new TestNamespace::Test();


  //communication = new Communication();
  //Serial1.begin(9600);

  // pinMode(10, INPUT);
  // digitalWrite(10, 0);
  // pinMode(11, INPUT);
  // digitalWrite(11, 0);

  //pinMode(6, OUTPUT);
  // pinMode(9, OUTPUT);
  // digitalWrite(9, HIGH); //LOW is write, HIGH is read
}

void loop()
{
 //logic->loop();
 test->manualPIDloop();
 //test->teabagging();
//  bool test = false;
//  Serial.print("test: ");
//  Serial.println(test);
//  if(!test){
//    Serial.println("in if statement");
//  } else {
//    Serial.println("in else statement");
//  }

 //delay(1000);

//  while(Serial1.available()){
//    char input = Serial1.read();
//    Serial.print("Serial1: ");
//    Serial.println(input);
//  }

//   while(Serial.available()){
//    char input = Serial.read();
//    Serial.print("Serial: ");
//    Serial.println(input);
//  }


//communication->listen();

// delay(10);
// Serial1.write("Herro\n");
// Serial.println("Herro");
}
