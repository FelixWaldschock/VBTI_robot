
#include <Stepper.h> 

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 1600
long NumberRevolutions;
int Angle;


void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT); 

  Serial.begin(9600);
}


void loop() {

  if (Serial.available() > 0){ 
    Angle= Serial.parseInt();
    Serial.println(Angle);
    NumberRevolutions= (Angle*1600L)/360;
    Serial.println(NumberRevolutions);
  }    


for (int i = 0; i < NumberRevolutions; i++) {

    // Set the spinning direction clockwise:
    digitalWrite(dirPin, HIGH);

    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
}
  
  // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 1/2 revolution:
  for (int i = 0; i < 800; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  delay(1000);

  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1/2 revolution:
  for (int i = 0; i < 800; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }


}