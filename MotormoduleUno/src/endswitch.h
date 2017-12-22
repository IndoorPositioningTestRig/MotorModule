#ifndef ENDSWITCH_H
#define ENDSWITCH_H

#include "Arduino.h"
#include "main.h"

#define SWITCH_MAX_CHECK  5
#define SWITCH_MIN_CHECK  6


int setupSwitches();

bool isSwitchPressed();

bool GetSwitchStatus(int SWITCH);


#endif