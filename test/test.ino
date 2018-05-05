/*Smart Hospital Bed (SHB).
 * UNIVERSITY OF PETRA .
 * Graduation project 2017/2018.
 * This code takes reads from Sensors fixed on the SHB and compute them in order to calculate the pmw to be sent to each Motor.where Speed sensors
 * calculate how many turns each Motor spin per second,moreover accourding to phisical law (destance = speed / time) we can calculate for how long   
 * should the wheels turn and how much pwm we should provide. 
 * the UltraSonic sensors dedict nearby obsticals and decide whether to keep moving or stop.
 * and this code also recivecs reads from glove sent by bluetooth to control the SHB gusturly.
 */

#include <TimerOne.h> 
// this library Controls Speed sensors to specify the time needed to cross specific length.
#include<AFMotor.h>
// this library Controls the power sent to the Motors and its Dirictin.
#include "Turn.h"
// this library Controls the gyroscope to ensure 90 degree turns.

AF_DCMotor rightMotor(4); //create motor #1 using M4 output on Motor Drive Shield, set to 1kHz PWM frequency right motor
AF_DCMotor leftMotor(2); //create motor #2 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency left motor

int rightIRSensor; // to take reads from the right ir sensor 
int leftIRSensor; // to take reads from the right ir sensor 

Turnlib turn; // instance of turn to use turn library.
int theta; // the current theta of the SHB.
int target; // in which theta should the HBS turn to to ensure 90 degree turns.
int x;// hold the value opf the theta temporary 
int y; // hold the value of the target temporary

int normal = 150; // intial speed in which the SHB will start moving.
int sharp = 150; // turning speed 
int backward = 150; // backward speed in sharp turns.

const float stepcount = 20.00;  //Constant for steps in disk, 20 Slots in disk. 
const float wheeldiameter = 66.10; // Constant for wheel diameter ,Wheel diameter in millimeters.

// Integers for pulse counters
volatile int counter_A = 0;
volatile int counter_B = 0;

const byte MOTOR_A = 19;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 18;  // Motor 1 Interrupt Pin - INT 0 - Left Motor

//========== ULTRASONIC   ==============
const int trigPin = 32;
const int echoPin = 30;
// defines variables
   long duration;
   int distance;
//=================== State of the Glove ========
char state = 0;
// ==================== heart pulse
int PulseSensorPurplePin = 0; // pulse sensor reads from A0 pin 
int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore.
bool checkPulse = false; // start by button push
//=============== SETUP METHOD=========================
void setup() {
  Serial.begin(9600);
 // turn.Setup(); // necessarily to setup GyroScop mpu 5060.
  pinMode(A0, INPUT); // readings from right IR Sensor.
  pinMode(A3, INPUT); // readings from left IR Sensor.
  pinMode(42, OUTPUT); // red Blue LED for Obsticals.
  pinMode(50, OUTPUT); // left Blue LED.
  pinMode(52, OUTPUT); // right Blue LED.
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(36,OUTPUT); // top left green light
  pinMode(38,OUTPUT); // back left green light
  pinMode(40,OUTPUT); // back right
  pinMode(34,OUTPUT); // top right


  

// Attach the Interrupts to their ISR's
  attachInterrupt(digitalPinToInterrupt (MOTOR_A), ISR_countA, RISING);  // Increase counter A when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR_B), ISR_countB, RISING);  // Increase counter B when speed sensor pin goes High
  digitalWrite(42,LOW);
 //==================== BUTTONS ==============
  pinMode(33,INPUT);// Operation Room button Pin
  pinMode(35,INPUT);// take reads from pulse sensor
//==================buzzer==============
  pinMode(22,OUTPUT);
  
}

