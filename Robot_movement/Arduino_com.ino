#define Z_IN2 13 // positie plus
#define Z_IN3 12 // positie min

#define X_IN2 11 // positie plus
#define X_IN3 10 // positie min


String    data; // variable to store the received data string
String subData; // variable to store a substring of the received data

// array to store the parsed values from the received data
int value[3];

// array to store the previous values
int prevalue[3];


void setup() {
  // Set the baud rate for the serial port
  Serial.begin(9600);

  // Set the pins as outputs
  pinMode(Z_IN2, OUTPUT);
  pinMode(Z_IN3, OUTPUT);

  // Initialize the previous value array
  prevalue[0] = 0;
  prevalue[1] = 0;
  prevalue[2] = 0;
}

void loop() {
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
  } while (val != -1); // repeat until there are no more commas in the received data

  // Move the motor in the positive direction along the X axis
  while (prevalue[0] < value[0]) {

    
    for (prevalue [0]; prevalue[0] < value[0]; prevalue[0]++) {
      digitalWrite(X_IN2, HIGH);
      delay(10);
      digitalWrite(X_IN2, LOW);
      delay(10);
    }

    // Print the current position of the motor
    Serial.print(prevalue[0]);
    Serial.print(",");
    Serial.print(prevalue[1]);
    Serial.print(",");
    Serial.print(prevalue[2]);
  }

  // Move the motor in the positive direction along the Z axis
  while (prevalue[2] < value[2]) {

    for (prevalue [2]; prevalue[2] < value[2]; prevalue[2]++) {
      digitalWrite(Z_IN2, HIGH);
      delay(10);
      digitalWrite(Z_IN2, LOW);
      delay(10);
    }
    Serial.print(prevalue[0]);
    Serial.print(",");
    Serial.print(prevalue[1]);
    Serial.print(",");
    Serial.print(prevalue[2]);
  }
  // Move the motor in the negative direction along the Z axis
  while (prevalue[2] > value[2]) {

    for (prevalue [2]; prevalue[2] > value[2]; prevalue[2]--) {
      digitalWrite(Z_IN3, HIGH);
      delay(10);
      digitalWrite(Z_IN3, LOW);
      delay(10);
    }
    Serial.print(prevalue[0]);
    Serial.print(",");
    Serial.print(prevalue[1]);
    Serial.print(",");
    Serial.print(prevalue[2]);
  }
}
