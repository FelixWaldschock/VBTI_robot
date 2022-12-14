// for the raspberry pi we can make an UI for inserting parameters:
//for the distance of the rails(x-axis), the height of the plants(z-axis), the steps for taking the pictures(z-axis/steps)
//optional: a library with the pictures and the corresponding coordinates
#include <Controllino.h> /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

int val1 = 0;  //val1 = X position
int val2 = 0;  //val2 = Y position
int val3 = 0;  //val3 = Z position
bool temp1 = 0;
bool temp2 = 0;

String data;     // variable to store the received data string
String subData;  // variable to store a substring of the received data

// array to store the parsed values from the received data
int value[3];

// array to store the previous values
int prevalue[3];


void setup() {
  // 2 inputs for each motor, so 4 in total
  // IN1/2 current status of motor(moving or not)
  // 5 INputs for each motor, so 10 in total
  // IN0 for limit switch, IN1/2/3 for positioning/ different positions, IN4 enable IN1/2/3 or not
  // need to define positioning for IN1/2/3 but that is in motorprogram
  pinMode(CONTROLLINO_D0, OUTPUT);  // Set the pin CONTROLLINO_D0 as IN0 left.
  pinMode(CONTROLLINO_D1, OUTPUT);  // Set the pin CONTROLLINO_D1 as IN1 left.
  pinMode(CONTROLLINO_D2, OUTPUT);  // Set the pin CONTROLLINO_D2 as IN2 left.
  pinMode(CONTROLLINO_D3, OUTPUT);  // Set the pin CONTROLLINO_D3 as IN3 left.
  pinMode(CONTROLLINO_D4, OUTPUT);  // Set the pin CONTROLLINO_D4 as IN4 left.

  pinMode(CONTROLLINO_D5, OUTPUT);  //Set the pin CONTROLLINO_D5 as IN0 right.
  pinMode(CONTROLLINO_D6, OUTPUT);  //Set the pin CONTROLLINO_D6 as IN1 right.
  pinMode(CONTROLLINO_D7, OUTPUT);  //Set the pin CONTROLLINO_D7 as IN2 right.
  pinMode(CONTROLLINO_D8, OUTPUT);  //Set the pin CONTROLLINO_D8 as IN3 right.
  pinMode(CONTROLLINO_D9, OUTPUT);  //Set the pin CONTROLLINO_D9 as IN4 right.

  pinMode(CONTROLLINO_A1, INPUT);  // Set the pin CONTROLLINO_R0 as OUT1 left - Read digital value at the pin R0.
  pinMode(CONTROLLINO_A2, INPUT);  // Set the pin CONTROLLINO_R1 as OUT2 left - Read digital value at the pin R1.

  pinMode(CONTROLLINO_R2, INPUT);  // Set the pin CONTROLLINO_R2 as OUT1 right - Read digital value at the pin R2.
  pinMode(CONTROLLINO_R3, INPUT);  // Set the pin CONTROLLINO_R3 as OUT2 right - Read digital value at the pin R3.

  pinMode(CONTROLLINO_D10, OUTPUT);  //Set the pin CONTROLLINO_D5 as IN0 lift.
  pinMode(CONTROLLINO_D11, OUTPUT);  //Set the pin CONTROLLINO_D6 as IN1 lift.
  pinMode(CONTROLLINO_D12, OUTPUT);  //Set the pin CONTROLLINO_D7 as IN2 lift.
  pinMode(CONTROLLINO_D13, OUTPUT);  //Set the pin CONTROLLINO_D8 as IN3 lift.
  pinMode(CONTROLLINO_D14, OUTPUT);  //Set the pin CONTROLLINO_D9 as IN4 lift.

  pinMode(CONTROLLINO_R4, INPUT);  // Set the pin CONTROLLINO_R4 as IN1 lift - Read digital value at the pin R4.
  pinMode(CONTROLLINO_R5, INPUT);  // Set the pin CONTROLLINO_R5 as IN2 lift - Read digital value at the pin R5.

  // Initialize the previous value array
  prevalue[0] = 0;
  prevalue[1] = 0;
  prevalue[2] = 0;

  Serial.begin(115200);

  //digitalWrite(CONTROLLINO_D5, HIGH);
  digitalWrite(CONTROLLINO_D4, HIGH);
  digitalWrite(CONTROLLINO_D1, HIGH);
  delay(500);
  digitalWrite(CONTROLLINO_D1, LOW);

}

