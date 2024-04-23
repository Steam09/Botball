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
    //msleep(15000);
 
    raise_claw_arm(931); // port 0 - 931
    raise_claw(1452); // port 2 - formerly 1831
    open_claw(1800); 
    
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
    turn_left(460); //CHANGED from 420
    
    // taller green multipliers
    msleep(500);
    drive_forward(2535); //was 2585 
    msleep(1000);
    raise_claw(1770); //was 1750 CHANGED port 2
    msleep(1000);
    servoSpeed(3, 30, 1800, 450); //close claw
    //open_claw(450); // close claw
    msleep(1000);
    drive_backward(1500);
    turn_right(1000);
    //raise_claw_arm(1700); //was 1840 port 0 
    servoSpeed(0, 30, 931, 1791); //changed
    msleep(500);
    open_claw(1600);
    raise_claw_arm(650);
    
    //split multipliers & move one to fuel area
    turn_right(130);
    drive_forward(800);
    
 /*   raise_claw_arm(1000);
    msleep(1000);
    turn_right(130);
    msleep(1000);
    drive_forward(1200);
    msleep(1000);
*/
    //pushing third fuel
    turn_right(2500); //decrease this turn was 2500 changed
    msleep(1000);
    drive_forward(710); //was 1200 changed
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
    
    //pushing green poms into Area 2
    drive_forward(2200); //long distance across board going past moonbase
    msleep(500);
    turn_left(600); //turns to push poms that are farther from startbox
    msleep(500);
    drive_forward(1000);
    turn_left(300);
    drive_forward(300);
    msleep(500);
    turn_left(200);
    msleep(500);
    drive_backward(1100); //BACKS UP
    msleep(500);
    turn_right(500); //turns, might hit poms that are closer to startbox 
    msleep(500);
    drive_forward(700); 
    msleep(500);
    turn_right(200);
    msleep(500);
    drive_forward(300);
    msleep(500);
    turn_right(300); //finishes turning to face habitats
    msleep(500); 
    drive_forward(500);
    msleep(500);
    turn_right(600);
    msleep(500);
    drive_forward(400);
    msleep(500); 
    
    
    
    //positions claw to pick up habitats
    raise_claw_arm(1702);
    raise_claw(1100);
    open_claw(1100);
    msleep(500);
    
    turn_right(700);
    msleep(500);
    
    //taller horizontal habitats
    //raise_claw(320);
    //open_claw(0);
    
    servoSpeed(2, 30, 1100, 320);
    servoSpeed(3, 30, 1100, 0);
    
    drive_backward(1000);
    turn_left(200);
    drive_forward(700);
    raise_claw(1200);
    open_claw(1036);
    
    
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
