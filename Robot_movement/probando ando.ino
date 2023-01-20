#include <Stepper.h> 
// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 12800
int NumberRevolutions;
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
    NumberRevolutions= map(Angle,0,360,0,stepsPerRevolution);
    Serial.println(String(Angle) + "->" + String (NumberRevolutions));
  }    


 for (int i = 0; i < NumberRevolutions; i++) {

    // Set the spinning direction clockwise:
    digitalWrite(dirPin, HIGH);
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
 }

  for (int i = 0; i < -NumberRevolutions; i++) {

    // Set the spinning direction clockwise:
    digitalWrite(dirPin, LOW);
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(200);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(200);
 }

}
