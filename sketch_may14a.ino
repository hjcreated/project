
//================================================
#define blueLeft 27 //blue light alocated under beaneth the SHB indicates the Start of the Automated movement.
#define blueRight 26 //blue light alocated under beaneth the SHB indicates the Start of the Automated movement.
#define topRight 24     //Green Light that indicates the start of the gestural movement.
#define topLeft 23      //Green Light that indicates the start of the gestural movement.
#define backRight 22    //Green Light that indicates the start of the gestural movement.
#define backLeft 25     //Green Light that indicates the start of the gestural movement.
#define in1 7   // FORWARD.
#define in2 9   // REVERSE.
#define enA 8   // left Motor power.
#define in3 11  // FORWARD.
#define in4 10  // REVERSE.
#define enB 12  // right Motor power.
#define Speed 100 // hold how much pwm to send to the motors
#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
//======================= OTHERS===========================
int state; // hold the value of Serial. 
const float stepcount = 20.00;  //Constant for steps in disk, 20 Slots in disk. 
const float wheeldiameter = 66.10; // Constant for wheel diameter ,Wheel diameter in millimeters.
// Integers for pulse counters
volatile int counter_A = 0;
volatile int counter_B = 0;
const byte MOTOR_A = 19;  // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 18;  // Motor 1 Interrupt Pin - INT 0 - Left Motor
// ====================== SETUP ===========================
void setup() {
Serial.begin(9600); // set the baud rate to start communication with the Blutooth fixed on the Glove
/* Detirmen the output mode for each pin with 
 * input or output 
 * output recives 3.3V since we are using arduino Due
 */
pinMode(blueLeft,OUTPUT); 
pinMode(blueRight,OUTPUT);
pinMode(topRight,OUTPUT);
pinMode(topLeft,OUTPUT);
pinMode(backRight,OUTPUT);
pinMode(backLeft,OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(MOTOR_A,INPUT);
pinMode(MOTOR_B,INPUT);
// Attach the Interrupts to their ISR's
attachInterrupt(19, ISR_countA, RISING);  // Increase counter A when speed sensor pin goes High
attachInterrupt(18, ISR_countB, RISING);  // Increase counter B when speed sensor pin goes High
MoveForward(50,150);
}//Setup

// ====================== LOOP ===========================
void loop() {
state = Serial.read(); // start reading from bluetooth
    if(state == '1'){
           /*
            * MOVING BACKWARD
            */
     Glovebackward();}//BACKWARD
    
    if(state == '2'){
       /*
        * MOVING FORWARD
        */
       Gloveforward();}//FORWARD
   
    if(state == '3'){
       /*
        * MOVING TOWARD RIGHT
        */
        Gloveright();}
     
     if(state == '4'){
      /*
       * MOVING TOWARD LEFT
       */
       Gloveleft();}//LEFT
    
    if(state == '0'){
       /*
        * STOP
        */
        GloveStop();}//STOP



}//Loop

/*
 * METHODS IN THIS SECTION IS DESIGE TO REACT WITH GLOVE READS(SERIAL READS)
 */
//============ moving forward when recieveing signal from glove==========
void Gloveforward(){
     if(measureFront() > 5){
     
     digitalWrite(backRight,LOW);
     digitalWrite(backLeft,LOW);
     digitalWrite(topLeft,HIGH);  
     digitalWrite(topRight,HIGH); 

analogWrite(enA,Speed); 
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);

analogWrite(enB,Speed); 
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
    }
    else{GloveStop();}
//state = Serial.read();

       }
//============ moving backward when recieveing signal from glove==========       
void Glovebackward(){
     digitalWrite(backRight,HIGH);
     digitalWrite(backLeft,HIGH);
     digitalWrite(topLeft,LOW);  
     digitalWrite(topRight,LOW); 
     
analogWrite(enA,Speed); 
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);

analogWrite(enB,Speed); 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
     

  }
//============ moving to the left when recieveing signal from glove==========  
void Gloveleft(){
     digitalWrite(backRight,LOW);
     digitalWrite(backLeft,HIGH);
     digitalWrite(topLeft,HIGH);  
     digitalWrite(topRight,LOW);

analogWrite(enA,Speed); 
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);

analogWrite(enB,Speed); 
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);

     
}
//============ moving to the right when recieveing signal from glove==========
void Gloveright(){
     digitalWrite(backRight,HIGH);
     digitalWrite(backLeft,LOW);
     digitalWrite(topLeft,LOW);  
     digitalWrite(topRight,HIGH);

analogWrite(enA,Speed); 
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);

analogWrite(enB,Speed); 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);

  }
//============ stop when recieveing signal from glove==========  
void GloveStop(){
     digitalWrite(backRight,LOW);
     digitalWrite(backLeft,LOW);
     digitalWrite(topLeft,LOW);  
     digitalWrite(topRight,LOW);

analogWrite(enA,Speed); 
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);

analogWrite(enB,Speed); 
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
     }

//================== measure Front =======================
/*
 * measure he front distance to check the case of obsticals before start moving
 */
int measureFront(){
// 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  return distance;   // print the distance
  }

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
   digitalWrite(in1, HIGH);
   digitalWrite(in2, LOW);
   // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
   
   // Go forward until step value is reached
   while (steps > counter_A && steps > counter_B) {
    Serial.println(steps);
    Serial.println(counter_A);
     
      if (steps > counter_A) {
      analogWrite(enA,mspeed); 
      } else {
      analogWrite(enA,0); 
    }
     if (steps > counter_B) {
      analogWrite(enB,mspeed); 
      } else {
      analogWrite(enB,0);
    }
 }//while 
    
  // Stop when done
  analogWrite(enA,0); 
  analogWrite(enB,0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero 

}//MOVE FORWARD
/*
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

*/


