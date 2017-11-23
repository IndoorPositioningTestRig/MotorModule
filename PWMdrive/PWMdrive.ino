int clockWise = 4;
int counterClockWise = 2;
int pwmPin = 3;
int brightness = 0;
int fadeAmount = 5;
bool direction = true;

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(pwmPin, OUTPUT);
  pinMode(clockWise, OUTPUT);
  pinMode(counterClockWise, OUTPUT);
  Serial.begin(9600);
  digitalWrite(clockWise, direction);
  digitalWrite(counterClockWise, !direction);
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println(brightness);
  // set the brightness of pin 9:
  analogWrite(pwmPin, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  if(brightness <= 0){
    direction = !direction;
    digitalWrite(clockWise, direction);
    digitalWrite(counterClockWise, !direction);    
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}
