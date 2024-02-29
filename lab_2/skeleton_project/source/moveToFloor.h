#include "driver/elevio.h"
#include "time.h"
#include "button.h"


void updateLastFloor();
void moveToFloor(int destination, OrderList ** head);
void orientate();
int lastFloor();