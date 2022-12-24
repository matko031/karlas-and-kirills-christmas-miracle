/*
 * Turn the screw on the microphone until the printed value comes close to 10.
 * You should do this when there are no other sounds around.
 */

int amplitude;
int relayPin = 10;
void setup() {
    Serial.begin(9600);
    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, LOW);
}


void loop() {
  amplitude = analogRead(0) - 512;
  Serial.println(amplitude);
  delay(300);
}
