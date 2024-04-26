#include <kipr/wombat.h>

// Servo Ports
const int rotateServo = 0;
const int clawServo = 1;
const int smallServo = 2;
// Analog Ports
const int backLightSensor = 0;
const int leftLightSensor = 4;
const int rightLightSensor = 5;
// Digital Ports
const int backLeftButton = 0;
const int backRightButton = 1;

// Variable numbers to change
const int turningTime90 = 1250;
const int leftVelocity = 1500;
const int slowleftVelocity = 1000;
const int slowrightVelocity = 9070;
const int rightVelocity = 1470;
const int tapeIndicator = 3920;

// General Servo Positions
int horizontalArm = 350;
int verticalArm = 1500;
int openClaw =  1800;
int closedClaw = 910;
int closedClawHalf = 1200;
int closedSide = 1500;

// Habitat Heighs
const int positions[] = {660,775,10000000,923,1082};
const int heightsOfPoles[] = {667, 935, 100, 935, 667};
const int anglesOfPoles[] = {15,30,45,60,75};
// Used for Math

// Functions used throughout code, see below
void driveForward(double cm, int leftSpeed, int rightSpeed);
void driveBackward(double cm, int leftSpeed, int rightSpeed);
void turnLeft(double degrees);
void turnRight(double degrees);
void alignTape(int speed);
void servoSpeed(int port, int speed, int endPosition);
void alignWall(void);

// 800 is closed, 2000 is out


int main() {

    // Resetting Servos before run
    printf("calibrating\n");
    enable_servos();
    disable_servo(smallServo);
    servoSpeed(rotateServo, 40, 1500);
    disable_servo(smallServo);
    servoSpeed(clawServo, 5, openClaw);
    disable_servo(smallServo);
    msleep(500);
    set_servo_position(clawServo, closedClaw);
    disable_servo(smallServo);
    msleep(200);
    enable_servo(smallServo);
    servoSpeed(smallServo, 10, closedSide);
    disable_servo(smallServo);
    msleep(100);

    // wait_for_light(backLightSensor);

    shut_down_in(118);
    msleep(200);
    // Line up with tape
    alignTape(600);


    // Sweep top rocks to Area 5 Intersection
    printf("Rocks\n");
    driveForward(80, leftVelocity-100, rightVelocity);  // Arc to hit the top rock
    turnRight(80);
    driveForward(25, leftVelocity, rightVelocity); // Rocks to intersection
    disable_servo(smallServo);
    driveBackward(10, leftVelocity, rightVelocity);
    turnRight(60);
    driveBackward(11, leftVelocity, rightVelocity);
    disable_servo(smallServo);
    turnRight(67);
    printf("Align Tape\n"); // Continue turning till tape on rightLightSensor
    while (analog(rightLightSensor) < tapeIndicator) {
        driveForward(0.2, 200, -200);
    }
    ao();
    msleep(100);
    disable_servo(smallServo);
    turnRight(36); // Align to middle multis
    servoSpeed(clawServo, 5, openClaw);
    servoSpeed(rotateServo, 30, 1115);
    driveForward(25, leftVelocity, rightVelocity);
    msleep(500);
    set_servo_position(clawServo, 920);
    printf("Grabbed Center\n"); // Make close on multipliers
    msleep(100);
    driveBackward(5, leftVelocity, rightVelocity);
    turnRight(13);
    driveBackward(5, leftVelocity, rightVelocity);
    turnLeft(2);
    driveBackward(40, leftVelocity, rightVelocity);
    alignWall();
    driveForward(14, leftVelocity, rightVelocity);
    turnRight(90);


    // Drive next to Pom Line
    enable_servo(smallServo);
    set_servo_position(smallServo, 1765);
    disable_servo(smallServo);
    mav(1, (-1) * (leftVelocity - 50));
    mav(0, (-1) * (rightVelocity));
    disable_servo(smallServo);

    // Flick Closest Poms Out
    msleep(1700);
    ao();
    msleep(1000);
    enable_servo(smallServo);
    set_servo_position(smallServo, 0);
    msleep(300);
    disable_servo(smallServo);
    msleep(300);
    mav(1, (-1) * (leftVelocity - 50));
    mav(0, (-1) * (rightVelocity));
    msleep(1400);
    ao();
    // Grab Pom onto Robot
    enable_servo(smallServo);
    set_servo_position(smallServo, 1700);
    msleep(300);
    disable_servo(smallServo);
    mav(1, (leftVelocity - 50));    
    mav(0, (rightVelocity));
    msleep(1750);
    ao();
    enable_servo(smallServo);
    set_servo_position(smallServo, 0);
    msleep(500);
    disable_servo(smallServo);

    mav(1, (leftVelocity - 50));
    mav(0, (rightVelocity));
    msleep(500);
    ao();
    turnLeft(81);

    alignWall();
    driveForward(3, leftVelocity, rightVelocity);
    turnLeft(82);
    driveBackward(4, leftVelocity, rightVelocity);
    // droop multiplier
    servoSpeed(rotateServo, 40, 400);
    servoSpeed(clawServo, 10, openClaw);
    servoSpeed(rotateServo, 40, 1500);
    servoSpeed(clawServo, 10, closedClaw);
    ao();
    msleep(500);

    turnRight(15);
    driveForward(34, leftVelocity, rightVelocity);
    turnRight(68);
    driveBackward(7, leftVelocity, rightVelocity);
    alignWall();
    driveForward(80, leftVelocity, rightVelocity);
    driveBackward(30, leftVelocity, rightVelocity);
    turnLeft(73);
    driveBackward(3, leftVelocity, rightVelocity);

    // grab habitat
    servoSpeed(clawServo, 10, openClaw);
    servoSpeed(rotateServo, 40, 350);
    servoSpeed(clawServo, 10, closedClaw);
    servoSpeed(rotateServo, 40, 1600);
    turnRight(26);
    //drop multiplier 
    driveForward(40, leftVelocity, rightVelocity);
    servoSpeed(rotateServo, 40, 800);
    servoSpeed(clawServo, 10, openClaw);

    disable_servos();
    ao();
    printf("I snooze\n");




}


