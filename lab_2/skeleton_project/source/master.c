#include "master.h"
#include "time.h"


//printer matrise
void printMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d\t", matrix->data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//lager beslutningsmatrisa
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



void master_init(Matrix * bm, Matrix * mm){

    create_beslutningsmatrise(bm);
    create_mask_matrix(mm);
    printf("Beslutningsmatrise:\n");
    printMatrix(bm);
    printf("Maskematrise:\n");
    printMatrix(mm);

}


// her er selve aksjonen. 
void what_to_do(Order nextOrder, int lastFloor, int stop, int doorOpen, Matrix * bm, Matrix * mm, OrderList ** head){

    int isBetween;
    if(elevio_floorSensor() == -1) {
        isBetween = 1;
    }else {
        isBetween = 0;
    }
    int dir = nextOrder.floor-lastFloor;
    int vil_opp, vil_ned, vil_bli;
    
    if(!isBetween) {
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
    }else {
        if(dir > 0 || (dir == 0 && (getLastDir() == -1) )){
            vil_opp = 1;
            vil_ned = 0;
            vil_bli = 0;
        }else if(dir < 0 || (dir == 0 && (getLastDir() == 1) )){
            vil_opp = 0;
            vil_ned = 1;
            vil_bli = 0;
        }
    }


    int data[5] = {vil_opp, vil_ned, vil_bli, stop, doorOpen};
    int result[7] = {0, 0, 0, 0, 0, 0, 0};


    // & matrix
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
    



    //aksjoner ->
    if(result[0] == 1){ //stop
        handleStop(head);
        return;
    }
    if(result[1] == 1){
        elevio_motorDirection(DIRN_UP);
        updateLastDir(DIRN_UP, elevio_floorSensor());
    }
    if(result[2] == 1){
        elevio_motorDirection(DIRN_STOP);
    }
    if(result[3] == 1){
        elevio_motorDirection(DIRN_DOWN);
        updateLastDir(DIRN_DOWN, elevio_floorSensor());
    }
    if(result[4] == 1){
        elevio_motorDirection(DIRN_STOP);
    }
    if(result[5] == 1){
        elevio_motorDirection(DIRN_STOP);
        removeFloorOrders(head, nextOrder.floor);
        openDoor(head);
        

    }
    if(result[6] == 1){
        elevio_motorDirection(DIRN_STOP);
    }
    
}


// åpne døra
void openDoor(OrderList ** head){
    elevio_doorOpenLamp(1);
    //printf("opening door\n");
    clock_t before = clock();
    int msec = 0;
    int timer = 3000;
    while(msec < timer){
        if(elevio_obstruction()){
            //printf("reseting time\n");
            before = clock();
        }

        //Handle orders and stop button
        loopThroughButtons(head);
        if(elevio_stopButton()){
            elevio_doorOpenLamp(1);
            before = clock();
            handleStop(head);
            // elevio_motorDirection(DIRN_STOP);
            // freeList(&head);
            // break;
        }


        clock_t diff = clock() - before;
        msec = (diff * 2000/ CLOCKS_PER_SEC);
        // printf("msec: %d timer: %d\n", msec, timer);
    }

    elevio_doorOpenLamp(0);
    
}


//hva som skjer om stoppknappen blir trykket
void handleStop(OrderList ** head) {
    printf("STOP\n");
    freeList(head);
    elevio_motorDirection(DIRN_STOP);
    elevio_stopLamp(1);

    if(elevio_floorSensor() != -1) {
        elevio_doorOpenLamp(1);
    }

    while(elevio_stopButton()) {
    }

    elevio_stopLamp(0);

    if(elevio_floorSensor() != -1) {
        openDoor(head);
    }
}