/*void homing() {
  //homing: get the robot to the starting position
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, HIGH);
  }
*/
void loop() {
  /*
    // check if homing is done
    digitalRead(CONTROLLINO_D0);
    digitalRead(CONTROLLINO_D1);
    if (CONTROLLINO_D0 == HIGH && CONTROLLINO_D1 == LOW) {
    Serial.print("homing is done or stopped moving");
    } else {
    void homing();
    }

    // when homing is done read the wanted position from the raspberry pi
  */

  // software of Luc:
  // robot forward/backward and up/down
  // Wait for data to be received over the serial port
  while (Serial.available() == 0);

  // Read the received data and store it in the "data" variable
  data = Serial.readString();

  // Initialize some variables that will be used to parse the received data
  int initialVal = 0;
  int val;
  int tmp1 = 0;
  int pos = 0;

  // Parse the received data and store the values in the "value" array
  do {
    // Find the next comma in the received data
    val = data.indexOf(',', initialVal);

    // Extract a substring from the received data between the current position
    // and the next comma
    subData = data.substring(initialVal, val);

    // Convert the substring to an integer and store it in the "value" array
    value[pos] = subData.toInt();

    // Increment the position in the "value" array
    pos = pos + 1;

    // Update the current position in the received data
    initialVal = val + 1;
  }  while (val != -1);  // repeat until there are no more commas in the received data

  // Move the motor in the positive direction along the X axis(forward rails)
  if (value[0] == 0 && value[1] == 0 && value[2] == 0) {
    Serial.print("1");

  }
  while (prevalue[0] < value[0]) {


    for (prevalue[0]; prevalue[0] < value[0]; prevalue[0]++) {
      //      digitalWrite(CONTROLLINO_D2, HIGH);
      //      digitalWrite(CONTROLLINO_D4, HIGH);
      //
      //      delay(50);
      //      digitalWrite(CONTROLLINO_D2, LOW);
      //      digitalWrite(CONTROLLINO_D4, LOW);
      //
      //
      //      delay(50);
      //      Serial.println("move positive X");
      delay(20);

    }

    // Print the current position of the motor
    //Serial.print(prevalue[0]);
    Serial.print("1");
    //Serial.print(prevalue[1]);
    //Serial.print(",");
    //Serial.print(prevalue[2]);
  }
  // Move the motor in the negative direction along the X axis(backward rails)
  while (prevalue[0] > value[0]) {


    for (prevalue[0]; prevalue[0] > value[0]; prevalue[0]--) {
      //      digitalWrite(CONTROLLINO_D3, HIGH);
      //      digitalWrite(CONTROLLINO_D8, HIGH);
      //      digitalWrite(CONTROLLINO_D4, HIGH);
      delay(10);
      //      digitalWrite(CONTROLLINO_D3, LOW);
      //      digitalWrite(CONTROLLINO_D8, LOW);
      //      digitalWrite(CONTROLLINO_D4, HIGH);
      delay(10);
      //      Serial.println("move negative X");
    }

    // Print the current position of the motor
    //Serial.print(prevalue[0]);
    //Serial.print(",");
    //Serial.print(prevalue[1]);
    //Serial.print(",");
    //Serial.print(prevalue[2]);
    Serial.print("1");
  }
  // Move the motor in the positive direction along the Z axis(lift up)
  while (prevalue[2] < value[2]) {

    for (prevalue[2]; prevalue[2] < value[2]; prevalue[2]++) {
      //digitalWrite(CONTROLLINO_D12, HIGH);
      digitalWrite(CONTROLLINO_D2, HIGH);
      delay(15);
      temp1 = digitalRead(CONTROLLINO_A1);
      temp2 = digitalRead(CONTROLLINO_A2);
      while ((temp1 == LOW) && (temp2 == HIGH))
      {
        temp1 = digitalRead(CONTROLLINO_A1);
        temp2 = digitalRead(CONTROLLINO_A2);
      }
      digitalWrite(CONTROLLINO_D2, LOW);
      delay(10);
      //Serial.println("move positive Z");
    }

    // Make picture of plant(via raspberry?)


    // Print the current position of the motor
    //Serial.print(prevalue[0]);
    //Serial.print(",");
    //Serial.print(prevalue[1]);
    //Serial.print(",");
    //Serial.print(prevalue[2]);
    Serial.print("1");
  }
  // Move the motor in the negative direction along the Z axis(lift down)
  while (prevalue[2] > value[2]) {

    for (prevalue[2]; prevalue[2] > value[2]; prevalue[2]--) {
      //digitalWrite(CONTROLLINO_D12, HIGH);
      digitalWrite(CONTROLLINO_D3, HIGH);
      delay(15);
      temp1 = digitalRead(CONTROLLINO_A1);
      temp2 = digitalRead(CONTROLLINO_A2);
      while ((temp1 == LOW) && (temp2 == HIGH))
      {
        temp1 = digitalRead(CONTROLLINO_A1);
        temp2 = digitalRead(CONTROLLINO_A2);
      }
      digitalWrite(CONTROLLINO_D3, LOW);
      delay(10);
      //Serial.println("move positive Z");
    }

    // Make a picture of the plant(via raspberry?)

    // Print the current position of the motor
    //Serial.print(prevalue[0]);
    //Serial.print(",");
    //Serial.print(prevalue[1]);
    //Serial.print(",");
    //Serial.print(prevalue[2]);
    Serial.print("1");
  }



  //  // When maximum x has been reached, rotate camera 180 degrees
  //  if (prevalue[0] == 75) {
  //    prevalue[1] = 180;
  //  }
  //
  //  // Robot goes backwards on X-axis and does all the x and z positions again
  //
  //  // When all the x and z postitions are done stop the program
  //  // if x is back to 0, IN1/2/3 LOW
  //  if (prevalue[0] == 0 && prevalue[1] == 180) {
  //    digitalWrite(CONTROLLINO_D1, LOW);
  //    digitalWrite(CONTROLLINO_D2, LOW);
  //    digitalWrite(CONTROLLINO_D3, LOW);
  //    digitalWrite(CONTROLLINO_D4, HIGH);
  //
  //    digitalWrite(CONTROLLINO_D6, LOW);
  //    digitalWrite(CONTROLLINO_D7, LOW);
  //    digitalWrite(CONTROLLINO_D8, LOW);
  //    digitalWrite(CONTROLLINO_D9, HIGH);
  //
  //    digitalWrite(CONTROLLINO_D11, LOW);
  //    digitalWrite(CONTROLLINO_D12, LOW);
  //    digitalWrite(CONTROLLINO_D13, LOW);
  //    digitalWrite(CONTROLLINO_D14, HIGH);
  //
  //    Serial.print("end of program");
  //  }
}
