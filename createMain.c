#include <kipr/wombat.h>

int main()
{
    create_connect();
    enable_servos();
        //pushing green poms into Area 2
    drive_forward(2200);
    msleep(500);
    turn_left(500);
    msleep(500);
    drive_forward(1000);
    turn_left(300);
    drive_forward(900);
    msleep(500);
    turn_left(200);
    msleep(500);
    drive_backward(1100);
    msleep(500);
    turn_right(1000);
    drive_forward(600);
    turn_right(1000);
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
}
