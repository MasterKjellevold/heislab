#pragma once
#include "button.h"

void queue_init();
void addToQueue(Order *o);

typedef struct{
    Order *order;
    OrderList *next;
 }OrderList;