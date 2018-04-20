
/*Smart Hospital Bed (SHB).
 * UNIVERSITY OF PETRA .
 * Graduation project 2017/2018.
 * This code takes reads from Sensors fixed on the SHB and compute them in order to calculate the pmw to be sent to each Motor.where Speed sensors
 * calculate how many turns each Motor spin per second,moreover accourding to phisical law (destance = speed / time) we can calculate for how long   
 * should the wheels turn and how much pwm we should provide. 
 * the UltraSonic sensors dedict nearby obsticals and decide whether to keep moving or stop.
 */
#include <SoftwareSerial.h>

#include "Turn.h"
// this library reads Gyroscope Data.

Turnlib turn; // instance of turn to use turn library.
int theta; // the current theta of the SHB.
//=============== SETUP METHOD=========================
void setup() {
  turn.Setup(); // necessarily to setup GyroScop mpu 5060.
  Serial.begin(9600);

}

//=================== LOOP ================================
void loop() {
  //start reading from gyroscope 
turn.readAngle();

if((turn.readUp()>-8 && turn.readUp()<8) &&(turn.readLeft()>20)){Serial.println("Right");}// Turnning right
if((turn.readUp()>-8 && turn.readUp()<8) &&(turn.readLeft()<-20)){Serial.println("Left");}// Turnning left
if((turn.readLeft()>-20 && turn.readLeft()<20) &&(turn.readUp()>20)){Serial.println("Up");}// Turnning up
if((turn.readLeft()>-20 && turn.readLeft()<20) &&(turn.readUp()<-20)){Serial.println("Down");}// Turnning Down
if((turn.readLeft()>-20 && turn.readLeft()<20)&&(turn.readUp()>-8 && turn.readUp()<8)){Serial.println("Stop");}//Stop






}// LOOP



