#include <kipr/wombat.h>
#include <time.h>

clock_t start = clock(), diff;
ProcessIntenseFunction();
diff = clock() - start;

int msec = diff * 1000 / CLOCKS_PER_SEC;
printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);

create3_pose_get();

// March 11, 2024 CREATE
int main()
{
// functions 
    void drive_forward(int distance) {}
    void turn_left(void) {}
    void turn_right(void) {}
    void drive_backward(int distance) {}
    void raise_claw(int angle) {}
    void lower_claw(int angle) {}
    void raise_plow(int angle) {}
    void lower_plot(int angle) {}    

// variables
    int speed = __; 


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

