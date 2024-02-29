#pragma once


typedef struct{
    Order order;
    struct OrderList *next;
 }OrderList;

void queue_init();
void addToQueue(OrderList** head, Order newOrder);
void pop(OrderList **head);
void freeList(OrderList **head);
void removeFloorOrders(OrderList **head, int floor);

Order getOrder(OrderList* head);
int get_len_of_queue(OrderList* head);