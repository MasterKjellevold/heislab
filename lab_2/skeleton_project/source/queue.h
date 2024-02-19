#pragma once
#include "button.h"

void queue_init();
void addToQueue(Order *o);

typedef struct{
    Order *order;
    struct OrderList *next;
 }OrderList;