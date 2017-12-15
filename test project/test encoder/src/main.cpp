#include "main.h"


void setup() {
    Serial.begin(9600);
    setupEncoder();
        Serial.read();
    Serial.println("Starting test encoder");
    Serial.println("Press a key to start");
    while(Serial.available() == 0){}
    Serial.read();
    Serial.println("Set the test data: ");
    Serial.println("Set current length in mm");
    while(Serial.available() == 0){}
    String currentLength = Serial.readString();
    Serial.println("Set desired length");
    while(Serial.available() == 0){}
    String desiredLength = Serial.readString();
    Serial.println("Set desired speed in mm /s");
    while(Serial.available() == 0){}
    String speed = Serial.readString();

    Serial.print("currentpos: ");
    Serial.println(currentLength);
    Serial.print("desiredpos: ");
    Serial.println(desiredLength);
    Serial.print("desiredspeed: ");
    Serial.println(speed);
    Serial.println("going to test the encoder");

    //Parse strings to int 
    int currentLengthInt = currentLength.toInt();
    int desiredLengthInt = desiredLength.toInt();
    int speedInt = speed.toInt(); 
    
    int currentticks =  currentLengthInt / MMPERTICK;
    Serial.print("amount of ticks = ");
    Serial.println(currentticks);
    setCurrentPosition(currentLengthInt);
    setEncoderData(desiredLengthInt, speedInt);
}

void loop() {

    bool direction = false;
    int speed = 122;
    bool done = false;
    calculateMotorSpeed(direction,speed,done);
    Serial.print("direction: ") ;
    Serial.print(direction);
    Serial.print("\t Speed:");
    Serial.print(speed);
    Serial.print("\t done: ");
    Serial.println(done);        
    delay(2000);
}