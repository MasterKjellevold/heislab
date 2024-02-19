#include "order.h"


void button_init();
typedef struct{
    ButtonType buttonType;
    int isPressed;
    int floor;
    int lightIsOn;
} Button;



// isPressed can be found by using the function elevio_callButton(int floor, ButtonType button).
// This function returns an int.

// the button light is set by elevio_buttonLamp(int floor, ButtonType button, int value).
// With value (1 or 0), you chose if you want to turn the light on or off (I hope)
// lightIsOn has to be updated every time elevio_buttonLamp is called

