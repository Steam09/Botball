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
void servoSpeed(int port, int speed, int initialPosition, int endPosition);

int main()
{
	create_connect();
    enable_servos();
    /*
        wait_for_light(0);
    */
    
    //PAUSE TO GIVE LEGOBOT TIME
    msleep(12000);
    
    //beginning servo positions: 0-1024, 2-248, 3-1466
/*    //red/green poms (NOT TESTED)
    drive_forward(2000); //move forward
    turn_left(260);
    drive_forward(120);
    msleep(1000);
    raise_claw_arm(1843); // set claw arm to sort top pom
	msleep(1000);
    raise_claw(1651); //set claw arm to sort top poms
    msleep(1000);
    open_claw(1024); //open claw
    turn_left(200); // turn toward poms
    msleep(1000000);
    //open_claw(354); //turn robot left toward first top pom
*/
    raise_claw_arm(931); // port 0 - 931
    raise_claw(1452); // port 2 - formerly 1831
    open_claw(1600); 
    
    //rocks (TESTED)
    drive_forward(6600); //drive toward 3 rocks
    turn_left(400); // turn to catch 4th rock
    drive_forward(3000); //drive into rock heap and catch 5th rock 
    turn_left(190); // turn toward rock heap
    drive_forward(1000); // push //CHANGED from 1200
    turn_right(120); // turn right to unlatch from rock
    drive_backward(500); // back up to prepare for poms
    turn_left(300);
    drive_backward(1600);
    
    // 2 orange poms (TESTED)
    turn_left(480); //CHANGED from 420
    
    // taller green multipliers
    msleep(500);
    drive_forward(2600); //CHANGEDDDDDDDDDDDDDDDDDDDDDDDDDDDDD
    msleep(1000);
    raise_claw(1750); //was 1800 CHANGED port 2
    msleep(1000);
    open_claw(250); // close claw
    msleep(1000);
    drive_backward(1500);
    turn_right(1000);
    //raise_claw_arm(1700); //was 1840 port 0 
    servoSpeed(0, 30, 931, 1791); //CHANGEDDDDDDDDDDDDDDDD
    msleep(500);
    open_claw(1600);
    
    //split multipliers & move one to fuel area
    raise_claw_arm(1000);
    msleep(1000);
    turn_right(140);
    msleep(1000);
    drive_forward(1200);
    msleep(1000);

    //pushing third fuel
    turn_right(2500); //decrease this turn was 2500 changed
    msleep(1000);
    drive_forward(700); //was 1200 changed
    msleep(500);
    turn_right(300);
    drive_forward(370);
    drive_backward(800);
    turn_left(800);
    drive_forward(1300);
    turn_right(800);
    msleep(500);
    drive_forward(350);
    drive_backward(500);
    turn_left(800); //800 to go straight
    msleep(500);
    
    //setting servos for horizontal habitats
    raise_claw_arm(2047);
    raise_claw(350);
    open_claw(1100);
    msleep(500);
    
    //pushing green poms into Area 2
    drive_forward(2200);
    msleep(500);
    turn_left(600);
    msleep(500);
    drive_forward(1000);
    turn_left(300);
    drive_forward(600);
    msleep(500);
    turn_left(200);
    msleep(500);
    drive_backward(1100);
    msleep(500);
    turn_right(1000);
    drive_forward(600);
    turn_right(600);
    msleep(500);
    drive_forward(600);
    msleep(500);
    turn_right(600);
    msleep(500);
    drive_forward(600);
    
    //taller horizontal habitats
    open_claw(0);
    drive_backward(1000);
    turn_left(100);
    drive_forward(1000);
    raise_claw(1100);
    open_claw(1036);
    
    
    
    //habitats (NOT TESTED)
    /*open_claw(900);
    drive_backward(350);
    turn_left(140);
    drive_forward(200);
    raise_claw_arm(1990);
    raise_claw(1000);
    msleep(500);
    open_claw(180); */
    
    printf("done\n");
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


    //splitting multipliers w servoSpeed
    /*msleep(500);
    servoSpeed(2, 500, 1800, 1700); 
    msleep(1000);
    turn_left(150); 
    msleep(1000);
    msleep(1000);
    servoSpeed(2, 500, 1700, 1850); 
    msleep(1000);
    servoSpeed(3, 500, 1600, 500); 
    msleep(1000);
    turn_left(100);*/
