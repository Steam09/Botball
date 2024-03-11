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
int etSensor = 1;

// Moving Times or Speeds
int turningTime90 = 810;
int leftVelocity = 1000;
int rightVelocity = 960;
// 26.5

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
    
    // Push 4 intiail left side habitats to Area 1
    enable_servos();
    set_servo_position(sideServo, pushedSide);
    msleep(50);
    set_servo_position(sideServo, innerSide);

    // Line up with tape
    while (analog(0) < 2800) {
        mav(0,400);
        mav(1,400);
        msleep(50);
    }
    ao();

    // Sweep top rocks to Area 5 Intersection



    driveForward(22, leftVelocity, rightVelocity);
    while (analog(lightSensor) < 2800) { 
        driveForward(0.2, 100, 100)
    }


    
    // Light Switch
    cmpc(0);
    set_servo_position(rotateServo, 1400);
    while (analog(etSensor) < 2800) { 
        driveForward(0.2, 100, 100)
    }
    set_servo_position(rotateServo, 1600);
    msleep(400);
    set_servo_position(rotateServo, 1400);

    // Top Cubes
    driveForward(-4, 500, 500)
    set_servo_position(rotateServo, verticalArm);

    

}

























void driveForward(float cm, int leftSpeed, int rightSpeed) {
    mav(1,leftVelocity);
    mav(0,rightVelocity);
    msleep(cm*1000/26.5);
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