// Custom Function for a Controlled Servo
void servoSpeed(int port, int speed, int endPosition) {
    enable_servo(smallServo);
    enable_servo(port);
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
}


// Drives forward uptil tape, then stops; Must trigger both sensors
void alignTape(int speed) {
    while (analog(rightLightSensor) < tapeIndicator) {
        printf("%d \n", analog(rightLightSensor));
        driveForward(2.5, speed, speed);
        msleep(5);
    }
    freeze(0);
    freeze(1);
    msleep(100);
}


// Drives forward a set distance cm with custom wheel speeds
void driveForward(double cm, int leftSpeed, int rightSpeed) {
    mav(1,leftSpeed);
    mav(0,rightSpeed);
    msleep(1000/15 * cm);
    ao();
}


// See driveForward, easier for debugging and testing purposes
void driveBackward(double cm, int leftSpeed, int rightSpeed) {
    mav(1,(-1) * leftSpeed);
    mav(0,(-1) * rightSpeed);
    msleep(1000/15 * cm);
    ao();
}


// Self-Explanatory
void turnRight(double degrees) {
    mav(0,-1000);
    mav(1,1000);
    msleep(degrees * (turningTime90) / 90);
    ao();
}


// Self-Explanatory
void turnLeft(double degrees) {
    mav(0,1000);
    mav(1,-1000);
    msleep(degrees * (turningTime90) / 90);
    ao();
}




// Drives backwards into a wall until normal
void alignWall(void) {
    while ((digital(backLeftButton) != 1) || (digital(backRightButton) != 1)) {
        if (digital(backLeftButton) == 1) {
            mav(1, -300);
            mav(0, -800);
            msleep(5);
        }
        else if (digital(backRightButton) == 1) {
            mav(1, -800);
            mav(0, -300);
            msleep(5);
        }
        else {
            mav(1, -1000);
            mav(0, -1000);
            msleep(5);  
        }
    }
    printf("Aligned to Wall");
}
