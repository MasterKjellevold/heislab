#include "moveToFloor.h"

// Variables
int lastFloor;
MotorDirection lastDir;
//------------

int getLastFloor() {
    updateLastFloor();
    return lastFloor;
}

MotorDirection getLastDir() {
    return lastDir;
}

void updateLastFloor(){
    int floor = elevio_floorSensor();
    if(floor != -1) { //Ser ut til at sensoren gir -1 mellom etasjesensorer
        lastFloor = floor;
    }
    elevio_floorIndicator(lastFloor);
}

void updateLastDir(MotorDirection newDir, int currentFloor) {
    if(!(currentFloor == -1)){
        lastDir = newDir;
    }
}

void orientate() {
    printf("oriantating\n");
    int floor;
    while(1) {
        if(elevio_stopButton()) {
            handleStop();
            return;
        }
        floor = elevio_floorSensor();
        for(int f = 0; f <= N_FLOORS; f++) {
            if(floor == f) {
                lastFloor = f;
                printf("orientated to floor %d \n", floor);
                elevio_motorDirection(DIRN_STOP);
                updateLastFloor();
                return;
                }
        }
        elevio_motorDirection(DIRN_DOWN);
        updateLastDir(DIRN_DOWN, elevio_floorSensor());
    }

}