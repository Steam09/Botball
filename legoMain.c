#include <kipr/wombat.h>

// Ports
int sideServo = 0;
int rotateServo = 1;
int clawServo = 2; 
int lightSensor = 0;
int etSensor = 1;

// Moving Times or Speeds
int turningTime90 = 810;
int leftVelocity = 1500;
int rightVelocity = 1500;
// 26.5 cm per 1000ms

// Servo Positions
int horizontalArm = 1473;
int verticalArm = 800;
int openClaw = 20;
int closedClaw = 400;
int innerSide = 200;
int pushedSide = 1500;

void driveForward(float inches, int leftSpeed, int rightSpeed);
void turnLeft(int degrees);
void turnRight(int degrees);

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
    while (analog(0) < 2800) {
        driveForward(2, leftVelocity, int rightVelocity);
    }

    // Sweep top rocks to Area 5 Intersection
    driveForward(65, leftVelocity, rightVelocity);
    while (analog(lightSensor) < 2800) { 
        driveForward(2, 100, 100)
    }
    turnRight(90);
    driveForward(50, leftVelocity, rightVelocity);
    driveForward(20, -1 * leftVelocity, -1 * rightVelocity);
    turnLeft(180);
    
    // Light Switch
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

























void driveForward(float cm, int leftSpeed, int rightSpeed) {
    mav(1,leftVelocity);
    mav(0,rightVelocity);
    msleep(cm*1000/26.5);
    freeze(0);
    freeze(1);
}

void turnRight(int degrees) {
    mav(0,-250);
    mav(1,250);
    msleep(degrees * (turningTime90) / 90);
    ao();
}

void turnLeft(int degrees) {
    mav(0,250);
    mav(1,-250);
    msleep(degrees * (turningTime90) / 90);
    ao();
}





int main()
{
    enable_servos();
    set_servo_position(0, horizontalArm);
    set_servo_position(1, openArm);
    msleep(2000);
        cmpc(0);
    cmpc(1);
    while (analog(0) < 2800) {
        
        mav(0,500);
        mav(1,500);
        
        printf("sensor reads %d\n", analog(0));
        
        msleep(100);
    }
    
    
    mav(0,500);
    mav(1,500);
    msleep(800);
    int driveTime = gmpc(1);
    printf("%d\n", driveTime);
    ao();
    
    msleep(2000);
    
    
    set_servo_position(1, closedArm);
    msleep(2000);
    set_servo_position(0, maxHeightArm);
    msleep(2000);
    turnLeft();
        printf("%d\n",driveTime);
    turnLeft();
    
    cmpc(0);
    cmpc(1);
    while (gmpc(0) < driveTime) {   //2800 ticks = 333 mm  
        mav(0,500);
        mav(1,500);
    }
        printf("STOP");
    mav(0,0);
    mav(1,0);
    msleep(2000);
    
    set_servo_position(1, openArm);
    msleep(2000);
    disable_servos();
        printf("%d\n",driveTime);
    ao();
}

