#include <Servo.h>                           // Include servo library
     
Servo servoLeft;                             // Declare left and right servos
Servo servoRight;
const int switchPin1 = 6;
const int switchPin2 = 7;
const int switchPin3 = 8;
int switches = 0;
int buttonState1 = digitalRead(switchPin1);
int buttonState2 = digitalRead(switchPin2);
int buttonState3 = digitalRead(switchPin3);
int note[] = {1047, 1245, 1397, 1480, 1568, 1865, 2093}; 
void setup()                                 
{
  // plays a ditty at startup //
  tone(4, note[7], 250);
  delay(250);
  tone(4, note[6], 250);
  delay(250);
  tone(4, note[5], 125);
  delay(125);
  tone(4, note[6], 125);
  delay(125);
  tone(4, note[3], 62);
  delay(62);
  tone(4, note[4], 250);
  delay(250);
  tone(4, note[1], 125);
  delay(125);
  tone(4, note[2], 125);
  delay(125);
  tone(4, note[4], 250);
  delay(250);
  tone(4, note[3], 125);
  delay(125);
  tone(4, note[4], 125);
  delay(125);
  tone(4, note[3], 125);
  delay(125);
  tone(4, note[2], 125);
  delay(125);
  tone(4, note[1], 750);
  delay(750);
  // end of ditty //
  pinMode(10, INPUT);  pinMode(9, OUTPUT);   // Left IR LED & Receiver
  pinMode(3, INPUT);  pinMode(2, OUTPUT);    // Right IR LED & Receiver

  servoLeft.attach(13);                      // Attach left signal to pin 13
  servoRight.attach(12);                     // Attach right signal to pin 12

  if (buttonState1 == HIGH) {
  switches = switches + 1;
  }
  if (buttonState2 == HIGH) {
  switches = switches + 2;
  }
  if (buttonState3 == HIGH) {
  switches = switches + 4;
  }


  switch (switches){
    case 0:
      // return to start of void setup, (but after the ditty plays) //
      break;
    case 1:
      // play song //
      break;
    case 2:
      // run simple rover command (drive forward and then back) //
      break;
    case 3:
      // jump to void loop() //
      break;
  }
}
void loop() {
 
int irLeft = irDetect(9, 10, 38000);       // Check for object on left
  int irRight = irDetect(2, 3, 38000);       // Check for object on right

  if((irLeft == 0) && (irRight == 0))        // If both sides detect
  {
    maneuver(-200, -200, 20);                // Backward 20 milliseconds
  }
  else if(irLeft == 0)                       // If only left side detects
  {
    maneuver(50, -50, 50);                 // Right for 20 ms
  }
  else if(irRight == 0)                      // If only right side detects
  {
    maneuver(-50, 50, 50);                 // Left for 20 ms
  }
  else                                       // Otherwise, no IR detects
  {
    maneuver(200, 200, 20);                  // Forward 20 ms
  }
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);              // IRLED 38 kHz for at least 1 ms
  delay(1);                                  // Wait 1 ms
  int ir = digitalRead(irReceiverPin);       // IR receiver -> ir variable
  delay(1);                                  // Down time before recheck
  return ir;                                 // Return 1 no detect, 0 detect
}  

void maneuver(int speedLeft, int speedRight, int msTime)
{
  // speedLeft, speedRight ranges: Backward  Linear  Stop  Linear   Forward
  //                               -200      -100......0......100       200
  servoLeft.writeMicroseconds(1500 + speedLeft);   // Set left servo speed
  servoRight.writeMicroseconds(1500 - speedRight); // Set right servo speed
  if(msTime==-1)                                   // if msTime = -1
  {                                  
    servoLeft.detach();                            // Stop servo signals
    servoRight.detach();   
  }
  delay(msTime);                                   // Delay for msTime
}
