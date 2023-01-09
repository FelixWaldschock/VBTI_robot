// for the raspberry pi we can make an UI for inserting parameters:
//for the distance of the rails(x-axis), the height of the plants(z-axis), the steps for taking the pictures(z-axis/steps)
//optional: a library with the pictures and the corresponding coordinates
#include <Controllino.h> /* Usage of CONTROLLINO library allows you to use CONTROLLINO_xx aliases in your sketch. */

int val1 = 0;  //val1 = X position
int val2 = 0;  //val2 = Y position
int val3 = 0;  //val3 = Z position
bool temp1 = 0;
bool temp2 = 0;
bool temp5 = 0;
bool temp6 = 0;

String data;     // variable to store the received data string
String subData;  // variable to store a substring of the received data

// array to store the parsed values from the received data
int value[3];

// array to store the previous values
int prevalue[3];

int position[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

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

  pinMode(CONTROLLINO_A1, INPUT);  // Set the pin CONTROLLINO_R0 as OUT1 left - Read digital value at the pin A1.
  pinMode(CONTROLLINO_A2, INPUT);  // Set the pin CONTROLLINO_R1 as OUT2 left - Read digital value at the pin A2.

  pinMode(CONTROLLINO_A3, INPUT);  // Set the pin CONTROLLINO_A3 as OUT1 right - Read digital value at the pin A3.
  pinMode(CONTROLLINO_A4, INPUT);  // Set the pin CONTROLLINO_A4 as OUT2 right - Read digital value at the pin A4.

  pinMode(CONTROLLINO_D10, OUTPUT);  //Set the pin CONTROLLINO_D5 as IN0 lift.
  pinMode(CONTROLLINO_D11, OUTPUT);  //Set the pin CONTROLLINO_D6 as IN1 lift.
  pinMode(CONTROLLINO_D12, OUTPUT);  //Set the pin CONTROLLINO_D7 as IN2 lift.
  pinMode(CONTROLLINO_D13, OUTPUT);  //Set the pin CONTROLLINO_D8 as IN3 lift.
  pinMode(CONTROLLINO_D14, OUTPUT);  //Set the pin CONTROLLINO_D9 as IN4 lift.

  pinMode(CONTROLLINO_A5, INPUT);  // Set the pin CONTROLLINO_A5 as OUT1 lift - Read digital value at the pin A5.
  pinMode(CONTROLLINO_A6, INPUT);  // Set the pin CONTROLLINO_A6 as OUt2 lift - Read digital value at the pin A6.

  // Initialize the previous value array
  prevalue[0] = 0;
  prevalue[1] = 0;
  prevalue[2] = 0;

  Serial.begin(115200);

  //digitalWrite(CONTROLLINO_D5, HIGH);
  digitalWrite(CONTROLLINO_D1, HIGH);
  delay(500);
  digitalWrite(CONTROLLINO_D1, LOW);
  
  digitalWrite(CONTROLLINO_D6, HIGH);
  delay(500);
  digitalWrite(CONTROLLINO_D6, LOW);
  
  digitalWrite(CONTROLLINO_D11, HIGH);
  delay(500);
  digitalWrite(CONTROLLINO_D11, LOW);
}

void position0() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(100);
}

void position1() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(1000);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D2, LOW);

  digitalWrite(CONTROLLINO_D7, LOW);

  delay(10);
}


void position2() {
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);


  delay(10);
}

void position3() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D3, LOW);

  digitalWrite(CONTROLLINO_D8, LOW);


  delay(10);
}

void position4() {
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);

  delay(10);
}

void position5() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);

  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);

  delay(10);
}

void position6() {
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);

  delay(10);
}

void position7() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D9, LOW);

  delay(10);
}

void position8() {
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);

  delay(10);
}

void position9() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);

  delay(10);
}

void position10() {
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(10);
}

void position11() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);


  delay(10);
}

void position12() {
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);
  delay(10);
}

void position13() {
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);

  delay(10);
}

void position14() {
  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D2, HIGH);
  digitalWrite(CONTROLLINO_D3, HIGH);
  digitalWrite(CONTROLLINO_D4, HIGH);

  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D7, HIGH);
  digitalWrite(CONTROLLINO_D8, HIGH);
  digitalWrite(CONTROLLINO_D9, HIGH);
  delay(100);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D2, LOW);
  digitalWrite(CONTROLLINO_D3, LOW);
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D7, LOW);
  digitalWrite(CONTROLLINO_D8, LOW);
  digitalWrite(CONTROLLINO_D9, LOW);

  delay(10);
}

//position z axis:
void position0b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(100);
}

