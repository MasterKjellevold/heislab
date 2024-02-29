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
        Order test = {.floor = 3, .btype = BUTTON_CAB};
        
        loop_through(&head);


        if(get_len_of_queue(head) != 0){
            what_to_do(head->order, getLastFloor(), elevio_stopButton(), 0, &beslutnings_matrise, &maske_matrise, &head); //test
        }else{
            if(elevio_stopButton()){
                elevio_motorDirection(DIRN_STOP);
                freeList(&head);
            break;
        }
        }
        
        
        /*
        
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


        
        /*
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            freeList(&head);
            break;
        }
        */
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
