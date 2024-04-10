#include <kipr/wombat.h>
// March 11, 2024 CREATE
// variables
int lm_speed = 192; //changed from 192
int rm_speed = 195; //changed from 195

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
    //beginning servo positions: 0-1024, 2-248, 3-1466
    //red/green poms
    drive_forward(400); //move forward
    turn_left(260);
    drive_forward(120);
    msleep(1000);
    raise_claw(1000); //set claw arm to sort top poms
    msleep(1000);
    raise_claw_arm(1331); // set claw arm to sort top pom
    msleep(1000);
    open_claw(1466); //open claw
    msleep(1000000);
    //open_claw(354); //turn robot left toward first top pom

    //rocks (TESTED)
    drive_forward(6600); //drive toward 3 rocks
    turn_left(400); // turn to catch 4th rock
    drive_forward(2800); //drive into rock heap and catch 5th rock 
    turn_left(210);
    drive_forward(1200);
    drive_backward(3000); // back up to prepare for poms
    // third orange pom (TESTED)
    turn_left(230);
    drive_forward(2000);
    drive_backward(2000);
    
    //habitats (NOT TESTED)
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
set_servo_position(3,angle);
} //open or close

void raise_claw(int angle) {
set_servo_position(2, angle);
}

void raise_claw_arm(int angle) {
set_servo_position(0, angle);
}
