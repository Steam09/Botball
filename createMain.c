#include <kipr/wombat.h>
// March 11, 2024 CREATE
// variables
int lm_speed = 180; 
int rm_speed = 200;

//declare functions
void drive_forward(int distance);
void drive_backward(int distance);
void turn_left(int angle);
void turn_right(int angle);
void open_claw(int angle);
void raise_claw(int angle);

int main()
{
create_connect();
// 0-15 seconds start with front of CREATE 6 cm from black line and on the side of the right PVC pipe
// drive out of starting box and sort poms CREATE
  //turn_left(34); //turn left toward poms
  //drive_forward(20); //move toward poms
  //raise_claw(100); //lower claw to poms
  //open_claw(620); //close claw
//raise plow
//turn left 90 degrees
//pick up red pom with claw
//drop in Area 2
//move forward toward green poms so that plow will drop with poms behind it
//drop plow
//back up and pull green poms into Area 3
//raise plow
//turn right 90 degrees
//move forward to be in line with next set of poms
//turn left 90 degrees
//pick up green pom with claw
//move forward toward red poms so that plow will drop with poms in front of it
//drop plow
//move forward to push red poms into Area 2
//raise plow
//back up into Area 3 and drop pom in claw
    
// 15-45 seconds
// push rocks into area 6 CREATE
    
drive_forward(80); // drive forward toward rocks at T shaped intersection between Areas 3,5,6 (LEGO will put them there)
turn_right(15); // realign
drive_forward(80); //continue driving forward
turn_left(80); // turn left toward rock at intersection between Area 4 and Rock Heap
drive_forward(20); // drive toward it
turn_right(45); // align with rock
drive_forward(60); // push all four rocks into rock heap

// 45-60 seconds
// push fuel into area 4 CREATE
    
//back up till CREATE reaches the line between Areas 5 and 6
//turn left 45 degrees
//move forward and push fuel poms into Area 4
    
// 60-75 seconds
// flip solar panel

//back up till robot is aligned with solar panel's right tube
//turn right 90 degrees
//open claw
//move forward till claw hits back of solar panel
//close claw around right tube
//raise claw arm until it would lose grip (when panel is at about 90 degrees)
//open claw
//raise claw arm enough that claw is not in the way of solar panel moving backward but also so that bottom piece is still under panel
//move CREATE forward to push panel


//75-90 seconds
//put habitats onto short and medium pole (1st and 2nd) closest to starting boxes

//back up into Area 2 until aligned with pink habitats
//raise claw arm to habitat height
//open claw
//move forward to first outer habitat
//close claw
//back up
//turn left to align with shortest post
//move forward or backward to align with shortest post
//lower claw arm
//open claw
//back up to align with pink habitat pole
//turn right to align with pink habitat pole
//raise claw arm to habitat height
//open claw
//move forward to last inner habitat
//close claw
//back up
//turn left to align with 2nd post from moonbase
//move forward or backward to align with post
//lower claw arm
//open claw
    

// 90-105 seconds
//put habitats onto short and medium pole (1st and 2nd) closest to solar panel 
    
//back up
//turn right till lined up with solar panel
//move forward till directly across from pink habitats
//turn left 45 degrees
//raise claw arm to align with habitats
//open claw
//move forward till claw is on outer habitat
//close claw
//back up till aligned with shortest pole close to moon base
//turn right to align with pole
//move forward
//lower claw arm
//open claw
//back up
//turn left to align with habitat pole again
//raise claw arm
//move forward
//close claw
//move backward
//turn right to align with 2nd pole from moon base
//move forward
//lower claw arm
//open claw
    
   
// 105-120 seconds
// return to starting box
    
//back up till aligned with CREATE starting box
//turn right 90 degrees
//move backward into starting box

}

// functions 

void drive_forward(int distance) {
    create_drive_direct(lm_speed, rm_speed);
    msleep(distance / 20 * 1000); // 1000 moves 20 cm 
    create_drive_direct(0, 0);
}

void drive_backward(int distance) {
    create_drive_direct(-lm_speed, -rm_speed);
    msleep(distance / 20 * 1000); // 1000 moves 20 cm 
}

void turn_left(int angle) {
    create_drive_direct(-lm_speed, rm_speed);
    msleep(2050 * angle / 180); // 1800 moves 180 degrees
}

void turn_right(int angle) {
	create_drive_direct(lm_speed, -rm_speed);
    msleep(2050 * angle / 180); // 1800 moves 180 degrees
}

void open_claw(int angle) {
set_servo_position(1,angle);
} //open or close

void raise_claw(int angle) {
set_servo_position(2, angle);
}
