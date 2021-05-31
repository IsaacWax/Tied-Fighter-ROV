//began with minirov code

/*#include <Servo.h>
 Servo thruster;     // create servo object to control the ESC
 Servo claw;
*/
//declare analog pins
int clawopencloseinput = A0;
int driveinput = A1;  // do we really need this? we could output the same signal from A3 if we wanted to (using the arduino as an amplifier)
int clawrotateinput = A2;
//declare digital pins
int tetherforward = 0;
int tetherreverse = 1;
int permissivepin = 4;
//declare output pins
int tetherwindera = 6;
int tetherwinderb = 7;
int clawopenclosea = 8;
int clawopencloseb = 9;
int clawrotatea = 10;
int clawrotateb = 11;
int futuresparea = 12;
int futurespareb = 13;

// initial values

int permissive=0;
int clawrotateval;
int clawopencloseval;
int tetherreverseval = 0;
int tetherforwardval= 0;

void setup() {
 Serial.begin(9600);
 Serial.println("<Arduino is ready>");
 pinMode(permissivepin,INPUT);
 pinMode(tetherwindera,OUTPUT);

 pinMode(tetherwinderb,OUTPUT);
 
 pinMode(clawopenclosea,OUTPUT);
 pinMode(clawopencloseb,OUTPUT);
pinMode(clawrotatea,OUTPUT);
pinMode(clawrotateb,OUTPUT);
// set all the motor control drivers to low
 digitalWrite(tetherwindera,LOW); 
 digitalWrite(tetherwinderb,LOW); 
 digitalWrite(clawopenclosea,LOW); 
 digitalWrite(clawopencloseb,LOW); 
 digitalWrite(clawrotatea,LOW); 
 digitalWrite(clawrotateb,LOW); 
}

void loop() {
permissive = digitalRead(permissivepin);
if (permissive=LOW)  { 
clawrotateval = analogRead(clawrotateinput);
clawopencloseval = analogRead(clawopencloseinput); 
}
tetherforwardval = digitalRead(tetherforward);
tetherreverseval = digitalRead(tetherreverse);


// this is where we instruct the motor drivers.

if (tetherforwardval = HIGH) 
  {
  digitalWrite(tetherwindera,HIGH);
  }
  else
  {
  digitalWrite(tetherwindera,LOW);  
  }
  
if (tetherreverseval = HIGH) {
  digitalWrite(tetherwinderb,HIGH);
  }
  else {
  digitalWrite(tetherwinderb,LOW);  
  }
  
if (clawopencloseval > 300 ) {
  digitalWrite(clawopenclosea,HIGH);
  }
else if (clawopencloseval < 200) {
  digitalWrite(clawopencloseb,HIGH);
  }
  else {
  digitalWrite(clawopenclosea,LOW);
  digitalWrite(clawopencloseb,LOW);  
  }
if (clawrotateval > 300 ) 
  {
  digitalWrite(clawrotatea,HIGH);
  }
else if (clawrotateval < 200) {
  digitalWrite(clawrotateb,HIGH);
  }
  else {
  digitalWrite(clawrotatea,LOW);
  digitalWrite(clawrotateb,LOW);  
  }
}
