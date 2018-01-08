int clockWise = 4;
int counterClockWise = 7;
int pwmPin = 3;
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
  digitalWrite(pwmPin, 50);
}

// the loop routine runs over and over again forever:
void loop() {
  delay(1);
}
