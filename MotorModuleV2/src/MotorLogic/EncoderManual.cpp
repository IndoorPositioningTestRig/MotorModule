#include "EncoderManual.hpp"

using namespace MotorLogic;

#define PIN_A 2
#define PIN_B 8

RotaryEncoder EncoderManual::_encoder(PIN_A, PIN_B);

EncoderManual::EncoderManual() {
    delay(500);
    attachInterrupt(digitalPinToInterrupt(PIN_A), [](){
        //Serial.println("interruptA");
        _encoder.tick(); 
    }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_B), [](){
        //Serial.println("interruptB");
        _encoder.tick();
    }, CHANGE);
    delay(500);
}

long EncoderManual::read() {
    return _encoder.getPosition();
}
