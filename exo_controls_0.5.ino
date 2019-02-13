//Connect ground of Arduino and actuators

int sensorPin[] = { A0 }; // , A1 , A2 , A3 , A4 , A5 , A6 , A7 };
int digWArr[] = { 39 };// , 40 , 41 , 42 , 43 , 44 , 45 , 46 , 47 };
int anaWArr[] = { 9 }; // , 10 , 0 , 0 , 0 , 0 , 0 , 0 };
int neutralPoint[] = { 447 };//, 447 , 447 , 447 , 447 , 447 , 447 , 447 };

int recallButton = 8;
int offButton = 7;

int dir;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < (sizeof(sensorPin) / sizeof(int)); i++) {
    pinMode(sensorPin[i], INPUT);
    pinMode(digWArr[i], OUTPUT);
  }

  pinMode(recallButton, INPUT);
  pinMode(offButton, INPUT);

  dir = HIGH;

  recalibrate();
}


//analogRead ->  0-1023
//Zero ->        447 +- 2%

void loop() {
  if (digitalRead(recallButton) == HIGH) {
    recalibrate();
  }

  if (digitalRead(offButton) == HIGH) {
    halt();
  }

  for (int i = 0; i < (sizeof(sensorPin) / sizeof(int)); i++) {
    int input = analogRead(sensorPin[i]);
    int moveVal = input - neutralPoint[i];
    int output = map(abs(moveVal), 0, 1023, 190, 255);

    if (moveVal < 0) {
      dir = LOW;
    } else {
      dir = HIGH;
    }

    digitalWrite(digWArr[i], dir);
    analogWrite(anaWArr[i], output);

    if (moveVal != 0) {
      Serial.print("Actuator: ");
      Serial.print(anaWArr[i], DEC);
      Serial.print(" | ");
      Serial.print(moveVal, DEC);
      Serial.print(" | ");
      Serial.println(output, DEC);
    }
  }
}

void recalibrate() {
  delay(1000);

  for (int i = 0; i < sizeof(sensorPin); i++)
    neutralPoint[i] = analogRead(sensorPin[i]);

  //TODO On board LED signal recalibration
}

void halt() {
  while (digitalRead(offButton) == HIGH) {
    delay(2000);
  }
}
