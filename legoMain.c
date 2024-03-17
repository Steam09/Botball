#include <kipr/wombat.h>

// Ports
const int sideServo = 2;
const int rotateServo = 0;
const int clawServo = 1; 
const int lightSensor = 0;
const int etSensor = 1;

// Moving Times or Speeds
int turningTime90 = 1250;
int leftVelocity = 1500;
int rightVelocity = 1470;
const int tapeIndicator = 3850;
// 26.5 cm per 1000ms

// Servo Positions
int horizontalArm = 1473;
int verticalArm = 1321;
int openClaw = 1731;
int closedClaw = 1026;
int innerSide = 200;
int pushedSide = 1500;

void driveForward(float cm, int leftSpeed, int rightSpeed);
void turnLeft(int degrees);
void turnRight(int degrees);
void alignTape(int speed);
void servoSpeed(int speed, int endPosition)

int main() {

    // Resetting Servos
    	enable_servos();
    	cmpc(0);
    	cmpc(1);
    	set_servo_position(sideServo, innerSide);
    	set_servo_position(rotateServo, verticalArm);
    	set_servo_position(clawServo, closedClaw);
    	disable_servos();

    // Waiting for Start Light
    	wait_for_light(lightSensor);
    	shut_down_in(118);
    
    // Push 4 initial left side habitats to Area 1
    	enable_servos();
    	set_servo_position(sideServo, pushedSide);
    	msleep(50);
    	set_servo_position(sideServo, innerSide);

    // Line up with tape
    	alignTape(250);

    // Sweep top rocks to Area 5 Intersection
    	driveForward(75, leftVelocity-100, rightVelocity);
    	turnRight(80);
    	driveForward(18, leftVelocity, rightVelocity);
    	turnRight(30);
    	driveForward(10, leftVelocity, rightVelocity);
    	driveForward(20, -1 * leftVelocity, -1 * rightVelocity);

    // Red Poms
    	turnRight(60);
    	driveForward(20, leftVelocity, rightVelocity);
    	turnLeft(40);
	driveForward(27, leftVelocity, rightVelocity);
    	driveForward(20, -1 * leftVelocity, -1 * rightVelocity);
    	alignTape(-250);
    
    // Light Switch
    /*
    	turnLeft(90);
	alignTape(500);
	driveForward(10, leftVelocity, rightVelocity);
    	turnLeft(90);
    */

    // Top Cubes
    	turnLeft(90);
    	alignTape(500);
	driveForward(12, leftVelocity, rightVelocity);
    	turnLeft(95);
    	msleep(500);
    	set_servo_position(0, 1250);
    	msleep(500);
    	set_servo_position(0, 1210);
    	msleep(500);
    	set_servo_position(1, 1603);
    	msleep(1000);
    	driveForward(25, leftVelocity, rightVelocity);
    	msleep(1000);
    	set_servo_position(1, 1024);
    	msleep(500);
    	driveForward(10, -1 * leftVelocity, -1 * rightVelocity); // has grabb yey
    

    

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

