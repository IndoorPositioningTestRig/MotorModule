#include "endswitch.h"

#define SwitchCheckMaxForcePin 5
#define SwitchCheckMinForcePin 6

bool checkMaxForceSwitchPressed;
bool checkMinForceSwitchPressed;

void interruptSwitch();

int setupSwitches()
{
    Serial.println("setting up switches");
    attachInterrupt(digitalPinToInterrupt(SwitchCheckMaxForcePin), interruptSwitch, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SwitchCheckMinForcePin), interruptSwitch, CHANGE);
    checkMaxForceSwitchPressed = digitalRead(SwitchCheckMaxForcePin);
    checkMinForceSwitchPressed = digitalRead(SwitchCheckMinForcePin);
    return STATUS_OK;
}

bool isSwitchPressed()
{
    return checkMaxForceSwitchPressed || checkMinForceSwitchPressed;
}

bool getSwitchStatus(int SWITCH){
    switch(SWITCH){
        case 5:
            return checkMaxForceSwitchPressed;
        case 6:
            return checkMinForceSwitchPressed;
        default: return false;
    }
}

void interruptSwitch(){
    checkMaxForceSwitchPressed = digitalRead(SwitchCheckMaxForcePin);
    checkMinForceSwitchPressed = digitalRead(SwitchCheckMinForcePin);
}
