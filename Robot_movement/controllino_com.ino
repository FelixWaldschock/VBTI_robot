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
bool temp15 = false;
bool temp16 = false;
bool temp17 = false;
bool prox_sen = false;
bool home_sequence = false;
bool stop_upward_movement = false;
bool stop_downward_movement = false;
int timer1 = 1000;
int timer2 = 100;


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
  pinMode(CONTROLLINO_A7, INPUT);
  pinMode(CONTROLLINO_IN0, INPUT);
  pinMode(CONTROLLINO_IN1, INPUT);
  // Initialize the previous value array



  Serial.begin(115200);
  //Serial.print("2");


  digitalWrite(CONTROLLINO_D1, HIGH);
  digitalWrite(CONTROLLINO_D6, HIGH);
  digitalWrite(CONTROLLINO_D11, HIGH);
  delay(500);
  digitalWrite(CONTROLLINO_D1, LOW);
  digitalWrite(CONTROLLINO_D6, LOW);
  digitalWrite(CONTROLLINO_D11, LOW);
  home_lift();
  attachInterrupt(digitalPinToInterrupt(CONTROLLINO_IN0), stop_motor_down, RISING);
  attachInterrupt(digitalPinToInterrupt(CONTROLLINO_IN1), stop_motor_above, RISING);
}

void stop_motor_down() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);
  prevalue[1] = 0;
  value[1] = 0;
  position2b();
  stop_downward_movement = true;
}
void stop_motor_above() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);
  prevalue[1] = 290;
  value[1] = 290;
  position8b();
  stop_upward_movement = true;
}

void home_lift() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);
  prox_sen = digitalRead(CONTROLLINO_IN0);
  while (prox_sen != HIGH) {
    prox_sen = digitalRead(CONTROLLINO_IN0);
  }
  position2b();
  //Serial.print("1");
  home_sequence = true;


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
  delay(timer1);
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
  delay(timer1);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);

  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D2, LOW);

  digitalWrite(CONTROLLINO_D7, LOW);

  delay(timer2);
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
  delay(timer1);
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


  delay(timer2);
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
  delay(timer1);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D3, LOW);

  digitalWrite(CONTROLLINO_D8, LOW);


  delay(timer2);
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
  delay(timer1);
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

  delay(timer2);
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
  delay(timer1);
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

  delay(timer2);
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
  delay(timer1);
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

  delay(timer2);
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
  delay(timer1);
  temp1 = digitalRead(CONTROLLINO_A1);
  temp2 = digitalRead(CONTROLLINO_A2);
  while ((temp1 == HIGH) && (temp2 == HIGH)) {
    temp1 = digitalRead(CONTROLLINO_A1);
    temp2 = digitalRead(CONTROLLINO_A2);
  }
  digitalWrite(CONTROLLINO_D4, LOW);

  digitalWrite(CONTROLLINO_D9, LOW);

  delay(timer2);
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
  delay(timer1);
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

  delay(timer2);
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
  delay(timer1);
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

  delay(timer2);
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
  delay(timer1);
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
  delay(timer2);
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
  delay(timer1);
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


  delay(timer2);
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
  delay(timer1);
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
  delay(timer2);
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
  delay(timer1);
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

  delay(timer2);
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
  delay(timer1);
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

  delay(timer2);
}

//position z axis:
void position0b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer1);
}

void position1b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);

  delay(timer2);
}


void position2b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);

  delay(timer2);
}

void position3b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(timer2);
}

void position4b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(timer2);
}

void position5b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(timer2);
}

void position6b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);

  delay(timer2);
}

void position7b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer2);
}

void position8b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(timer2);
}

void position9b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  prox_sen = digitalRead(CONTROLLINO_A7);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(timer2);
}

void position10b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  prox_sen = digitalRead(CONTROLLINO_A7);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(timer2);
}

void position11b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  prox_sen = digitalRead(CONTROLLINO_A7);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);



  delay(timer2);
}

void position12b() {
  digitalWrite(CONTROLLINO_D11, HIGH);
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  prox_sen = digitalRead(CONTROLLINO_A7);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);

  delay(timer2);
}

