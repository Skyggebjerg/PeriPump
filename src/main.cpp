#include <Arduino.h>
#include <M5Atom.h>
#include "StepperDriver.h"
#include "FastLED.h"

int motor_steps = 200;
int step_divisition = 32; //32
int en_pin = 22;
int dir_pin = 23;
int step_pin = 19;
unsigned long startTime;
unsigned long elapsedTime;

int step = 0;
int speed = 0;

StepperDriver ss(motor_steps, step_divisition, en_pin, dir_pin, step_pin);

void setup()
{
  M5.begin(true, false, true);
  Serial.begin(115200);
  pinMode(32, INPUT_PULLDOWN); // set pin mode to input
  pinMode(26, OUTPUT);
  digitalWrite(26, LOW);
  ss.powerEnable(false);
  ss.setSpeed(0);
  delay(1600);

}

void loop()
{
   if(M5.Btn.wasPressed()) {
    //for (int i = 1; i <= 30; i++) {
      while (1)

      {
      startTime = millis();     
      ss.powerEnable(true);
      ss.setSpeed(600); // 60 = 60 revolutions per minute (rpm) = 1 rev per sec (There are 6.5 revs per 100 µl)
      Serial.println("AspirateStart:-750");
      ss.step(-750,100,100); //aspirate (1300 steps = 6.5 revs = 100 µl)
      Serial.println("AspirateEnd:-750");
      delay(100);
      
      //ss.setSpeed(5); // 5 revs/min = 300 revs/h = 46.15 full syringe strokes (300/6.5) = 4615 µl per hour (46 x 100µl) 
      //ss.setSpeed(1); // 1 revs/min = 60 revs/h = 9.23 full syringe strokes (60/6.5) = 923 µl per hour (9.23 x 100µl)
      ss.setSpeed(16); // 14 revs/min = 12.922 µl/h (14 x 923 µl)
      //ss.setSpeed(3); // 3 revs/min = 2.77 ml/h (3 x 923 µl)   
      Serial.println("DispenseStart:750");
      ss.step(750); //dispense
      Serial.println("DispenseEnd:750");
      delay(100);

      ss.powerEnable(false);
      M5.update();
      if(M5.Btn.wasPressed()) {
        break;
      }
      delay(1000);
      elapsedTime = millis() - startTime;
      Serial.print("Elapsed:");
      Serial.println(elapsedTime);
   //  delay(500); // include in for loop
   //} // for loop end
   }
         }
         M5.update();
}