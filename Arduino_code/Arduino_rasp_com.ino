void setup() {
  Serial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    delay(1000);
    Serial.print("Robot it at position: ");
    Serial.println(data);
  }
}
