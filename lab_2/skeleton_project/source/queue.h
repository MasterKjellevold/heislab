#pragma once
#include "button.h"


typedef struct{
    Order order;
    struct OrderList *next;
 }OrderList;

void queue_init();
void addToQueue(OrderList** head, Order newOrder);
Order getOrder(OrderList* head);
void pop(OrderList **head);