void position1b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);

  delay(10);
}


void position2b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);

  delay(10);
}

void position3b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(10);
}

void position4b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(10);
}

void position5b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(10);
}

void position6b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(10);
}

void position7b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(10);
}

void position8b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(10);
}

void position9b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(10);
}

void position10b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(10);
}

void position11b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);



  delay(10);
}

void position12b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(10);
}

void position13b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(10);
}

void position14b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);


  delay(100);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);



  delay(10);
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
  while (Serial.available() == 0)
    ;

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
  } while (val != -1);  // repeat until there are no more commas in the received data

  // Move the motor in the positive direction along the X axis(forward rails)
  if (value[0] == 0 && value[1] == 0 && value[2] == 0) {
    Serial.print("1");
  }

  while (prevalue[0] != value[0]) {
    if ((-prevalue[0] + value[0]) >= 250) {
      position7();
      prevalue[0] = prevalue[0] + 250;
    } else if ((-prevalue[0] + value[0]) >= 100) {
      position6();
      prevalue[0] = prevalue[0] + 100;
    } else if ((-prevalue[0] + value[0]) >= 50) {
      position5();
      prevalue[0] = prevalue[0] + 50;
    } else if ((-prevalue[0] + value[0]) >= 25) {
      position4();
      prevalue[0] = prevalue[0] + 25;
    } else if ((-prevalue[0] + value[0]) >= 10) {
      position3();
      prevalue[0] = prevalue[0] + 10;
    } else if ((-prevalue[0] + value[0]) >= 5) {
      position2();
      prevalue[0] = prevalue[0] + 5;
      Serial.println("move 2");
    } else if ((-prevalue[0] + value[0]) >= 1) {
      position1();
      prevalue[0] = prevalue[0] + 1;
      Serial.println("move 1");
    }

    if ((prevalue[0] - value[0]) >= 250) {
      position14();
      prevalue[0] = prevalue[0] - 250;
    } else if ((prevalue[0] - value[0]) >= 100) {
      position13();
      prevalue[0] = prevalue[0] - 100;
    } else if ((prevalue[0] - value[0]) >= 50) {
      position12();
      prevalue[0] = prevalue[0] - 50;
    } else if ((prevalue[0] - value[0]) >= 25) {
      position11();
      prevalue[0] = prevalue[0] - 25;
    } else if ((prevalue[0] - value[0]) >= 10) {
      position10();
      prevalue[0] = prevalue[0] - 10;
    } else if ((prevalue[0] - value[0]) >= 5) {
      position9();
      prevalue[0] = prevalue[0] - 5;
      Serial.println("move -2");
    } else if ((prevalue[0] - value[0]) >= 1) {
      position8();
      prevalue[0] = prevalue[0] - 1;
      Serial.println("move -1");
    }
  }
  //check the position wanted by raspberry pi. make a calculation to get to the same position. check all positions (1 to 14).
  //when a position is greater than the wanted position, take the previous position. subtract this position from the wanted position. repeat untill wanted position is 0.
  /*for (prevalue[0]; prevalue[0] < value[0]; prevalue[0]++) {
      if (prevalue[0] == value[0]) {
        //value[0] - position lower than prevalue[0]
        //void position?();
        //prevalue[0] = 0;
        else if (value[0] == 0) {
          void position0();
        }

        //
      }





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
  */
  /* Move the motor in the negative direction along the X axis(backward rails)
  while (prevalue[0] > value[0]) {
    prevalue[0] = value[0] + prevalue[0];
    if (prevalue[0] >= 250) {
      void position14();
      prevalue[0] = prevalue[0] + 250;
    } else if (prevalue[0] >= 100) {
      void position13();
      prevalue[0] = prevalue[0] + 100;
    } else if (prevalue[0] >= 50) {
      void position12();
      prevalue[0] = prevalue[0] + 50;
    } else if (prevalue[0] >= 25) {
      void position11();
      prevalue[0] = prevalue[0] + 25;
    } else if (prevalue[0] >= 10) {
      void position10();
      prevalue[0] = prevalue[0] + 10;
    } else if (prevalue[0] >= 5) {
      void position9();
      prevalue[0] = prevalue[0] + 5;
    } else if (prevalue[0] >= 1) {
      void position8();
      prevalue[0] = prevalue[0] + 1;
    }

    /*for (prevalue[0]; prevalue[0] > value[0]; prevalue[0]--) {
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
*/
// Move the motor in the positive direction along the Z axis(lift up)
while (prevalue[2] != value[2]) {
  if ((-prevalue[2] + value[2]) >= 250) {
    position7b();
    prevalue[2] = prevalue[2] + 250;
  } else if ((-prevalue[2] + value[2]) >= 100) {
    position6b();
    prevalue[2] = prevalue[2] + 100;
  } else if ((-prevalue[2] + value[2]) >= 50) {
    position5b();
    prevalue[2] = prevalue[2] + 50;
  } else if ((-prevalue[2] + value[2]) >= 25) {
    position4b();
    prevalue[2] = prevalue[2] + 25;
  } else if ((-prevalue[2] + value[2]) >= 10) {
    position3b();
    prevalue[2] = prevalue[2] + 10;
  } else if ((-prevalue[2] + value[2]) >= 5) {
    position2b();
    prevalue[2] = prevalue[2] + 5;
    Serial.println("move 2");
  } else if ((-prevalue[2] + value[2]) >= 1) {
    position1b();
    prevalue[2] = prevalue[2] + 1;
    Serial.println("move 1");
  }

// Z-axis down

  if ((prevalue[2] - value[2]) >= 250) {
    position14b();
    prevalue[2] = prevalue[2] - 250;
  } else if ((prevalue[2] - value[2]) >= 100) {
    position13b();
    prevalue[2] = prevalue[2] - 100;
  } else if ((prevalue[2] - value[2]) >= 50) {
    position12b();
    prevalue[2] = prevalue[2] - 50;
  } else if ((prevalue[2] - value[2]) >= 25) {
    position11b();
    prevalue[2] = prevalue[2] - 25;
  } else if ((prevalue[2] - value[2]) >= 10) {
    position10b();
    prevalue[2] = prevalue[2] - 10;
  } else if ((prevalue[2] - value[2]) >= 5) {
    position9b();
    prevalue[2] = prevalue[2] - 5;
    Serial.println("move -2");
  } else if ((prevalue[2] - value[2]) >= 1) {
    position8b();
    prevalue[2] = prevalue[2] - 1;
    Serial.println("move -1");
  }
}
}





