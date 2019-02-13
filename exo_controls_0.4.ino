//Connect ground of Arduino and actuators

#include <Servo.h>

Servo testServo;

int dir;

void setup()
{
  Serial.begin(9600);

  pinMode(39, OUTPUT);
  pinMode(40, OUTPUT);

  dir = HIGH;

}


//analogRead ->  0-1024
//servo.write -> 0-180
//Zero ->        447 +- 2%

//analogWrite worked on pin 42 but only full speed each direction
//On Mega boards, pins 2-13 and 44-46 analogWrite(pin, <0-255>) will write a PWM signal that should work for us
//TODO look into the Servo library, I saw something that might be useful
void loop()
{
  //Direction: HIGH OR LOW
  digitalWrite(39, dir);
  digitalWrite(40, dir);
  
  for(int i = 0; i < 255; i += 10){
    //testServo.writeMicroseconds(i);
    analogWrite(9, i);
    analogWrite(10, i);
    Serial.print(i);
    Serial.print(" | ");
    delay(1000);
  }
    if(dir == LOW){
      dir = HIGH;
    } else {
      dir = LOW;
    } 
}

