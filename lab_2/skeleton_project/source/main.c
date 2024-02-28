#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "master.h"

int main(){
    elevio_init();


    Matrix beslutnings_matrise;
    Matrix maske_matrise;
    init_master(&beslutnings_matrise, &maske_matrise);
    printf("Press the stop button on the elevator panel to exit\n");
    button_init();

    // The list gets initialize here
    OrderList * head = NULL;

    orientate();
    while(1){
        Order test = {.floor = 6, .btype = BUTTON_CAB};
        what_to_do(test, 0, 0, 1, 0, &beslutnings_matrise, &maske_matrise); //test
        /*
        loop_through(&head);
        if(get_len_of_queue(head) != 0){  // dersom køen er tom, skjer det ingenting
            // skrape data
            // loop through buttons
            // int floor = elevio_floorSensor();
            Order nextOrder = head->order;
            int nextFloor = nextOrder.floor;
            moveToFloor(nextFloor, &head);
            pop(&head);
        }

        /*
        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
        
        */

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
