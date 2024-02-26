#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "queue.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");


    button_init();

    // The list gets initialize here
    OrderList * head = NULL;

    Order volatile test1 = {.floor = 3, .btype = BUTTON_HALL_DOWN};
    Order volatile test2 = {.floor = 1, .btype = BUTTON_HALL_UP};
    Order volatile test3 = {.floor = 2, .btype = BUTTON_HALL_DOWN};
    Order volatile test4 = {.floor = 3, .btype = BUTTON_HALL_DOWN};
    Order volatile test5 = {.floor = 4, .btype = BUTTON_HALL_DOWN};
    Order volatile test6 = {.floor = 5, .btype = BUTTON_HALL_UP};
    Order volatile test7 = {.floor = 6, .btype = BUTTON_HALL_DOWN};
    Order volatile test8 = {.floor = 7, .btype = BUTTON_HALL_DOWN};

    addToQueue(&head, test1);
    addToQueue(&head, test2);
    addToQueue(&head, test3);
    addToQueue(&head, test4);
    addToQueue(&head, test5);
    addToQueue(&head, test6);
    addToQueue(&head, test7);
    addToQueue(&head, test8);
    orientate();
    while(1){


        // skrape data
        // loop through buttons
        // int floor = elevio_floorSensor();
        Order nextOrder = head->order;
        int test = nextOrder.floor;
        moveToFloor(test);
        pop(&head);

       



        /*
        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
        */
        /*
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
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
