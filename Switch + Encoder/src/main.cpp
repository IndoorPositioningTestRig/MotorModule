#include <Arduino.h>

//Encoder pins:
int EncoderPinA = 11;       //RISING interrupt
int EncoderPinB = 12;
int EncoderPos = 0;

//switch pins
int Switch1Pin = 2;         //CHANGE interrupt
int Switch2Pin = 7 ;       //CHANGE interrupt

//interrupt functions:
void interruptSwitch1();
void interruptSwitch2();
void interruptRotate();

void setup() {
    //set interrupts:
    attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptRotate, RISING);
    attachInterrupt(digitalPinToInterrupt(Switch1Pin), interruptSwitch1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(Switch2Pin), interruptSwitch2, CHANGE);
    Serial.begin(9600);
}

void loop() {
    delay(1);
}

void interruptSwitch1(){
    bool switchValue = digitalRead(Switch1Pin);
    if(switchValue)
        Serial.println("button 1 pressed!");
    else
        Serial.println("button 1 released!");
}

void interruptSwitch2(){
    bool switchValue = digitalRead(Switch2Pin);
    if(switchValue)
        Serial.println("button 2 pressed!");
    else
        Serial.println("button 2 released!");
}

void interruptRotate(){
    if (digitalRead(EncoderPinB) == LOW)
        EncoderPos--;
    else
        EncoderPos++;
    Serial.println(EncoderPos);
}