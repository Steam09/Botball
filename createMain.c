#include <kipr/wombat.h>

// variables
int speed = __; 

void turn_right(void) {}
void drive_backward(int distance) {}
void raise_claw(int angle) {}
void lower_claw(int angle) {}
void raise_plow(int angle) {}
void lower_plot(int angle) {}    


\\ create3_pose_get();

\\ March 11, 2024 CREATE
int main()
{




// 0-15 seconds 
// drive out of starting box and sort poms CREATE
// turn in starting box and push habitats into area 1 LEGO
    
// 15-30 seconds
// push rocks into area 6 CREATE
// push rocks into area 6 LEGO

// 30-45 seconds
// push fuel into area 4 CREATE
// 
    
// 45-60 seconds
// push rocks into Rock Heap

//60-90 seconds
// flip solar panel

// 90-105 seconds
// Margin of error
   
// 105-120 seconds
// return to starting box

}

void drive_forward(int distance) {
    set_create_distance(0);
    while(abs(get_create_distance ()) < distance) {
        create_drive_direct(200,200);
        msleep(10);
    }
}

void turn_left(void) {
    set_create_total_angle(0);
    while(abs(get_create_total_angle ()) < 90) {
        create_drive_direct(-200,200);
        msleep(10);
    }
}
