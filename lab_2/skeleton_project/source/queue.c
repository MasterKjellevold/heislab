#include "button.h"
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

    printf("Adding floor %d to queue\n", newOrder.floor);
    //lage ny noede
    OrderList* newNode = (OrderList*)malloc(sizeof(OrderList));
    newNode->order = newOrder;
    newNode->next = NULL;

    

    //er listen tom 
    if(*head == NULL){
        *head = newNode;
        elevio_buttonLamp(newOrder.floor, newOrder.btype, 1); // skrur på lyset
        return; //ferdig
    }


    //traverse
    OrderList *current = *head;
    while(current->next != NULL){
        current = current->next;
    }
    current->next = newNode;
    // OrderList * temp = current->next; //Hva gjør denne???

    //Turnin on light
    // elevio_buttonLamp((newNode)->order.floor, (newNode)->order.btype, 1);
    elevio_buttonLamp(newOrder.floor, newOrder.btype, 1);
}

void pop(OrderList **head){ // delete the first element

    if (*head == NULL) { //tom liste
        printf("List is empty. Cannot pop.\n");
        return;
    }


    // printf("popping floor %d \n", (*(*head)).order.floor);

    //Turning of light
    elevio_buttonLamp((*head)->order.floor, (*head)->order.btype, 0);

    //Removing from list
    OrderList *temp = *head;
    *head = (**head).next;
    free(temp);
}

Order getOrder(OrderList* head){
    Order temp = head->order;
    return temp;
}


int get_len_of_queue(OrderList* head){
    int len = 1;
    if (head == NULL)
    {
        return 0;
    }
    OrderList *current = head;
    while(current->next != NULL){
        current = current->next;
        len ++;
    }
    return len;
}

void freeList(OrderList **head) {
    while(*head != NULL) {
        pop(head);
    }
}

void removeFloorOrders(OrderList **head, int floor) {
    
    OrderList *prev = *head;
    OrderList *current = prev->next;

    while(current != NULL) {

        //Sjekker om head er lik, og popper hvis den er
        if( ((*head)->order.floor) == floor) {
            prev = prev->next;
            current = current->next;
            printf("Popping head\n");
            pop(head);
            continue;
        }

        //Skjekker om order er neste element er lik order, og fjerner hvis den er
        if( (current->order.floor) == floor) {

            OrderList *temp = current;
            prev->next = current->next;
            current = current->next;
            printf("Removing from middle\n");
            elevio_buttonLamp(temp->order.floor, temp->order.btype, 0);
            free(temp);

        }
        else {
            prev = prev->next;
            current = current->next;
        }
    }

    // skjekker head en gang til når (current == NULL)
    if( ((*head)->order.floor) == floor) {
            printf("Popping head when current==NULL\n");
            pop(head);
        }
    
}
