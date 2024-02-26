

void handleOrdre(OrderList **head, Order newOrder) {

    //Checking if newOrder is already in the order list
    int newOrderNotInList = 1;
    while(head->next != NULL) {
        if( ((*head)->order.floor == newOrder.floor) && ((*head)->order.btype == newOrder.btype) ) {
            newOrderNotInList = 0;
        }
    }
    
    //Adding newOrder to the order list if it is not there jet
    if(newOrderNotInList) {
        addToQueue(head, newOrder);
    }
}