// Pin declaration
int clockWise = 7;
int counterClockWise = 4;
int pwmPin = 3;

void Retract(int Speed) {
  digitalWrite(clockWise, false);
  digitalWrite(counterClockWise, !false);
  analogWrite(pwmPin, Speed);
}

void Feed(int Speed) {
  digitalWrite(clockWise, true);
  digitalWrite(counterClockWise, !true);
  analogWrite(pwmPin, Speed);
}


void setup() {
  // Set pin modes
  pinMode(pwmPin, OUTPUT);
  pinMode(clockWise, OUTPUT);
  pinMode(counterClockWise, OUTPUT);

  Retract(35);
}

void loop() {
  delay(1);
}
