#include <kipr/wombat.h>

// Servos
const int rotateServo = 0;
const int clawServo = 1;
// Analog Ports
const int backLightSensor = 0;
const int leftLightSensor = 4;
const int rightLightSensor = 5;
// Digital Ports
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
int verticalArm = 1500;
int openClaw = 1300;
int closedClaw = 200;

int positions[] = {521,693,809,1020,1207};
const int armLength = 1000;

void driveForward(float cm, int leftSpeed, int rightSpeed);
void driveBackward(float cm, int leftSpeed, int rightSpeed);
void turnLeft(int degrees);
void turnRight(int degrees);
void alignTape(int speed);
void servoSpeed(int port, int speed, int endPosition);
void alignWall(void);
void habitats(int poleNum, int num, int side);
void grabHabitat(int newNum);

//Order of Events
//Push Rocks
//Grab Multipliers
//Get OUTTA MY WAY!!!
//Sort Poms
//Habitats 
int main() {

    // Resetting Servos
    enable_servos();
    cmpc(0);
    cmpc(1);
    servoSpeed(rotateServo, 40, 1400);
    servoSpeed(clawServo, 20, 1600);
    servoSpeed(clawServo, 20, 200);
    printf("calibrating\n");
    msleep(100);
	/*
    wait_for_light(backLightSensor);
    shut_down_in(119);
  	*/
    // Line up with tape
    alignTape(600);

    // Sweep top rocks to Area 5 Intersection
    printf("Rocks\n");
    driveForward(80, leftVelocity-100, rightVelocity);  // Arc to hit the top rock
    turnRight(80);
    driveForward(25, leftVelocity, rightVelocity); // Rocks to intersection

    driveBackward(10, leftVelocity, rightVelocity);
    turnRight(60); 
    driveBackward(8, leftVelocity, rightVelocity);
    
    turnRight(43);
    printf("Align Tape\n");
    while (analog(rightLightSensor) < tapeIndicator) {
        printf("%d \n", analog(5));
        driveForward(5, 400, -400);
        msleep(5);
    }
    ao();
    msleep(50);

    turnRight(40); // Align to middle multis
    servoSpeed(clawServo, 5, 1500);
    servoSpeed(rotateServo, 30, 1060);
    msleep(200);
    driveForward(9, leftVelocity, rightVelocity);
    servoSpeed(clawServo, 20, 200);
    printf("Grabbed Center\n");
    msleep(50);
    driveBackward(5, leftVelocity, rightVelocity);

    turnLeft(90);
    driveForward(15, leftVelocity, rightVelocity);
    turnLeft(90);
    servoSpeed(rotateServo, 40, 300);
    msleep(300);
    servoSpeed(clawServo, 6 1500); // Place multipliers on the ground
    msleep(50);
    servoSpeed(rotateServo, 40, 1400);
    msleep(300);
    turnLeft(8);

    printf("splitting multis\n");
    driveForward(20, leftVelocity, rightVelocity);
    turnRight(8);
    driveForward(12, leftVelocity, rightVelocity);
    driveBackward(10, leftVelocity, rightVelocity);
    turnRight(120);

    printf("left poms\n");
    driveForward(10, leftVelocity, rightVelocity);
    driveForward(15, leftVelocity, 200);
    driveForward(10, 200, rightVelocity)
    driveForward(30, leftVelocity, rightVelocity);

    driveBackward(20, 1500, 1500);
    turnLeft(90);
    driveForward(10, 1500, 1500);
    
    /*
    turnRight(150);
    driveForward(50, leftVelocity, rightVelocity);
    turnRight(30);
    driveForward(50, leftVelocity, rightVelocity);
	doubleTape();
    servoSpeed(clawServo, 10, 1200);
    for (int i = 0; i < 6; i += 1) {
        habitats(i, 6 - i);
    }
    */
   
    disable_servos();
    ao();
    printf("I snooze\n");

}


// Custom Function for a Controlled Servo
void servoSpeed(int port, int speed, int endPosition) {
   int initialPosition = get_servo_position(port);
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

// Drives forward uptil tape, then stops; Must trigger both sensors
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

// Drives forward a set distance cm with custom wheel speeds
void driveForward(float cm, int leftSpeed, int rightSpeed) {
   mav(1,leftSpeed);
   mav(0,rightSpeed);
   msleep(1000/15 * cm);
   ao();
}

// See driveForward, easier for debugging and testing purposes
void driveBackward(float cm, int leftSpeed, int rightSpeed) {
   mav(1,(-1) * leftSpeed);
   mav(0,(-1) * rightSpeed);
   msleep(1000/15 * cm);
   ao();
}

// Self-Explanatory
void turnRight(int degrees) {
   mav(0,-1000);
   mav(1,1000);
   msleep(degrees * (turningTime90) / 90);
   ao();
}

// Self-Explanatory
void turnLeft(int degrees) {
   mav(0,1000);
   mav(1,-1000);
   msleep(degrees * (turningTime90) / 90);
   ao();
}

// Drives backwards into a wall until normal
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

// Drives up to and places habitats on designated poles
void habitats(int poleNum, int num, int side) { 

    servoSpeed(rotateServo, 40, positions[num]);
    driveForward(5,500,500);
    servoSpeed(clawServo, 10, 100);

    grabHabitat(0);
    servoSpeed(rotateServo, 5, verticalArm);

    turnRight(180);
    alignWall();

    if (side == 0) {
        driveForward(poleNum * 5 + 2 , leftVelocity, rightVelocity);
    }
    else {
        driveForward(poleNum * 5 + 2 , leftVelocity, rightVelocity);
    }

    turnLeft(90);

    servoSpeed(rotateServo, poleNum * 10, heights[poleNum]);
    servoSpeed(clawServo, 10 1200);
    servoSpeed(rotateServo, poleNum * 10, verticalArm);

    turnLeft(90);
    driveForward(poleNum * 5 + 2, leftVelocity, rightVelocity);

}

// Grabbing the habitats off their poles / grpund
void grabHabitat(int newNum) {

    if (newNum < 4) {
        servoSpeed(rotateServo, 20, horizontalArm);
        driveForward(4 * newNum + 5, leftVelocity, rightVelocity);
        servoSpeed(clawServo, 10, closedClaw);
        msleep(50);
        servoSpeed(rotateServo, 30, verticalArm);
        printf("Grabbed ground multiplier\n")
    }

    else {

    }
    
}
