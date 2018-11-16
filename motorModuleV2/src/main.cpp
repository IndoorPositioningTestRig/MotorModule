#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "Communication.hpp"
#include "Test/Test.hpp"
//#include <vector>
//#include <string>


static MotorLogic::Logic *logic;
static Communication *communication;
static TestNamespace::Test *test;

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    ;
#ifdef WAIT_SERIAL
  while (!Serial)
    ;
#endif
  Serial.println("starting...");
  //logic = new MotorLogic::Logic();
  test = new TestNamespace::Test();

  communication = new Communication();
  Serial1.begin(9600);

  // pinMode(10, INPUT);
  // digitalWrite(10, 0);
  // pinMode(11, INPUT);
  // digitalWrite(11, 0);

  // pinMode(6, OUTPUT);
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

  //communication->listen();

  uint8_t message[11] = {
    'h', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r','l','d'
  };
  communication->write_c(11, 22, 33, message, 11);
  delay(2000);
  // std::vector<uint8_t> message;
  // std::string s = "hello world!!";
  // //char str[] = "hello world!!";
  // //message.emplace_back((uint8_t)str);
  // //std::copy(str.c_str(), str.c_str() + str.length(), message);
  // message.push_back('H');
  // message.push_back('E');
  // message.push_back('L');
  // message.push_back('L');
  // message.push_back('O');
  // message.push_back('!');

  // communication->write(11, 22, 33, message);
  // delay(2000);
}
