/*Smart Hospital Bed (SHB).
 * UNIVERSITY OF PETRA .
 * Graduation project 2017/2018.
 * This code takes reads from Sensors fixed on the SHB and compute them in order to calculate the pmw to be sent to each Motor.where Speed sensors
 * calculate how many turns each Motor spin per second,moreover accourding to phisical law (destance = speed / time) we can calculate for how long   
 * should the wheels turn and how much pwm we should provide. 
 * the UltraSonic sensors dedict nearby obsticals and decide whether to keep moving or stop.
 */

 
#include "Turn.h"
// this library reads Gyroscope Data.

Turnlib turn; // instance of turn to use turn library.
bool on=false ; // to start or stop sending 
//=============== SETUP METHOD=========================
void setup() {
  turn.Setup(); // necessarily to setup GyroScop mpu 5060.
  Serial.begin(9600);
  pinMode(7,INPUT); // Green Button  
  pinMode(8,INPUT); // Red Button  
  pinMode(11,OUTPUT); // Green Light  
  pinMode(9,OUTPUT); // Red Light  

}

//=================== LOOP ================================
void loop() {
  

if(digitalRead(7)==HIGH){on=true;}
if(digitalRead(8)==HIGH){on=false;}
if(on == true){digitalWrite(11,HIGH);digitalWrite(9,LOW);
//start reading from gyroscope 
turn.readAngle();
}
if(on == false){digitalWrite(9,HIGH);digitalWrite(11,LOW);
Serial.write('7');
}



}// LOOP



