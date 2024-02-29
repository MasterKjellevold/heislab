#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "master.h"

int main(){
    elevio_init();


    Matrix beslutnings_matrise;
    Matrix maske_matrise;
    master_init(&beslutnings_matrise, &maske_matrise);
    printf("Press the stop button on the elevator panel to exit\n");

    // The list gets initialize here
    OrderList * head = NULL;

    orientate();
    while(1){
        loopThroughButtons(&head);


        if(get_len_of_queue(head) != 0){
            what_to_do(head->order, getLastFloor(), elevio_stopButton(), 0, &beslutnings_matrise, &maske_matrise, &head); //test
        }else{
            if(elevio_stopButton()){
                // elevio_motorDirection(DIRN_STOP);
                // freeList(&head);
                handleStop(&head);
                // break;
            }
        }
    
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
