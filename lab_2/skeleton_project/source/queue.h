#pragma once
#include "driver/elevio.h"

typedef struct {
    int floor;
    ButtonType btype;
} Order;


typedef struct{
    Order order;
    struct OrderList *next;
 }OrderList;

void addOrderToQueue(OrderList** head, Order newOrder);
void pop(OrderList **head);
void freeList(OrderList **head);
void removeFloorOrders(OrderList **head, int floor);
void loopThroughButtons(OrderList ** head);
int get_len_of_queue(OrderList* head);
void handleNewOrder(OrderList **head, Order newOrder);