//=================== LOOP ================================
void loop() {
//Serial.println(turn.readAngle()); // prevent fifo OverFlow
 
  // ================ if Operation room button pressed=====
  if(digitalRead(33) == HIGH)
    {
      digitalWrite(50,HIGH); // turn the blue lights on 
      digitalWrite(52,HIGH); // turn the blue lights on
      MoveForward(200,normal);  // start moving forward 
      delay(500);  // wait one second
      SpinLeft(55,150); // spin to the left using gyroscope
      MoveForward(100,normal);  // start moving forward 
      delay(500); 
      SpinRight(60,150);
      
      digitalWrite(50,LOW); // turn the blue lights off 
      digitalWrite(52,LOW); // turn the blue lights off
       
    }// if
// ================ pulse button is pushed =====
 if(digitalRead(35) == HIGH)
    {
      
      
    }// if

  // ===================== TAKES READ FROM THE GLOVE IF AVALIABLE =========

if(Serial.read() != '7'){
    state = Serial.read();
    if(state == '1'){Glovebackward();
       digitalWrite(40,HIGH);
       digitalWrite(38,HIGH);
       digitalWrite(36,LOW);  
       digitalWrite(34,LOW); }
    if(state == '2'){Gloveforward();
       digitalWrite(40,LOW);
       digitalWrite(38,LOW);
       digitalWrite(36,HIGH);  
       digitalWrite(34,HIGH); }
    if(state == '3'){Gloveright();
       digitalWrite(40,HIGH);
       digitalWrite(38,LOW);
       digitalWrite(36,LOW);  
       digitalWrite(34,HIGH);}
     if(state == '4'){Gloveleft();
       digitalWrite(40,LOW);
       digitalWrite(38,HIGH);
       digitalWrite(36,HIGH);  
       digitalWrite(34,LOW); }
    if(state == '0'){GloveStop();
       digitalWrite(40,LOW);
       digitalWrite(38,LOW);
       digitalWrite(36,LOW);  
       digitalWrite(34,LOW); }
}// not equal 7 


if(Serial.read()== '7'){
   digitalWrite(40,LOW);
   digitalWrite(38,LOW);
   digitalWrite(36,LOW);  
   digitalWrite(34,LOW); }


    
   
}// LOOP


// ==============Interrupt Service Routines =================
// Motor A pulse count ISR
void ISR_countA()  
{
  counter_A++;  // increment Motor A counter value
} 

// Motor B pulse count ISR
void ISR_countB()  
{
  counter_B++;  // increment Motor B counter value
}

// ============convert from centimeters to steps ============

int CMtoSteps(float cm) {
  int result;  // Final calculation result
  float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
  float cm_step = circumference / stepcount;  // CM per Step
  float f_result = cm / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)
  return result;  // End and return result
}
//================ Move Forward ==================
void MoveForward(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A forward
   rightMotor.run(FORWARD);
   // Set Motor B forward
   leftMotor.run(FORWARD);
   
   // Go forward until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
//======== check Obsticals
    if(Calcdistance()<= 13){
    Stop();
    delay(100);
    digitalWrite(42,HIGH);
    delay(100);
    digitalWrite(42,LOW);
    tone(22,500,500);
    }//if
else{

   

 //  Serial.println(turn.readAngle());
   
    if (steps > counter_A) {
    rightMotor.setSpeed(mspeed);
    } else {
    rightMotor.setSpeed(0);
    }
    if (steps > counter_B) {
    leftMotor.setSpeed(mspeed);
    } else {
    leftMotor.setSpeed(0);
    }

}
   
   }//while 
    
  // Stop when done
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}//MOVE FORWARD

// ============ MoveReverse ==========================

void MoveReverse(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
   rightMotor.run(BACKWARD);
   // Set Motor B reverse
   leftMotor.run(BACKWARD);

   
   // Go in reverse until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    leftMotor.setSpeed(mspeed);
    } else {
    leftMotor.setSpeed(0);
    }
    if (steps > counter_B) {
    rightMotor.setSpeed(mspeed);
    } else {
    rightMotor.setSpeed(0);
    }
    }
    
  // Stop when done
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}


// ============ Spin Right  ========================

void SpinRight(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
   rightMotor.run(BACKWARD);
  
  // Set Motor B forward
  leftMotor.run(FORWARD); 
   // Go until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    rightMotor.setSpeed(mspeed);
    } else {
    rightMotor.setSpeed(0);
    }
    if (steps > counter_B) {
    leftMotor.setSpeed(mspeed);
    } else {
    leftMotor.setSpeed(0);
    }
   }
    
  // Stop when done
  rightMotor.setSpeed(0);
  leftMotor.setSpeed(0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}

