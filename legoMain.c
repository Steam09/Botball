#include <kipr/wombat.h>

// Ports
const int sideServo = 2;
const int rotateServo = 0;
const int clawServo = 1; 
const int lightSensor = 0;
const int etSensor = 1;
const int leftButton = 0;
const int rightButton = 1;

// Moving Times or Speeds
int turningTime90 = 1250;
int leftVelocity = 1500;
int rightVelocity = 1470;
const int tapeIndicator = 3850;
// 26.5 cm per 1000ms

// Servo Positions
int horizontalArm = 500;
int verticalArm = 1321;
int openClaw = 1731;
int closedClaw = 1026;
int innerSide = 200;
int pushedSide = 1500;

void driveForward(float cm, int leftSpeed, int rightSpeed);
void driveBackward(float cm, int leftSpeed, int rightSpeed);
void turnLeft(int degrees);
void turnRight(int degrees);
void alignTape(int speed);
void servoSpeed(int speed, int endPosition);
void alignWall(void);

int main() {

    // Resetting Servos
    enable_servos();
    cmpc(0);
    cmpc(1);
    set_servo_position(sideServo, innerSide);
    set_servo_position(rotateServo, verticalArm);
    set_servo_position(clawServo, closedClaw);
    disable_servos();
    msleep(1000);

    /*
    // Waiting for Start Light
    	wait_for_light(lightSensor);
    	shut_down_in(118);
    
    // Push 4 initial left side habitats to Area 1
    	enable_servos();
    	set_servo_position(sideServo, pushedSide);
    	msleep(50);
    	set_servo_position(sideServo, innerSide);
    */

    // Line up with tape
    alignTape(750);

    // Sweep top rocks to Area 5 Intersection
    driveForward(75, leftVelocity-100, rightVelocity);  // Arc to hit the top rock
    turnRight(80);
    driveForward(18, leftVelocity, rightVelocity);
    turnRight(30);
    driveForward(10, leftVelocity, rightVelocity);
    driveBackward(20, leftVelocity, rightVelocity);
    turnRight(180);

    // WOK

    servoSpeed(0, 5, verticalArm, 1240);
    set_servo_position(1, 1603);
    msleep(200);
    driveForward(10, leftVelocity, rightVelocity);
    msleep(1000);
    set_servo_position(1, 1024);
    msleep(500);
    driveBackward(10, leftVelocity, rightVelocity); 
    turnLeft(150);

    // Outer Poms

    driveForward(10, leftVelocity - 200, rightVelocity); 
    msleep(500);
    driveBackward(20, leftVelocity, rightVelocity); 
    servoSpeed(0, 4, 1240, horizontalArm);
    set_servo_position(clawServo, openClaw);
    servoSpeed(0, 1, horizontalArm, verticalArm);

    // Inner Poms

    turnRight(40);
    driveForward(30, leftVelocity, rightVelocity - 900); 
    driveBackward(12, leftVelocity, rightVelocity - 900); 
    turnRight(130);
    driveForward(50, leftVelocity, rightVelocity); 
    alignTape(1000);


    

}

// Changes how fast the servo goes, otherwise we're gonna make the robot do a kickflip. 
void servoSpeed(int port, int speed, int intialPosition, int endPosition) {
	increment = abs((endPosition - intialPosition) / speed);
	if (endPosition > intialPosition) {
		for( i = 0; i <= speed; i += 1 ){
			set_servo_position(port, intialPosition + increment * i);
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
		for( i = 0; i < speed; i += 1 ){
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
	return;
}

// Goes up to the nearest tape in front of it at speed "int speed". 
void alignTape(int speed) {
    while (analog(5) < tapeIndicator) {
        printf("%d \n", analog(5));
        driveForward(10, speed, speed);
        msleep(5);
    }
    freeze(0);
    freeze(1);
    msleep(100);
	return();
}

void driveForward(float cm, int leftSpeed, int rightSpeed) {
    mav(1,leftSpeed);
    mav(0,rightSpeed);
    msleep(1000/15 * cm);
    ao();
	return();
}

void driveBackward(float cm, int leftSpeed, int rightSpeed) {
    mav(1,(-1) * leftSpeed);
    mav(0,(-1) * rightSpeed);
    msleep(1000/15 * cm);
    ao();
	return();
}

void turnRight(int degrees) {
    mav(0,-1000);
    mav(1,1000);
    msleep(degrees * (turningTime90) / 90);
    ao();
	return();
}

void turnLeft(int degrees) {
    mav(0,1000);
    mav(1,-1000);
    msleep(degrees * (turningTime90) / 90);
    ao();
	return();
}

void alignWall(void) {
    while (leftButton != 1) && (rightButton != 1) {
		if (leftButton == 1) {
			driveBackward(1, leftVelocity - 800, rightVelocity);
			msleep(10);
		}
		else if (rightButton == 1) {
			driveBackward(1, leftVelocity, rightVelocity - 800);
			msleep(10);
		}
		else {
			driveBackward(1, leftVelocity, rightVelocity);
			msleep(10);
		}
	}
}
