#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "queue.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);

    button_init();

    OrderList * head = NULL;
    Order test1 = {test1.floor = 1, test1.btype = BUTTON_HALL_DOWN};
    Order test2 = {test1.floor = 1, test1.btype = BUTTON_HALL_UP};
    Order test3 = {test1.floor = 88, test1.btype = BUTTON_HALL_DOWN};
    addToQueue(&head, test1);
    addToQueue(&head, test2);
    addToQueue(&head, test3);

    while(1){


        // skrape data
        // loop through buttons
        int floor = elevio_floorSensor();
        Order firstOrder = head->order;
        int test = firstOrder.floor;
        int stop = elevio_stopButton();
        int obstruction = elevio_obstruction();
        printf("%d", floor);

        if(floor > 2){
            elevio_motorDirection(DIRN_DOWN);
        }else if(floor < 2){
            elevio_motorDirection(DIRN_UP);
        }else{
            elevio_motorDirection(DIRN_STOP);
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
