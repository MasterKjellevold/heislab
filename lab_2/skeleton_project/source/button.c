#include "button.h"

Button buttons[];


void init_button(){

    // initialize buttons in first floor
    Button *firstFloorUp = {firstFloorUp.floor = 1, firstFloorUp.buttonType = BUTTON_HALL_UP};
    Button *firstFloorCab = {firstFloorUp.floor = 1, firstFloorUp.buttonType = BUTTON_CAB}

    // initalize buttons
    int count = 0;
    for(int f = 1; f < N_FLOORS - 2 ; f++){
        Button *newUp = {new.floor = f, new.buttonType = BUTTON_HALL_UP};
        Button *newDown = {new.floor = f, new.buttonType = BUTTON_HALL_DOWN};
        Button *newCab = {new.floor = f, new.buttonType = BUTTON_CAB};

        button[count] = newUp;
        button[count + 1] = newDown;
        button[count + 2] = new
        count += 3;
    }
    // initialize buttons in last floor
    Button *lastFloorUp = {lastFloorUp.floor = N_FLOORs, lastFloorUp.buttonType = BUTTON_HALL_UP};
    Button *lastFloorCab = {lastFloorUp.floor = N_FLOORS, lastFloorUp.buttonType = BUTTON_CAB}
}

void loop_through(){

}



Order get_order(Button button){
    Order newOrder = {newOrder.floor = button.floor, newOrder.btype = button.buttonType};
    return newOrder;
}