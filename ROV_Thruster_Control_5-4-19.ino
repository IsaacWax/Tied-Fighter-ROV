/*
The controls for the ROV will be
  Left Stick - Up/down the water column
  Right Stick - X-axis = Yaw, Y-axis = forward/back

4/4/19 update boxes out noisy values between +/- 30%...
5/4/19 update
*/

#include <Servo.h>  //For driving the ESCs and Servos
Servo up;
Servo up2;
Servo right;
Servo left;
Servo side;
// here are my pin assignments (in the global variable area)
//INPUTS

int forwardin=A2;
int upin=A3;
int sidein2 = A4;  //new side thrusters
int sidein=A5;
int chilling=2;  //Eric changed to available Pin

//OUTPUTS
int sideout = 10;
int upPin2 = 3;
int upPin = 9;
int rightPin = 5;
int leftPin = 6;

// Set initial values of working variables.
int var=0;
int Totalizer=0;
int Limiter=175;
int relax=1;

// Set initial values for raw data from controller
int UpVal = 0; //Value read off the PS2 Left Stick up/down
int UpVal2 = 0;  // output mirrors UpVal for the other up motor
int ForwardVal = 0;
int YawLeftVal = 0;  

// These are the data values from the controller, tranlated to motors.
int RightVal = 0;  
int LeftVal = 0;  //Value read off the PS2 Right Stick left/right
int sideval= 0;

/*/ These are logic tools to keep us from overloading the power needs
int Totalizer = 100;
int Limiter = 400;  //We will change this experimentally to make sure we don't exceed 12 AMPS ..started at 150.. bumped to 250
*/
// this are used to Slow the reaction from the controls
int lastuv=0;
int lastlf=0;
int lastrf=0;
int slow=30; //% of slow changed from 40 to 30 on 5/4/19
int HLraw = 0;
int HRraw = 0;

void setup()  {

// initialize the thrusters.
// up thruster
   up.attach(upPin);
   up.writeMicroseconds(1500);
   delay(1000);
// up thruster # 2
   up2.attach(upPin2);
   up2.writeMicroseconds(1500);
   delay(1000);
// left thruster
   left.attach(leftPin);
   left.writeMicroseconds(1500);
   delay(1000);
// right thruster
   right.attach(rightPin);
   right.writeMicroseconds(1500);
   delay(1000);
   side.attach(sideout);
   side.writeMicroseconds(1500);
   delay(3000);
  Serial.begin(9600);
}

void loop()
{
//power limiting switch
if (digitalRead(chilling) == HIGH) {
  relax=2;
}
else {
  relax=1;
}

//Analogue Stick readings
  sideval = map(analogRead(sidein2),0,1023,-100,100)*.8/relax;  // I mapped this from 80 to -80 to limit its power
  ForwardVal = map(analogRead(forwardin),0,1023,100,-100)/relax;
  YawLeftVal = map(analogRead(sidein),0,1023,100,-100)/relax;  //this is where we change if it left and right is backwards
  UpVal = map(analogRead(upin),0,1023,100,-100)/relax;
 
// Translate to left and right motors  

  LeftVal = (ForwardVal)+(YawLeftVal);  //This will be up to a value of 200
  RightVal = (ForwardVal)-(YawLeftVal);  //ditto

 //  making a soft start for the motors by setting the slope of the ramp rate to "slow"
  UpVal = (slow*lastuv+UpVal)/(slow+1) ;  //slow it down
  LeftVal = (slow*lastlf+LeftVal)/(slow+1) ;  //slows the reaction time
  RightVal = (slow*lastrf+RightVal)/(slow+1) ; //ditto
  lastuv=UpVal;
  lastlf=LeftVal;
  lastrf=RightVal;

//Current limiter
  Totalizer = abs(UpVal) * 2 + abs(LeftVal) + abs(RightVal) + abs(sideval);
 if (Totalizer > Limiter) {
  UpVal = (UpVal * Limiter / Totalizer) ;
  LeftVal = (LeftVal * Limiter / Totalizer);
  RightVal = (RightVal * Limiter / Totalizer);
  sideval = (sideval * Limiter / Totalizer);
 }
 
// to repair a noise problem, we propose to ignore values between -35 and 35  added 4/4/19, changed to 20 on 5/4/19
  if (abs(LeftVal) < 20/relax) {
    LeftVal = 0;
      }
  if (abs(UpVal) < 20/relax) {
    UpVal = 0;
  }
if (abs(RightVal) < 20/relax) {
    RightVal = 0;
      }
if (abs(sideval) < 20/relax) {
    sideval = 0;
    }
// Map the raw values to the analog output of the ESC drive thrusters.
// Change motor speed by switching the 1100 and the 1900
  UpVal = map(UpVal,-100,100, 1100,1900);
  UpVal2 = map(UpVal,1100,1900, 1900,1100);   // this maps the UpVal2 to the opposite of the UpVal to account for the opposite orientation of the props
  LeftVal = map(LeftVal,-100,100,1900,1100);
  RightVal = map(RightVal,-100,100,1100,1900);
  sideval = map(sideval,-100,100, 1100,1900);

//  lets us see what is happeningon the serial monitor
//  Serial.println(" map to esc, up, left, right");
//  Serial.println(UpVal);
//  Serial.println(UpVal2);
//  Serial.println(LeftVal);
//  Serial.println(RightVal);
//  output to the ESCs

  left.writeMicroseconds(LeftVal);
  right.writeMicroseconds(RightVal);
  side.writeMicroseconds(sideval);

/* taken out on request 5/4/19
if (abs(1500-LeftVal)>100 or abs(1500-RightVal)> 100) {
up.writeMicroseconds(1500);
up2.writeMicroseconds(1500);  
}
else {
*/  up.writeMicroseconds(UpVal);
  up2.writeMicroseconds(UpVal2);  
//}

}
