#include <kipr/wombat.h>
// March 11, 2024 CREATE
// variables
int lm_speed = 98; 
int rm_speed = 110;

//declare functions
void drive_forward(int time);
void drive_backward(int time);
void turn_left(int angle);
void turn_right(int angle);
void open_claw(int angle);
void raise_claw(int angle);
void raise_claw_arm(int angle);

int main()
{
	create_connect();
    drive_forward(11700);
    turn_left(1000);
    drive_forward(4600);
    turn_right(200);
    drive_forward(1300);
    drive_backward(6000);
}

void drive_forward(int time) {
    create_drive_direct(lm_speed, rm_speed);
    msleep(time);
    create_drive_direct(0, 0);
}


void drive_backward(int time) {
    create_drive_direct(-lm_speed, -rm_speed);
    msleep(time);
    create_drive_direct(0, 0);
}

void turn_left(int angle) {
    create_drive_direct(-lm_speed, rm_speed);
    msleep(angle);
    create_drive_direct(0, 0);

}

void turn_right(int angle) {
	create_drive_direct(lm_speed, -rm_speed);
    msleep(angle);
    create_drive_direct(0, 0);
}

void open_claw(int angle) {
set_servo_position(0,angle);
} //open or close

void raise_claw(int angle) {
set_servo_position(1, angle);
}

void raise_claw_arm(int angle) {
set_servo_position(2, angle);
}
