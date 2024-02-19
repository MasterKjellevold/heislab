#include "queue.h"
#include <stddef.h>


OrderList *head; // peker til det første elementet

void queue_init(){
    Order headNode = {headNode.floor = 0, headNode.btype = BUTTON_CAB}; // lager en vilkårlig head node.
    OrderList *null_ptr = NULL;
    OrderList objectives = {objectives.order = &headNode, objectives.next=null_ptr};
    head = &objectives; // setter head peker til den initialiserte objective
}

void addToQueue(Order *o){ 
    OrderList* new = {new->next = NULL, new->order = o}; //tar inn en ny order, lager en peker til struct orderlist
    OrderList* p = head;
    while(p != NULL){ //travarserer gjennom lista
        p = p->next;
    }
    *p = *new; //det siste elementet peker nå til det nye.
}

void pop(){ // delete the first element
    OrderList *temp = head;
    head = head->next;
    free(temp);
}