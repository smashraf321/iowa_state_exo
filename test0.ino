//Connect ground of Arduino and actuators

#include <Servo.h>

int sensorPin[] =   {A0, A1};
//int k[] =           {1,  1};
int neutralPoint[] = {447, 447};
int threshold = 10;
//int i = 0;
//int j = 0;

int recalButton = 8;
int offButton = 9;

int killswitch = 0;

Servo servos[2];

void setup()
{
  Serial.begin(9600);

  for (int i = 0; i < 2; i++)
  {
    pinMode(INPUT, sensorPin[i]);
  }

  pinMode(INPUT, recalButton);

  for (int i = 0; i < 2; i++) {
    servos[i].attach(31 + i);
  }

  recalibrate();
}


//analogRead ->  0-1024
//servo.write -> 0-180
//Zero ->        447 +- 2%

void loop()
{
  if (digitalRead(recalButton) == HIGH)
  {
    recalibrate();
  }

  if (digitalRead(offButton) == HIGH)
  {
    killswitch = 1;
    halt();
  }

  if (killswitch != 1)
  {
    for (int i = 0; i <= 1; i++)
    {
      int input = analogRead(sensorPin[i]);
      int error = input - neutralPoint[i] ;
      int output = map(input, 0, 1023, 0, 180);
//
//      if (i < 4) {
//        int second_input = analogRead(sensorPin[i + 8]);
//        if (abs(second_input - neutralPoint[i + 8]) > abs(error)) {
//          input = second_input * -1;
//          error = input - neutralPoint[i + 8];
//          output = map(input, 0, 1023, 0, 180);
//        }

        if (abs(error) >= threshold)
        {
          //servos[i].write(90 - output);
          servos[i].write(output);
        } else {
          servos[i].write(90);
        }

//      } else if (i == 4) {
//        if (error > 0 && abs(error) >= threshold) {
//          servos[4].write(90 - output);
//        } else if (error < 0 && abs(error) >= threshold) {
//          servos[5].write(90 - output);
//        } else {
//           servos[4].write(90);
//           servos[5].write(90);
//        }
//      } else if (i == 5) {
//        if (error > 0 && abs(error) >= threshold) {
//          servos[4].write(90 + output);
//        } else if (error < 0 && abs(error) >= threshold) {
//          servos[5].write(90 + output);
//        } else {
//           servos[4].write(90);
//           servos[5].write(90);
//        }
//      } else {
//        if (abs(error) >= threshold)
//        {
//          servos[i].write(90 - output);
//        } else {
//          servos[i].write(90);
//        }
//      }

    }

  }
}

void recalibrate()
{
  delay(1000);

  for (int i = 0; i < 2; i++)
  {
    neutralPoint[i] = analogRead(sensorPin[i]);
  }

  //TODO On board LED signal recalibration
}

void halt()
{
  for (int i = 0; i <= 2; i++) {
    servos[i].write(90);
  }

  exit(0);
  //delay(2000);
}