/*while (prevalue[2] < value[2]) {
    prevalue[0] = value[0] - prevalue[0];
    if (prevalue[0] >= 250) {
      void position7();
      prevalue[0] = prevalue[0] - 250;
    } else if (prevalue[0] >= 100) {
      void position6();
      prevalue[0] = prevalue[0] - 100;
    } else if (prevalue[0] >= 50) {
      void position5();
      prevalue[0] = prevalue[0] - 50;
    } else if (prevalue[0] >= 25) {
      void position4();
      prevalue[0] = prevalue[0] - 25;
    } else if (prevalue[0] >= 10) {
      void position3();
      prevalue[0] = prevalue[0] - 10;
    } else if (prevalue[0] >= 5) {
      void position2();
      prevalue[0] = prevalue[0] - 5;
    } else if (prevalue[0] >= 1) {
      void position1();
      prevalue[0] = prevalue[0] - 1;
    }




    /*for (prevalue[2]; prevalue[2] < value[2]; prevalue[2]++) {
        //digitalWrite(CONTROLLINO_D12, HIGH);
        digitalWrite(CONTROLLINO_D2, HIGH);
        delay(15);
        temp1 = digitalRead(CONTROLLINO_A1);
        temp2 = digitalRead(CONTROLLINO_A2);
        while ((temp1 == LOW) && (temp2 == HIGH)) {
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
  prevalue[0] = value[0] + prevalue[0];
  if (prevalue[0] >= 250) {
    void position14();
    prevalue[0] = prevalue[0] + 250;
  } else if (prevalue[0] >= 100) {
    void position13();
    prevalue[0] = prevalue[0] + 100;
  } else if (prevalue[0] >= 50) {
    void position12();
    prevalue[0] = prevalue[0] + 50;
  } else if (prevalue[0] >= 25) {
    void position11();
    prevalue[0] = prevalue[0] + 25;
  } else if (prevalue[0] >= 10) {
    void position10();
    prevalue[0] = prevalue[0] + 10;
  } else if (prevalue[0] >= 5) {
    void position9();
    prevalue[0] = prevalue[0] + 5;
  } else if (prevalue[0] >= 1) {
    void position8();
    prevalue[0] = prevalue[0] + 1;
  }


  /*
        for (prevalue[2]; prevalue[2] > value[2]; prevalue[2]--) {
          //digitalWrite(CONTROLLINO_D12, HIGH);
          digitalWrite(CONTROLLINO_D3, HIGH);
          delay(15);
          temp1 = digitalRead(CONTROLLINO_A1);
          temp2 = digitalRead(CONTROLLINO_A2);
          while ((temp1 == LOW) && (temp2 == HIGH)) {
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
*/


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