// ============ Spin Left  ========================

void SpinLeft(int steps, int mspeed) 
{
   counter_A = 0;  //  reset counter A to zero
   counter_B = 0;  //  reset counter B to zero
   
   // Set Motor A reverse
   rightMotor.run(FORWARD);
  
  // Set Motor B forward
  leftMotor.run(BACKWARD); 
   // Go until step value is reached
   while (steps > counter_A && steps > counter_B) {
   
    if (steps > counter_A) {
    rightMotor.setSpeed(mspeed);
    } else {
    rightMotor.setSpeed(0);
    }
    if (steps > counter_B) {
    leftMotor.setSpeed(mspeed);
    } else {
    leftMotor.setSpeed(0);
    }
   }
    
  // Stop when done
  rightMotor.setSpeed(0);
  leftMotor.setSpeed(0);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}



// ============ Spin left gyro  ========================
 void spinLeftGyro(){   
    for(int i=0 ; i<300;i++){ // to prevent fifo Overflow
      theta = turn.readAngle();
     // Serial.print(theta);
     // Serial.println(" ");
                  }
     turn.fifoReset();             
    //======================= theta > 90 =============================
    if ( theta > 90) {
      target = theta - 85;
      while (theta > target) {
        leftMotor.setSpeed(backward);
        rightMotor.setSpeed(sharp);
        leftMotor.run(BACKWARD);
        rightMotor.run(FORWARD);
        theta = turn.readAngle();
       // Serial.print(theta);
      //  Serial.print(" ");
       /// Serial.print(target);
       // Serial.println("");}
        /*
        //====== adjesment =========
        for(int i=0 ; i<100 ; i++){
        if(theta < target - 5 ){
         LeftMotor.setSpeed(backward);
         RightMotor.setSpeed(sharp);
         LeftMotor.run(FORWARD);
         RightMotor.run(BACKWARD);
             }
        }//adjesemnt
        */
        }//while
    }
     // ===================== theta < 90 =============================
    else if (theta < 90 ) {
       x = 95 - theta;
       target = 360 - x;
while (true){
        while(theta <  target){
        leftMotor.setSpeed(backward);
        rightMotor.setSpeed(sharp);
        leftMotor.run(BACKWARD);
        rightMotor.run(FORWARD);
        theta = turn.readAngle();
      //// Serial.print(theta);
     //  Serial.print(" ");
     ///  Serial.print(target);
     //  Serial.println("");
        
        }

        while(theta > target){
        leftMotor.setSpeed(backward);
        rightMotor.setSpeed(sharp);
        leftMotor.run(BACKWARD);
        rightMotor.run(FORWARD);
        theta = turn.readAngle();
       // Serial.print(theta);
      ////  Serial.print(" ");
      //  Serial.print(target);
      //  Serial.println("");
                }
       break;
       }//while alkbereh
       /*
       //====== adjesment =========
       for(int i=0 ; i<100 ; i++){
        if(theta < target - 5 ){
         LeftMotor.setSpeed(backward);
         RightMotor.setSpeed(sharp);
         LeftMotor.run(FORWARD);
         RightMotor.run(BACKWARD);
             }
 
        }//adjesment
       */
    }//theta < 90

       
    leftMotor.setSpeed(0);
    rightMotor.setSpeed(0);
   
      }

 

