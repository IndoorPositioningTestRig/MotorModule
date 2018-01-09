// Pin declaration
int clockWise = 4;
int counterClockWise = 2;
int pwmPin = 3;

void Retract(int Speed) {
  digitalWrite(clockWise, true);
  digitalWrite(counterClockWise, !true);
  analogWrite(pwmPin, Speed);
}

void Feed(int Speed) {
  digitalWrite(clockWise, false);
  digitalWrite(counterClockWise, !false);
  analogWrite(pwmPin, Speed);
}


void setup() {
  Serial.begin(9600);

  // Set pin modes
  pinMode(pwmPin, OUTPUT);
  pinMode(clockWise, OUTPUT);
  pinMode(counterClockWise, OUTPUT);

  Feed(20);
}

void loop() {

}
