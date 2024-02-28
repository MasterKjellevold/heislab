#include "moveToFloor.h"


#define ROW_NUM 6
#define COL_NUM 5

typedef struct{
    int rows;
    int cols;
    int data[ROW_NUM][COL_NUM];
} Matrix;


void create_beslutningsmatrise(Matrix * m);
Matrix create_mask_matrix(Matrix * m);
void what_to_do(Order nextOrder, int lastFloor, int initializing, int stop, int obstruction, Matrix * bm, Matrix * mm);
void init_master(Matrix * bm, Matrix * mm);
void printMatrix(Matrix *matrix);