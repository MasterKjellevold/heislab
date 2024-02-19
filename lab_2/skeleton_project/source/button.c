#include "button.h"

Button *buttons[(N_FLOORS-2)*3+4];


void init_button(){

    // initialize buttons in first floor
    Button *firstFloorUp = {firstFloorUp->floor = 1, firstFloorUp->buttonType = BUTTON_HALL_UP};
    Button *firstFloorCab = {firstFloorCab->floor = 1, firstFloorCab->buttonType = BUTTON_CAB};

    // initalize buttons
    int count = 0;
    for(int f = 1; f < N_FLOORS - 2 ; f++){
        Button *newUp = {newUp->floor = f, newUp->buttonType = BUTTON_HALL_UP};
        Button *newDown = {newDown->floor = f, newDown->buttonType = BUTTON_HALL_DOWN};
        Button *newCab = {newCab->floor = f, newCab->buttonType = BUTTON_CAB};

        buttons[count] = newUp;
        buttons[count + 1] = newDown;
        buttons[count + 2] = newCab;
        count += 3;
    }
    // initialize buttons in last floor
    Button *lastFloorUp = {lastFloorUp->floor = N_FLOORS, lastFloorUp->buttonType = BUTTON_HALL_UP};
    Button *lastFloorCab = {lastFloorCab->floor = N_FLOORS, lastFloorCab->buttonType = BUTTON_CAB};
}

int loop_through(){
    return 0;
}



Order get_order(Button button){
    Order newOrder = {newOrder.floor = button.floor, newOrder.btype = button.buttonType};
    return newOrder;
}