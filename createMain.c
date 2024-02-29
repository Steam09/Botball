#include <kipr/wombat.h>
#include <time.h>

clock_t start = clock(), diff;
ProcessIntenseFunction();
diff = clock() - start;

int msec = diff * 1000 / CLOCKS_PER_SEC;
printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);

create3_pose_get();


int main() {
    create_connect();
    enable_servos();
    cmpc(0);
    cmpc(1);
    set_servo_position();
    set_servo_position();



}
