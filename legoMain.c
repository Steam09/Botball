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
int horizontalArm = 100;
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
void servoSpeed(int port, int speed, int initialPosition, int endPosition);
void alignWall(void);

int main() {

    // Resetting Servos
    enable_servos();
    cmpc(0);
    cmpc(1);
    set_servo_position(sideServo, innerSide);
    set_servo_position(0, 1450);
    set_servo_position(clawServo, 400);
    msleep(100);

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
    alignTape(600);

    // Sweep top rocks to Area 5 Intersection
    driveForward(75, leftVelocity-100, rightVelocity);  // Arc to hit the top rock
    turnRight(80);
    driveForward(22, leftVelocity, rightVelocity);
    turnRight(30);
    driveForward(8, leftVelocity, rightVelocity);
    driveBackward(20, leftVelocity, rightVelocity);
    msleep(500);
    turnRight(180);
    alignWall();
    
    driveForward(25, leftVelocity, rightVelocity);
    
    set_servo_position(0, 1450);
    set_servo_position(clawServo, 1200);
    
    driveForward(10, leftVelocity, rightVelocity);
    
    set_servo_position(clawServo, 100);
    
    driveBackward(10, leftVelocity, rightVelocity);

	
    /*
    driveForward(25, leftVelocity, rightVelocity);
    turnRight(180);
    driveForward(25, leftVelocity, rightVelocity);
    turnLeft(115);
    msleep(200); 

    // multis

    servoSpeed(0, 5, verticalArm, 1240);
    set_servo_position(1, 1603);
    msleep(200);
    driveForward(15, leftVelocity, rightVelocity);
    msleep(1000);
    set_servo_position(1, 300);
    msleep(500);
    driveBackward(20, leftVelocity, rightVelocity); 
    turnLeft(100);
    msleep(500);

    // Outer Poms

    driveForward(30, leftVelocity - 500, rightVelocity); 
    msleep(500);
    driveBackward(20, leftVelocity, rightVelocity); 
    msleep(500);
    servoSpeed(0, 8, 1240, horizontalArm);
    msleep(1000);
    set_servo_position(clawServo, openClaw);
    msleep(500);
    servoSpeed(0, 1, horizontalArm, verticalArm);

    // Inner Poms

    turnRight(40);
    driveForward(30, leftVelocity, rightVelocity - 900); 
    driveBackward(12, leftVelocity, rightVelocity - 900); 
    turnRight(130);
    driveForward(50, leftVelocity, rightVelocity); 
    alignTape(1000);


    */

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
    while ((analog(leftLightSensor) < tapeDetection) && (analog(rightLightSensor) < tapeDetection)) {
        printf("%d \n", analog(5));
        driveForward(10, speed, speed);
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
    while ((digital(leftButton) != 1) || (digital(rightButton) != 1)) {
        if (digital(rightButton) == 1) {
            driveForward(2, 200, 200);
            driveBackward(5, 200, -200);
            msleep(50);

        }
        else if (digital(leftButton) == 1) {
            driveForward(2, 200, 200);
            driveBackward(5, -200, 200);
            msleep(50);
        }
        else {
            driveBackward(1, leftVelocity, rightVelocity);
            msleep(200);
        }
    }
}


void lineTrack(int distance, int direction) { // in centimeteres, direction == 0 <-- left, 1 <-- right
    int tickDistance = 28.5 * distance * 1800;
    cmpc(0);
    cmpc(1);
    if (direction == 0) {
        while (analog(leftLightSensor) < tapeDetection) { // Turn left and drive up to tape
        	driveForward(2, leftVelocity - 400, rightVelocity);
        	msleep(20);
    	} 
        driveForward(3, leftVelocity, 0);
        ao();
        msleep(50);
  	}
    else {
        while (analog(rightLightSensor) < tapeDetection) { // Turn right and drive up to tape
        	driveForward(2, leftVelocity, rightVelocity - 400);
        	msleep(20);
    	}
        driveForward(3, 0, rightVelocity);
        ao();
        msleep(50);
    }
    
	while ((gmpc(1) + gmpc(0)) / 2 < tickDistance) { // start wiggling
        if ((analog(leftLightSensor) < tapeDetection) && (analog(rightLightSensor) < tapeDetection)) {
            driveForward(2, leftVelocity, rightVelocity);
            continue;
        }
        if ((analog(leftLightSensor) < tapeDetection) && (analog(rightLightSensor) > tapeDetection)) {
            driveForward(2, leftVelocity, rightVelocity - 600);
            continue;
        }
        if ((analog(leftLightSensor) > tapeDetection) && (analog(rightLightSensor) < tapeDetection)) {
            driveForward(2, leftVelocity - 600, rightVelocity);
            continue;
        }
    }
    freeze(0);
    freeze(1);



}
