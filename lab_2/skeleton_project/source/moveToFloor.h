#include "driver/elevio.h"
/*
#include "time.h"
#include "button.h"
*/

void updateLastFloor();
void updateLastDir(MotorDirection newDir, int currentFloor); //Må ta inn elevio_floorSensor() som andre parameter
void orientate();
int getLastFloor();
MotorDirection getLastDir();