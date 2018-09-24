#include <Arduino.h>
#include "MotorLogic/Logic.hpp"
#include "MotorLogic/Counter.hpp"
#include "MotorLogic/ForceDetector.hpp"

static MotorLogic::Logic * logic;
static MotorLogic::Counter * counter;    
static MotorLogic::ForceDetector d;


void setup() {
    Serial.begin(9600);
#ifdef WAIT_SERIAL
    while(!Serial);
#endif
    Serial.println("starting...");
    logic = new MotorLogic::Logic(255);
    counter = new MotorLogic::Counter();

    d.init();
}

void move(int len) {
    for (uint64_t i = 0; i < 100; i++) {
        logic->move(len);
        Serial.println(counter->getCount());
    }
}

void loop() {
    Serial.print("max: ");
    if (d.max) {
        Serial.print("High, ");
    } else {
        Serial.print("Low, ");
    }

    Serial.print("min: ");
    if (d.min) {
        Serial.println("High");
    } else {
        Serial.println("low");
    }


    if(Serial.available()){
        char input = Serial.read();
        Serial.println(input);
        if(input == 'r'){
            move(-10);
        } else if (input == 'f') {
            move(10);
        }
    }
}   