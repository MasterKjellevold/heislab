//#include "moveToFloor.h"
#include "queue.h"

#define ROW_NUM 5
#define COL_NUM 7

typedef struct{
    int rows;
    int cols;
    int data[ROW_NUM][COL_NUM];
} Matrix;


void create_beslutningsmatrise(Matrix * m);
void create_mask_matrix(Matrix * m);
void what_to_do(Order nextOrder, int lastFloor, int stop, int doorOpen, Matrix * bm, Matrix * mm, OrderList ** head);
void master_init(Matrix * bm, Matrix * mm);
void printMatrix(Matrix *matrix);
void openDoor(OrderList ** head);
void handleStop(OrderList ** head);