#include <kipr/wombat.h>


// Servos
const int rotateServo = 0;
const int clawServo = 1;
// Analog
const int backLightSensor = 0;
const int leftLightSensor = 5;
const int rightLightSensor = 4;
// Digital
const int backLeftButton = 0;
const int backRightButton = 1;


// Moving Times or Speeds
int turningTime90 = 1250;
int leftVelocity = 1500;
int rightVelocity = 1470;
const int tapeIndicator = 3950;
// 26.5 cm per 1000ms


// Servo Positions
int horizontalArm = 100;
int verticalArm = 1321;
int openClaw = 1731;
int closedClaw = 1026;


void driveForward(float cm, int leftSpeed, int rightSpeed);
void driveBackward(float cm, int leftSpeed, int rightSpeed);
void turnLeft(int degrees);
void turnRight(int degrees);
void alignTape(int speed);
void servoSpeed(int port, int speed, int initialPosition, int endPosition);
void alignWall(void);


int main() {


   // Resetting Servos
   enable_servos();
   cmpc(0);
   cmpc(1);
   set_servo_position(0, 1450);
   set_servo_position(clawServo, 2000);
   msleep(100);


   /*
   Waiting for Start Light
       wait_for_light(lightSensor);
       shut_down_in(118);
   */

	ao();
   // Line up with tape
   alignTape(400);


   // Sweep top rocks to Area 5 Intersection
   driveForward(80, leftVelocity-100, rightVelocity);  // Arc to hit the top rock
   turnRight(80);
   driveForward(25, leftVelocity, rightVelocity); //originally 22
  
   driveBackward(10, leftVelocity, rightVelocity);
   turnRight(60);
   driveBackward(12, leftVelocity, rightVelocity);
   msleep(500);
    
   turnRight(50);
   while (analog(rightLightSensor) < tapeIndicator) {
       printf("%d \n", analog(5));
       driveForward(5, 1000, -1000);
       msleep(5);
   }
   freeze(0);
   freeze(1);
   msleep(100);
    
   
    
    
   turnRight(10);
  
    
   msleep(2000);
   servoSpeed(rotateServo, 9, 1450, 1200);
   msleep(200);
   driveForward(14, leftVelocity, rightVelocity);
   msleep(800);
   set_servo_position(clawServo, 0);
   msleep(500);
   driveBackward(13, leftVelocity, rightVelocity);


   // New code as of April 7th, up to changes


   turnLeft(60);
   servoSpeed(rotateServo, 40, 1200, 400);
   msleep(900);
   servoSpeed(clawServo, 6, 0, 1200);
   msleep(500);
   servoSpeed(rotateServo, 40, 400, 1400);
    
   msleep(1000);
   turnLeft(14);
    
  	driveForward(35, 1400, 1500);
   driveForward(20, 00, 1500);
   driveForward(20, 1500, 1500);
   ao();
   msleep(2000);
    
    
    
    
   driveBackward(10, leftVelocity, rightVelocity);
   turnLeft(240);


   driveForward(15, leftVelocity, rightVelocity);
   turnLeft(100);
   driveForward(10, leftVelocity, rightVelocity);
   set_servo_position(clawServo, 15);
   driveBackward(10, leftVelocity, rightVelocity);


  


}


// Changes how fast the servo goes, otherwise we're gonna make the robot do a kickflip.
void servoSpeed(int port, int speed, int initialPosition, int endPosition) {
   int increment = abs((endPosition - initialPosition) / speed);
   if (endPosition > initialPosition) {
       for( int i = 0; i <= speed; i += 1 ){
           set_servo_position(port, initialPosition + increment * i);
           msleep(50);
           if (initialPosition + increment * i > endPosition) {
               set_servo_position(port, endPosition);
               msleep(50);
               disable_servos();
               break;
           }
       }
   }
   else {
       for( int i = 0; i < speed; i += 1 ){
           set_servo_position(port, initialPosition - increment * i);
           msleep(50);
           if (initialPosition - increment * i < endPosition) {
               set_servo_position(port, endPosition);
               msleep(50);
               disable_servos();
               break;
           }
       }
   }
   enable_servos();
}


// Goes up to the nearest tape in front of it at speed "int speed".
void alignTape(int speed) {
   while (analog(5) < tapeIndicator) {
       printf("%d \n", analog(5));
       driveForward(5, speed, speed);
       msleep(5);
   }
   freeze(0);
   freeze(1);
   msleep(100);
}


void driveForward(float cm, int leftSpeed, int rightSpeed) {
   mav(1,leftSpeed);
   mav(0,rightSpeed);
   msleep(1000/15 * cm);
   ao();
}


void driveBackward(float cm, int leftSpeed, int rightSpeed) {
   mav(1,(-1) * leftSpeed);
   mav(0,(-1) * rightSpeed);
   msleep(1000/15 * cm);
   ao();
}


void turnRight(int degrees) {
   mav(0,-1000);
   mav(1,1000);
   msleep(degrees * (turningTime90) / 90);
   ao();
}


void turnLeft(int degrees) {
   mav(0,1000);
   mav(1,-1000);
   msleep(degrees * (turningTime90) / 90);
   ao();
}


void alignWall(void) {
   while ((digital(backLeftButton) != 1) || (digital(backRightButton) != 1)) {
       if (digital(backRightButton) == 1) {
           driveForward(2, 200, 200);
           driveBackward(4, 200, -200);
           msleep(50);
          
       }
       else if (digital(backLeftButton) == 1) {
           driveForward(2, 200, 200);
           driveBackward(2, -200, 200);
           msleep(50);
       }
       else {
           driveBackward(1, leftVelocity, rightVelocity);
           msleep(200);
       }
   }
}
