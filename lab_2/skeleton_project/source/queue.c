#include "queue.h"
#include <stddef.h>

/*
OrderList *head; // peker til det første elementet

void queue_init(){
    Order headNode = {headNode.floor = 0, headNode.btype = BUTTON_CAB}; // lager en vilkårlig head node.
    OrderList *null_ptr = NULL;
    OrderList objectives = {objectives.order = headNode, objectives.next=null_ptr};
    head = &objectives; // setter head peker til den initialiserte objective
}

void addToQueue(Order o){ 
    OrderList* new = (OrderList*)malloc(sizeof(OrderList));
    new->next = NULL;
    new->order = o; //tar inn en ny order, lager en peker til struct orderlist
    OrderList* p = head;
    while(p != NULL){ //travarserer gjennom lista
        p = p->next;
    }
    *p = *new; //det siste elementet peker nå til det nye.
}
*/

void addToQueue(OrderList** head, Order newOrder){

    //lage ny noede
    OrderList* newNode = (OrderList*)malloc(sizeof(OrderList));
    newNode->order = newOrder;
    newNode->next = NULL;


    //er listen tom 
    if(*head == NULL){
        *head = newNode;
        return; //ferdig
    }


    //traverse
    OrderList *current = *head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
}

void pop(OrderList **head){ // delete the first element
    OrderList *temp = *head;
    *head = (**head).next;
    free(temp);
}

Order getOrder(OrderList* head){
    Order temp = head->order;
    return temp;
}
