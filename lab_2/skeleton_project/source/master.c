#include "master.h"


void printMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d\t", matrix->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void create_beslutningsmatrise(Matrix * m){
    m->rows = ROW_NUM;
    m->cols = COL_NUM;
    
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
            {
                m->data[i][j] = 0;
            }
    }

    
    m->data[4][0] = 1;
    
}

Matrix create_mask_matrix(Matrix * m){
    m->rows = ROW_NUM;
    m->cols = COL_NUM;
    
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
            {
                m->data[i][j] = 0;
            }
    }

    
    m->data[4][0] = 1;
}



void init_master(Matrix * bm, Matrix * mm){

    create_beslutningsmatrise(bm);
    create_mask_matrix(mm);
    printMatrix(bm);

}




void what_to_do(Order nextOrder, int lastFloor, int initializing, int stop, int obstruction, Matrix * bm, Matrix * mm){

    int dir = nextOrder.floor-lastFloor;
    int vil_opp, vil_ned, vil_bli;
    if(dir > 0){
        vil_opp = 1;
        vil_ned = 0;
        vil_bli = 0;
    }else if(dir == 0){
        vil_opp = 0;
        vil_ned = 0;
        vil_bli = 1;
    }else if(dir < 0){
        vil_opp = 0;
        vil_ned = 1;
        vil_bli = 0;
    }

    int data[6] = {vil_opp, vil_ned, vil_bli, initializing, stop, obstruction};

    int result[6] = {0, 0, 0, 0, 0, 0};
    for (int j = 0; j < COL_NUM; j++)
    {   
        int sum = 0;
        for (int i = 0; i < ROW_NUM; i++)
        {
            sum += bm->data[i][j]*mm->data[i][j]*data[i];
        }
        result[j] = sum;
        
    }

    if(result[0] == 1){ //stop
        printf("stooop \n");
        exit(0);
    }
    
}