// ============ SPIN RIGHT GYRO ========================
 void spinRightGyro(){   
    for(int i=0 ; i<300;i++){ // to prevent fifo Overflow
      theta = turn.readAngle();
    //  Serial.print(theta);
    //  Serial.println(" ");
           
                  }
     turn.fifoReset();             
    //======================= theta < 270 =============================
    if ( theta > 0 && theta < 270) {
      target = theta + 85;
      while (theta < target) {
        rightMotor.setSpeed(backward);
        leftMotor.setSpeed(sharp);
        leftMotor.run(FORWARD);
        rightMotor.run(BACKWARD);
        theta = turn.readAngle();
      //  Serial.print(theta);
       // Serial.print(" ");
      ////  Serial.print(target);
       // Serial.println("");}
        /*
        //====== adjesment =========
        for(int i=0 ; i<100 ; i++){
        if(theta < target - 5 ){
         LeftMotor.setSpeed(backward);
         RightMotor.setSpeed(sharp);
         LeftMotor.run(FORWARD);
         RightMotor.run(BACKWARD);
             }
        }//adjesemnt
        */
        }//theta< 270
    }
     // ===================== theta > 270 =============================
    else if (theta > 270 ) {
       y = 360 - theta;
       target = 95 - y;
while (true){
        while(theta >  target){
        leftMotor.setSpeed(170);
        rightMotor.setSpeed(150);
        leftMotor.run(FORWARD);
        rightMotor.run(BACKWARD);
        theta = turn.readAngle();
    //    Serial.print(theta);
    //    Serial.print(" ");
    //    Serial.print(target);
    //    Serial.println("");
        
        }

        while(theta < target){
        leftMotor.setSpeed(backward);
        rightMotor.setSpeed(sharp);
        leftMotor.run(FORWARD);
        rightMotor.run(BACKWARD);
        theta = turn.readAngle();
    //    Serial.print(theta);
    //    Serial.print(" ");
    //    Serial.print(target);
    //    Serial.println("");
                }
       break;
       }//while alkbereh
       /*
       //====== adjesment =========
       for(int i=0 ; i<100 ; i++){
        if(theta < target - 5 ){
         LeftMotor.setSpeed(backward);
         RightMotor.setSpeed(sharp);
         LeftMotor.run(FORWARD);
         RightMotor.run(BACKWARD);
             }
 
        }//adjesment
       */
    }//theta >270

       
    leftMotor.setSpeed(0);
    rightMotor.setSpeed(0);
   
    }
      
//=================== Calculate distance using Ultrasonic ===============

int Calcdistance(){
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
return distance= duration*0.034/2;
  }
//=================== Stop ===============

void Stop(){
  leftMotor.setSpeed(0);
  rightMotor.setSpeed(0);
  }
//============ moving forward when recieveing signal from glove==========
void Gloveforward(){
   //======== check Obsticals
    if(Calcdistance()<= 13){
    Stop();
    delay(100);
    digitalWrite(42,HIGH);
    delay(100);
    digitalWrite(42,LOW);
    tone(22,500,500);
    }//if
else{
     
   rightMotor.run(FORWARD);
   leftMotor.run(FORWARD);
   rightMotor.setSpeed(150);
   leftMotor.setSpeed(150);
}
       }
//============ moving backward when recieveing signal from glove==========       
void Glovebackward(){
  rightMotor.run(BACKWARD);
   leftMotor.run(BACKWARD);
   rightMotor.setSpeed(150);
   leftMotor.setSpeed(150);
   
  }
//============ moving to the left when recieveing signal from glove==========  
void Gloveleft(){
  rightMotor.run(FORWARD);
   leftMotor.run(BACKWARD);
   rightMotor.setSpeed(150);
   leftMotor.setSpeed(150);
}
//============ moving to the right when recieveing signal from glove==========
void Gloveright(){
  rightMotor.run(BACKWARD);
   leftMotor.run(FORWARD);
   rightMotor.setSpeed(150);
   leftMotor.setSpeed(150);
   
  }
//============ stop when recieveing signal from glove==========  
void GloveStop(){
   rightMotor.run(RELEASE);
   leftMotor.run(RELEASE);
   rightMotor.setSpeed(0);
   leftMotor.setSpeed(0);
   }

// ============== cheach heart beat ==========
void checkHeart(){
  Signal = analogRead(PulseSensorPurplePin);
  if(checkPulse == true){
  
if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     tone(22,500); } 
else if(Signal < 250){
    tone(22,1000);}
else {
     noTone(22);                //  Else, the sigal must be below "550", so "turn-off" this LED.}
  
  }
  
  }
}