void position13b() {
  digitalWrite(CONTROLLINO_D11, LOW);
  digitalWrite(CONTROLLINO_D12, HIGH);
  digitalWrite(CONTROLLINO_D13, HIGH);
  digitalWrite(CONTROLLINO_D14, HIGH);

  delay(timer1);
  temp5 = digitalRead(CONTROLLINO_A5);
  temp6 = digitalRead(CONTROLLINO_A6);
  prox_sen = digitalRead(CONTROLLINO_A7);
  while ((temp5 == HIGH) && (temp6 == HIGH)) {
    temp5 = digitalRead(CONTROLLINO_A5);
    temp6 = digitalRead(CONTROLLINO_A6);
  }
  digitalWrite(CONTROLLINO_D12, LOW);
  digitalWrite(CONTROLLINO_D13, LOW);
  digitalWrite(CONTROLLINO_D14, LOW);


  delay(timer2);
}


void loop() {
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
  } while (val != -1);  // repeat until there are no more commas in the received data

  // Move the motor in the positive direction along the X axis(forward rails)
  if ((prevalue[0] == value[0]) && (prevalue[1] == value[1]))
  {
    temp17 = true;
  }


  while ((prevalue[0] != value[0])) {
    //Serial.println("eerste while loop");
    temp16 = true;
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
    } else if ((-prevalue[0] + value[0]) >= 1) {
      position1();
      prevalue[0] = prevalue[0] + 1;
    }

    else if ((prevalue[0] - value[0]) >= 250) {
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

    } else if ((prevalue[0] - value[0]) >= 1) {
      position8();
      prevalue[0] = prevalue[0] - 1;

    }
  }

  while (prevalue[1] != value[1]) {
    //Serial.println("in while loop");
    temp16 = true;
    if (((-prevalue[1] + value[1]) >= 250) && stop_upward_movement == false) {
      prevalue[1] = prevalue[1] + 250;
      position7b();
    } else if (((-prevalue[1] + value[1]) >= 100) && stop_upward_movement == false) {
      prevalue[1] = prevalue[1] + 100;
      position6b();
    } else if (((-prevalue[1] + value[1]) >= 50) && stop_upward_movement == false) {
      prevalue[1] = prevalue[1] + 50;
      position5b();
    } else if (((-prevalue[1] + value[1]) >= 25) && stop_upward_movement == false) {
      prevalue[1] = prevalue[1] + 25;
      position4b();
    } else if (((-prevalue[1] + value[1]) >= 10) && stop_upward_movement == false) {
      prevalue[1] = prevalue[1] + 10;
      position3b();
    } else if (((-prevalue[1] + value[1]) >= 5) && stop_upward_movement == false) {
      prevalue[1] = prevalue[1] + 5;
      position2b();
    } else if (((-prevalue[1] + value[1]) >= 1) && stop_upward_movement == false) {
      prevalue[1] = prevalue[1] + 1;
      position1b();
    }

    // Z-axis down


    else if (((prevalue[1] - value[1]) >= 100)  && stop_downward_movement == false) {
      prevalue[1] = prevalue[1] - 100;
      position13b();
    } else if (((prevalue[1] - value[1]) >= 50)  && stop_downward_movement == false) {
      prevalue[1] = prevalue[1] - 50;
      position12b();
    } else if (((prevalue[1] - value[1]) >= 25)  && stop_downward_movement == false) {
      prevalue[1] = prevalue[1] - 25;
      position11b();
    } else if (((prevalue[1] - value[1]) >= 10)  && stop_downward_movement == false) {
      prevalue[1] = prevalue[1] - 10;
      position10b();  
    } else if (((prevalue[1] - value[1]) >= 5)  && stop_downward_movement == false) {
      prevalue[1] = prevalue[1] - 5;
      position9b();
    } else if (((prevalue[1] - value[1]) >= 1)  && stop_downward_movement == false) {
      prevalue[1] = prevalue[1] - 1;
      position8b();
    }
  }

  // sent values 1 to raspberry pi that motors are at correct position
  if (((prevalue[0] == value[0]) && (prevalue[1] == value[1]) && temp16 == true) || temp17 == true)
  {
    stop_downward_movement = false;
    stop_upward_movement = false;
    Serial.print("1");
    temp16 = false;
    temp17 = false;
  }
}

//|| stop_upward_movement == true || stop_downward_movement == true || home_sequence == true
