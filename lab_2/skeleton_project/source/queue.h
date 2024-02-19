#include "order.h"
void init();
void addToQueue(order *o);

typedef struct{
    order *order;
    OrderList *next;
 }OrderList;