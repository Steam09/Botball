#include <kipr/wombat.h>
#include <time.h>

clock_t start = clock(), diff;
diff = clock() - start;
int msec = diff * 1000 / CLOCKS_PER_SEC;
printf("Time taken is %d seconds and %d milliseconds", msec/1000, msec%1000); 

// Ports
int sideServo = 0;
int rotateServo = 1;
int clawServo = 2; 
int lightSensor = 0;


// Moving Times or Speeds
int turningTime90 = 4150;
int leftVelocity = 1000;
int rightVelocity = 960;

// Servo Positions
int horizontalArm = 1473;
int verticalArm = 800;
int openClaw = 20;
int closedClaw = 400;
int innerSide = 200;
int pushedSide = 1500;

void driveForward(int centimeters);
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


    // Push 4 intiail left side habitats to Area 1
    enable_servos();
    set_servo_position(sideServo, pushedSide);
    msleep(50);
    set_servo_position(sideServo, innerSide);

    // Go forward to poms and sort



    // Sweep top rocks to Area 5
    


}


void driveForward(int time) {
    mav(1,leftVel);
    mav(0,rightVel);
    msleep(time);
}

void turnRight() {
    mav(0,-250);
    mav(1,250);
    msleep(turningTime);
    mav(0,0);
    mav(1,0);
}

void turnLeft() {
    mav(0,250);
    mav(1,-250);
    msleep(turningTime);
    mav(0,0);
    mav(1,0);
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

