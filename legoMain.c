#include <kipr/wombat.h>

// Ports
int sideServo = 0;
int rotateServo = 1;
int clawServo = 2; 
int lightSensor = 0;
int etSensor = 1;

// Moving Times or Speeds
int turningTime90 = 1250;
int leftVelocity = 1500;
int rightVelocity = 1470;
const int tapeIndicator = 3850;
// 26.5 cm per 1000ms

// Servo Positions
int horizontalArm = 400;
int verticalArm = 1500;
int backArm = 1600; 
int openClaw = 20;
int closedClaw = 400;
int innerSide = 200;
int pushedSide = 1500;


void driveForward(float cm, int leftSpeed, int rightSpeed);
void turnLeft(int degrees);
void turnRight(int degrees);
void alignTape(int speed);

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
    turnLeft(90);
    alignTape(500);
	driveForward(10, leftVelocity, rightVelocity);
    turnLeft(90);

    // not finished
    cmpc(0);
    set_servo_position(rotateServo, 1400);
    while (analog(etSensor) < 2800) { 
        driveForward(2, 100, 100);
    }
    set_servo_position(rotateServo, 1600);
    msleep(400);
    set_servo_position(rotateServo, 1400);

    // Top Cubes
    driveForward(10, -500, -500)
    set_servo_position(rotateServo, verticalArm);

    

}





void alignTape(int speed) {
    while (analog(5) < tapeIndicator) {
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

