#include "handleOrder.h" //inkluderer queue og button

Button buttons[N_FLOORS*3-2];


void button_init(){

    int count = 0;
    // initialize buttons in first floor
    Button firstFloorUp = {firstFloorUp.floor = 0, firstFloorUp.buttonType = BUTTON_HALL_UP, .lastState = 0};
    buttons[count] = firstFloorUp;
    count++;
    Button firstFloorCab = {firstFloorCab.floor = 0, firstFloorCab.buttonType = BUTTON_CAB, .lastState = 0};
    buttons[count] = firstFloorCab;
    count++;
    // initalize buttons

    for(int f = 1; f < N_FLOORS - 1 ; f++){
        Button newUp = {newUp.floor = f, newUp.buttonType = BUTTON_HALL_UP, .lastState = 0};
        Button newDown = {newDown.floor = f, newDown.buttonType = BUTTON_HALL_DOWN, .lastState = 0};
        Button newCab = {newCab.floor = f, newCab.buttonType = BUTTON_CAB, .lastState = 0};

        buttons[count] = newUp;
        buttons[count + 1] = newDown;
        buttons[count + 2] = newCab;
        count += 3;
    }


    // initialize buttons in last floor
    Button lastFloorUp = {lastFloorUp.floor = N_FLOORS, lastFloorUp.buttonType = BUTTON_HALL_UP, .lastState = 0};
    buttons[count] = lastFloorUp;
    count++;
    Button lastFloorCab = {lastFloorCab.floor = N_FLOORS, lastFloorCab.buttonType = BUTTON_CAB, .lastState = 0};
    buttons[count] = lastFloorCab;
}
Order get_order(Button button){
    Order newOrder = {newOrder.floor = button.floor, newOrder.btype = button.buttonType};
    return newOrder;
}



int loop_through(OrderList ** head){
    /*
    for(int i = 1; i <= 4; i++){
        int btnPressed = elevio_callButton(buttons[i].floor, buttons[i].buttonType);
        if(btnPressed){
            printf("button pressed");
            handleOrdre(head, get_order(buttons[i]));
        }
    }
    */

    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);
            if (btnPressed)
            {
                printf("button pressed \n");
                Order newOrder = {.floor = f, .btype = b};
                handleOrdre(head, newOrder);
            }
            
        }
    }

    /*
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int should_check = 1;

            int btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);
            if (btnPressed)
            {
            }
            
        }
    }
    */
}


