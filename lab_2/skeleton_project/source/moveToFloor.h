#include "driver/elevio.h"
#include "time.h"
#include "button.h"


void updateLastFloor();
void updateLastDir(MotorDirection newDir, int currentFloor); //Må ta inn elevio_floorSensor() som andre parameter
void moveToFloor(int destination, OrderList ** head);
void orientate();
int getLastFloor();
MotorDirection getLastDir();