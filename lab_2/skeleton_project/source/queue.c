#include <stddef.h>
#include "queue.h"


void addOrderToQueue(OrderList** head, Order newOrder){

    printf("Adding floor %d to queue\n", newOrder.floor);
    //lage ny noede
    OrderList* newNode = (OrderList*)malloc(sizeof(OrderList));
    newNode->order = newOrder;
    newNode->next = NULL;

    

    //er listen tom 
    if(*head == NULL){
        *head = newNode;
        elevio_buttonLamp(newOrder.floor, newOrder.btype, 1); // skrur på lyset
        return; //ferdig
    }


    //traverserer gjennom listen
    OrderList *current = *head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newNode;

    //skrur på lys
    elevio_buttonLamp(newOrder.floor, newOrder.btype, 1);
}

void pop(OrderList **head){ // delete the first element

    if (*head == NULL) { //tom liste
        printf("List is empty. Cannot pop.\n");
        return;
    }


    // printf("popping floor %d \n", (*(*head)).order.floor);

    //Turning of light
    elevio_buttonLamp((*head)->order.floor, (*head)->order.btype, 0);

    //Removing from list
    OrderList *temp = *head;
    *head = (**head).next;
    free(temp);
}

int get_len_of_queue(OrderList* head){
    int len = 1;
    if (head == NULL)
    {
        return 0;
    }
    OrderList *current = head;
    while(current->next != NULL){
        current = current->next;
        len ++;
    }
    return len;
}

void freeList(OrderList **head) {
    while(*head != NULL) {
        pop(head);
    }
}

void removeFloorOrders(OrderList **head, int floor) {
    
    OrderList *prev = *head;
    OrderList *current = prev->next;

    while(current != NULL) {

        //Sjekker om head er lik, og popper hvis den er
        if( ((*head)->order.floor) == floor) {
            prev = prev->next;
            current = current->next;
            printf("Popping head\n");
            pop(head);
            continue;
        }

        //Skjekker om order er neste element er lik order, og fjerner hvis den er
        if( (current->order.floor) == floor) {

            OrderList *temp = current;
            prev->next = current->next;
            current = current->next;
            printf("Removing from middle\n");
            elevio_buttonLamp(temp->order.floor, temp->order.btype, 0);
            free(temp);

        }
        else {
            prev = prev->next;
            current = current->next;
        }
    }

    // sjekker head en gang til når (current == NULL)
    if( ((*head)->order.floor) == floor) {
            printf("Popping head when current==NULL\n");
            pop(head);
        }
    
}

void loopThroughButtons(OrderList ** head){

    // løper gjennom alle knappene
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed) { // dersom en knapp er trykt -> ny ordre
                Order newOrder = {.floor = f, .btype = b};
                handleNewOrder(head, newOrder); 
            }
            
        }
    }
}

void handleNewOrder(OrderList **head, Order newOrder) {

    //Checking if the order list is empty, and adding ordre directly
    if(*head == NULL) {
        addOrderToQueue(head, newOrder);
        return;
    }

    //Checking if newOrder is already in the order list
    int newOrderNotInList = 1;
    OrderList *current = *head;
    while(current != NULL) {
        if( (current->order.floor == newOrder.floor) && (current->order.btype == newOrder.btype) ) {
            newOrderNotInList = 0;
            break;
        }
        else {
            current = current->next;
        }
    }
    
    //Adding newOrder to the order list if it is not there jet
    if(newOrderNotInList) {
        addOrderToQueue(head, newOrder);
    }
}