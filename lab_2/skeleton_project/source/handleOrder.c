#include "handleOrder.h"


void handleOrdre(OrderList **head, Order newOrder) {

    //Checking if the order list is empty, and adding ordre directly
    if(*head == NULL) {
        addToQueue(head, newOrder);
        return;
    }

    //Checking if newOrder is already in the order list
    int newOrderNotInList = 1;
    OrderList *current = *head;
    while(current->next != NULL) {
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
        addToQueue(head, newOrder);
    }
}