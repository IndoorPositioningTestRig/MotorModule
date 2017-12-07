#include "encoder.h"

// Global variables
int EncoderPos = 0;
int desiredPos = 0;

int desiredSpeed = 0;
int currentSpeed = 0;

bool direction;
int acceleration = 0;

void interruptEncoder();

void setupEncoder(){
    // encoder setup
    pinMode(EncoderPinA, INPUT);
    pinMode(EncoderPinB, INPUT);
      //interrupt setup:
    attachInterrupt(digitalPinToInterrupt(EncoderPinA), interruptEncoder, RISING);
}

//interrupt functions:
void interruptEncoder()
{
  if (digitalRead(EncoderPinB) == LOW)
    EncoderPos--;
  else
    EncoderPos++;
}

void setEncoderData(int length, int speed ){
    desiredPos = round(length / ((ENCODER_DIAMETER * PI) / TICKS));
    desiredSpeed = speed;
}


