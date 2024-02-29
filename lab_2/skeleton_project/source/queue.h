#pragma once


typedef struct{
    Order order;
    struct OrderList *next;
 }OrderList;

void queue_init();
void addToQueue(OrderList** head, Order newOrder);
Order getOrder(OrderList* head);
void pop(OrderList **head);
int get_len_of_queue(OrderList* head);
void freeList(OrderList **head);