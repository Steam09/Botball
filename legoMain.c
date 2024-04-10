#include <kipr/wombat.h>

// Servos
const int rotateServo = 0;
const int clawServo = 1;
// Analog
const int backLightSensor = 0;
const int leftLightSensor = 4;
const int rightLightSensor = 5;
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

int positions = [1000,1000,1000,1000,1000,1000];

void driveForward(float cm, int leftSpeed, int rightSpeed);
void driveBackward(float cm, int leftSpeed, int rightSpeed);
void turnLeft(int degrees);
void turnRight(int degrees);
void alignTape(int speed);
void servoSpeed(int port, int speed, int initialPosition, int endPosition);
void alignWall(void);
void habitats(int poleNum, int num);


int main() {

    // Resetting Servos
    enable_servos();
    cmpc(0);
    cmpc(1);
    servoSpeed(rotateServo, 40, get_servo_position(rotateServo), 1400);
    servoSpeed(clawServo, 20, get_servo_position(clawServo), 1600);
    servoSpeed(clawServo, 20, 1600, 200);
    printf("calibrating\n");
    msleep(100);


    /*
    wait_for_light(lightSensor);
    shut_down_in(119);
    */

  
    // Line up with tape
    alignTape(400);

    // Sweep top rocks to Area 5 Intersection
    printf("Rocks\n");
    driveForward(80, leftVelocity-100, rightVelocity);  // Arc to hit the top rock
    turnRight(80);
    driveForward(25, leftVelocity, rightVelocity); //originally 22

    driveBackward(10, leftVelocity, rightVelocity);
    turnRight(60);
    driveBackward(8, leftVelocity, rightVelocity);
    msleep(300);
    
    turnRight(43);
    printf("Align Tape\n");
    while (analog(rightLightSensor) < tapeIndicator) {
        printf("%d \n", analog(5));
        driveForward(5, 300, -300);
        msleep(5);
    }
    ao();
    msleep(300);

    turnRight(40);
  
    msleep(200);
    servoSpeed(clawServo, 20, 200, 1500);
    servoSpeed(rotateServo, 30, 1450, 1060);
    msleep(200);
    driveForward(8, leftVelocity, rightVelocity);
    msleep(100);
    servoSpeed(clawServo, 20, 1500, 200);
    printf("Grabbed Center\n");
    msleep(100);
    driveBackward(13, leftVelocity, rightVelocity);

    turnLeft(60);
    driveBackward(15, leftVelocity, rightVelocity);
    servoSpeed(rotateServo, 40, get_servo_position(rotateServo), 300);
    msleep(500);
    servoSpeed(clawServo, 6, 200, 1500);
    msleep(200);
    servoSpeed(rotateServo, 40, 300, 1400);
    
    msleep(300);
    turnLeft(12);
    printf("splitting multis\n");
    driveForward(38, 1400, 1500);
    driveForward(24, 0, 1500);
    driveForward(20, leftVelocity, rightVelocity);
    
    driveBackward(15, leftVelocity, rightVelocity);
    turnRight(90);
    printf("left poms\n");
    driveForward(5, leftVelocity, rightVelocity);
    driveForward(40, leftVelocity, 200);
    driveForward(10, leftVelocity, rightVelocity);
    driveForward(22, 600, rightVelocity);
    driveForward(20, leftVelocity, rightVelocity);

    driveBackward(20, 1500, 1500);
    turnRight(46);
    printf("to diagonal\n");
    // go up to fuel area
    servoSpeed(rotateServo, 30, 1400, 1300);
    msleep(200);
    driveForward(80, leftVelocity, rightVelocity);
    servoSpeed(clawServo, 6, get_servo_position(clawServo), 1243);
    turnLeft(115);
    
    servoSpeed(rotateServo, 20, get_servo_position(rotateServo), 1190);
    driveForward(39, leftVelocity, rightVelocity); 
    servoSpeed(clawServo, 6, get_servo_position(clawServo), 100);
    driveBackward(15, leftVelocity, rightVelocity);
    turnRight(155);
    driveForward(20, 1500, 1500);
    turnLeft(25);

    // Drop multiplier rocks
    servoSpeed(rotateServo, 40, 1190, 300);
    msleep(400);
    servoSpeed(clawServo, 20, get_servo_position(clawServo), 1243);
    msleep(100);
    servoSpeed(rotateServo, 40, 300, 1300);
    msleep(400);
    driveBackward(10, leftVelocity, rightVelocity);

    turnRight(150);
    driveForward(50, leftVelocity, rightVelocity);
    turnRight(30);
    driveForward(50, leftVelocity, rightVelocity);

    /*
    servoSpeed(clawServo, 10, get_servo_position(clawServo), 1200);
    for (int i = 0; i < 6; i += 1) {
        habitats(i, 6 - i);
    }
    */
    printf("I snooze\n");

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

void habitats(int poleNum, int num) {

    int heights[] = {400, 700, 1000, 700, 400};

    servoSpeed(rotateServo, 40, get_servo_position(rotateServo), positions[num]);
    driveForward(5,500,500);
    servoSpeed(clawServo, 10, get_servo_position(clawServo), 100);

    for (int i = 0; i < num * 4; i += 1) {
        servoSpeed(rotateServo, 25, get_servo_position(rotateServo), position[num] + 50);
        driveForward(2, leftVelocity, rightVelocity);
    }
    servoSpeed(rotateServo, 5, get_servo_position, verticalArm);

    turnRight(180);
    alignWall();

    driveForward(poleNum * 5 + 2, leftVelocity, rightVelocity);

    turnLeft(90);

    servoSpeed(rotateServo, poleNum * 10, verticalArm, heights[poleNum]);
    servoSpeed(clawServo, 10, 100, 1200);
    servoSpeed(rotateServo, poleNum * 10, heights[poleNum], verticalArm);

    turnLeft(90);
    driveForward(polenum * 5 + 2, leftVelocity, rightVelocity);

}
