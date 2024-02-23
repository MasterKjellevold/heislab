#include "moveToFloor.h"



void moveToFloor(int destination) {

    int floor;
    int stop_is_active;
    while(1){
        floor = elevio_floorSensor();
        stop_is_active = elevio_stopButton();

        //Sjekker om stoppknappen er trykket, og stopper hvis den er
        if(stop_is_active) {
            elevio_motorDirection(DIRN_STOP);
            break;
        }

        //Sjekker om heisen er over, under, eller i riktig etasje, og setter motorretning
        if(destination < floor){
            elevio_motorDirection(DIRN_UP);}
        else if(destination > floor){
            elevio_motorDirection(DIRN_DOWN);}
        else {
            elevio_motorDirection(DIRN_STOP);
            break;}
    }
}