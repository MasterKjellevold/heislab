#include "moveToFloor.h"

// Variables
int lastFloor;
//------------

void OpenCloseDoor(){
    elevio_doorOpenLamp(1);
    while(1){
        while(elevio_obstruction()){}
        sleep(3);
        if(!elevio_obstruction()){
            elevio_doorOpenLamp(0);
            break;
        }
    }
}

void orientate() {
    int floor;
    while(1) {
        floor = elevio_floorSensor();
        for(int f = 0; f <= N_FLOORS; f++) {
            if(floor == f) {
                lastFloor = f;
                return;
                }
        }
        elevio_motorDirection(DIRN_DOWN);
    }
}

void updateLastFloor(){
    int floor = elevio_floorSensor();
    if(floor != -1) { //Ser ut til at sensoren gir -1 mellom etasjesensorer
        lastFloor = floor;
    }
}

void moveToFloor(int destination) {
    printf("Moving to %d\n",destination);
    int stop_is_active;
    while(1){
        updateLastFloor();
        stop_is_active = elevio_stopButton();

        //Sjekker om stoppknappen er trykket, og stopper hvis den er
        if(stop_is_active) {
            elevio_motorDirection(DIRN_STOP);
            break;
        }

        //Sjekker om heisen er over, under, eller i riktig etasje, og setter motorretning
        if(destination > lastFloor){
            elevio_motorDirection(DIRN_UP);}
        else if(destination < lastFloor){
            elevio_motorDirection(DIRN_DOWN);}
        else {
            elevio_motorDirection(DIRN_STOP);
            OpenCloseDoor();
            printf("Arrived %d\n",destination);
            break;}

    }
}