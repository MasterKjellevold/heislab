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
    
    //Setter alle elementer i matirsen til 0
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
            {
                m->data[i][j] = 0;
            }
    }

    //Definerer beslutningsmatrisen (se excel-ark)------------------------------------------------------------------------
                        m->data[0][1] = 1;  m->data[0][2] = 1;
                                                                m->data[1][3] = 1;  m->data[1][4] = 1;
                                                                                                        m->data[2][5] = 1;  m->data[2][6] = 1;
    m->data[3][0] = 1;
                                            m->data[4][2] = 1;                      m->data[4][4] = 1;                      m->data[4][6] = 1;
    //------------------------------------------------------------------------------------------------------
}

void create_mask_matrix(Matrix * m){
    m->rows = ROW_NUM;
    m->cols = COL_NUM;
    
    //Setter alle element i matrisen til 0
    for (int i = 0; i < ROW_NUM; i++)
    {
        for (int j = 0; j < COL_NUM; j++)
            {
                m->data[i][j] = 0;
            }
    }

    //Definerer maskematrisen (se excel-ark)--------------------------------------------------------------------------------------------------
                        m->data[0][1] = 1;  m->data[0][2] = 1;
                                                                m->data[1][3] = 1;  m->data[1][4] = 1;
                                                                                                        m->data[2][5] = 1;  m->data[2][6] = 1;
    m->data[3][0] = 1;  m->data[3][1] = 1;  m->data[3][2] = 1;  m->data[3][3] = 1;  m->data[3][4] = 1;  m->data[3][5] = 1;  m->data[3][6] = 1;
                        m->data[4][1] = 1;  m->data[4][2] = 1;  m->data[4][3] = 1;  m->data[4][4] = 1;  m->data[4][5] = 1;  m->data[4][6] = 1;
    //-----------------------------------------------------------------------------------------------------------------------------------------
}



void init_master(Matrix * bm, Matrix * mm){

    create_beslutningsmatrise(bm);
    create_mask_matrix(mm);
    printMatrix(bm);
    printMatrix(mm);

}




void what_to_do(Order nextOrder, int lastFloor, int stop, int doorOpen, Matrix * bm, Matrix * mm, OrderList ** head){

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

    int data[5] = {vil_opp, vil_ned, vil_bli, stop, doorOpen};
    int result[7] = {0, 0, 0, 0, 0, 0, 0};


    // oge matrix
    int og_matrix[ROW_NUM][COL_NUM];
    for (int i = 0; i < COL_NUM; i++)
    {
        for (int j = 0; j < ROW_NUM; j++)
        {
            og_matrix[j][i] = data[j] && mm->data[j][i];
        }
        
    }
    

    // sammenligne matrix
    for (int col = 0; col< COL_NUM; col++)
    {
        int like = 1;
        for (int row = 0; row < ROW_NUM; row++)
        {
            if(og_matrix[row][col] != bm->data[row][col]) like = 0;
        }
        
        result[col] = like;
    }
    


    if(result[0] == 1){ //stop
        freeList(head);
        printf("stooop \n");
        elevio_motorDirection(DIRN_STOP);
        exit(0);
    }



    if(result[1] == 1){
        elevio_motorDirection(DIRN_UP);
    }
    if(result[2] == 1){
        elevio_motorDirection(DIRN_STOP);
    }
    if(result[3] == 1){
        elevio_motorDirection(DIRN_DOWN);
    }
    if(result[4] == 1){
        elevio_motorDirection(DIRN_STOP);
    }
    if(result[5] == 1){
        elevio_motorDirection(DIRN_STOP);
        // pop(head);
        removeFloorOrders(head, nextOrder.floor);
        openDoor(head);

    }
    if(result[6] == 1){
        elevio_motorDirection(DIRN_STOP);
    }
    
}

void openDoor(OrderList ** head){
    elevio_doorOpenLamp(1);
    printf("opening door\n");
    clock_t before = clock();
    int msec = 0;
    int timer = 1000;
    while(msec < timer){
        if(elevio_obstruction()){
            printf("reseting time\n");
            before = clock();
        }

        //Handle orders and stop button
        loop_through(head);
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            freeList(&head);
            break;
        }


        clock_t diff = clock() - before;
        msec = (diff * 1000/ CLOCKS_PER_SEC);
        // printf("msec: %d timer: %d\n", msec, timer);
    }
    printf("closing door\n");
    elevio_doorOpenLamp(0);
    
}
