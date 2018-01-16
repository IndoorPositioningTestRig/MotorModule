#include "endswitch.h"

#define SwitchCheckMaxForcePin 10
#define SwitchCheckMinForcePin 11

bool checkMaxForceSwitchPressed;
bool checkMinForceSwitchPressed;

void interruptSwitch();

int setupSwitches()
{
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
