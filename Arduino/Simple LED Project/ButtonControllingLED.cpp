const int buttonPin = 2;
const int ledPin = 8;
int lastState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9900);
}

void loop() {
  int state = digitalRead(buttonPin);
  digitalWrite(ledPin, state == LOW ? HIGH : LOW);

  if (state != lastState) {
    Serial.println(state);
    lastState = state;
  }
}