/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*					                    WIN32 PORT & LINUX PORT
*                          (c) Copyright 2004, Werner.Zimmermann@fht-esslingen.de
*                 (Similar to Example 1 of the 80x86 Real Mode port by Jean J. Labrosse)
*                                           All Rights Reserved
** *****************************************************************************************************
*		Further modified by 	mikael.jakas@puv.fi &
* 					Jukka.matila@vamk.fi
* *****************************************************************************************************
*                                               EXAMPLE #1
*********************************************************************************************************
*/

#include "includes.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define  N_TASKS                        4       /* Number of identical tasks                          */



/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/



OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];

OS_EVENT* BoardSem, *Player1Sem,  *Player2Sem, *StatusSem;


INT8U HORIZONTAL = 3;
INT8U VERTICAL = 3;
char          TaskData[N_TASKS];                      /* Parameters to pass to each task               */
char          board[3][3];
INT8U game_status;
INT16U A[9];



/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void TaskStart(void* data);        /* Function prototype of Startup task           */

void DrawBoard(char board[3][3]);
void Game(void* data);
void Player1(void* data);
void Player2(void* data);
void GameStatus(void* data);





/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

int  main(void)
{
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

    OSInit();                                              /* Initialize uC/OS-II                      */

    Player2Sem = OSSemCreate(1);
    
    Player1Sem = OSSemCreate(1);




    OSTaskCreate(TaskStart, (void*)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
    OSStart();                                             /* Start multitasking                       */
    return 0;
}


/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
void TaskStart(void* pdata)
{
    INT16S key;
    INT8U symbol;
    INT8U symbol2;


    pdata = pdata;               /* Prevent compiler warning                 */

    symbol ='X';
    symbol2 = 'O';

   
   
   OSTaskCreate(Game, (void*)&symbol, (void*)&TaskStk[0][TASK_STK_SIZE - 1], 1);
   // OSTaskCreate(Player1, (void*)&symbol, (void*)&TaskStk[2][TASK_STK_SIZE - 1], 3);
   // OSTaskCreate(Player2, (void*)&symbol2, (void*)&TaskStk[3][TASK_STK_SIZE - 1], 4);

   //  OSTaskCreate(GameStatus, (void*)&symbol, (void*)&TaskStk[3][TASK_STK_SIZE - 1], 4);


    for (;;) {

        if (PC_GetKey(&key) == TRUE) {                     /* See if key has been pressed              */
            if (key == 0x1B) {                             /* Yes, see if it's the ESCAPE key          */
                exit(0);  	                           /* End program                              */
            }
        }
        OSTimeDlyHMSM(0, 0, 1, 0);                         /* Wait one second                          */
    }
}

/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

void DrawBoard(char board[3][3] )
{
    INT8U  err;
    OSMboxPend(BoardSem, 0, &err);
   

    INT8U size;
    size = '1';


    //numbers
    for (HORIZONTAL = 0; HORIZONTAL < 3; HORIZONTAL++)
    {
        for (VERTICAL = 0; VERTICAL < 3; VERTICAL++)
        {
            board[HORIZONTAL][VERTICAL] = size;
            size++;
        }
    }
    //layout
    for (HORIZONTAL = 0; HORIZONTAL < 3; HORIZONTAL++)
    {
        for (VERTICAL = 0; VERTICAL < 3; VERTICAL++)
        {
            printf("%c", board[HORIZONTAL][VERTICAL]);
            if (VERTICAL != 3)
                printf("|");
        }
        if (HORIZONTAL != 3) {
            printf("\n------");
            printf("\n");
        }
    }
    OSMboxPost(BoardSem, (void*)1);
   
}
















void Game(INT8U* text_ptr)
{
 
     INT8U x; 
    INT8U o;
    INT8U count = 0;
//    int game_status;
    DrawBoard(board);
    while (1);

    OSTimeDlyHMSM(0, 0, 1, 0 );

    if (count == 0 || count % 2) {
        Player1(x);     
       // player = 1;
        count++;
        OSTimeDlyHMSM(0, 0, 0, 50);
    }
    else
    {
        Player2(&o);
//     player = 2;
       count++;
        
   }

    GameStatus(game_status);


}




void Player1(INT8U* text_ptr) {

    INT8U err;
  
   OSSemPend(Player1Sem, 0, &err);
    int choice;
    int x=0;
    int y=0;
   
    printf("\n pick any value from 1-9 for X: ");
    scanf_s("%d", &choice);
    if (choice == 1 && A[choice] != 1 && A[choice] != 2) {
        
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY); 
        A[choice] = 1;
    }
    if (choice == 2 && A[choice] != 1 && A[choice] != 2) {
        int x = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }
    if (choice == 3 && A[choice] != 1 && A[choice] != 2) {
        int x = 4;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }
    if (choice == 4 && A[choice] != 1 && A[choice] != 2) {
        int y = 1;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }
    if (choice == 5 && A[choice] != 1 && A[choice] != 2) {
        int x = 2;
        int y = 1;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }
    if (choice == 6 && A[choice] != 1 && A[choice] != 2) {
        int x = 4;
        int y = 1;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }
    if (choice == 7 && A[choice] != 1 && A[choice] != 2) {
        
        int y = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }

    if (choice == 8 && A[choice] != 1 && A[choice] != 2) {
        int x = 2;
        int y = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }

    if (choice == 9 && A[choice] != 1 && A[choice] != 2) {
        int x = 4;
        int y = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 1;
    }


    else
    {
        printf("Invalid input, please try again: ");
        scanf_s("%d", &choice);
    }

    printf("\n");
    OSSemPost(Player1Sem);

    


}


void Player2(INT8U* text_ptr) {
    INT8U err;
    OSSemPend(Player2Sem, 0, &err);
    int choice;
    int x = 0;
    int y = 0;

    printf("\n pick any value from 1-9 for O: ");
    scanf_s("%d", &choice);
    if (choice == 1 && A[choice] != 1 && A[choice] != 2) {

        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }
    if (choice == 2 && A[choice] != 1 && A[choice] != 2) {
        int x = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }
    if (choice == 3 && A[choice] != 1 && A[choice] != 2) {
        int x = 4;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }
    if (choice == 4 && A[choice] != 1 && A[choice] != 2) {
        int y = 1;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }
    if (choice == 5 && A[choice] != 1 && A[choice] != 2) {
        int x = 2;
        int y = 1;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }
    if (choice == 6 && A[choice] != 1 && A[choice] != 2) {
        int x = 4;
        int y = 1;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }
    if (choice == 7 && A[choice] != 1 && A[choice] != 2) {

        int y = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }

    if (choice == 8 && A[choice] != 1 && A[choice] != 2) {
        int x = 2;
        int y = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }

    if (choice == 9 && A[choice] != 1 && A[choice] != 2) {
        int x = 4;
        int y = 2;
        PC_DispChar(x, y, *text_ptr, DISP_FGND_BLACK + DISP_BGND_GRAY);
        A[choice] = 2;
    }


    else
    {
        printf("Invalid input, please try again: ");
        scanf_s("%d", &choice);
    }

    printf("\n");
    OSSemPost(Player2Sem);

    
}


void GameStatus(void* data) {

    INT8U  err;


    OSSemPend(StatusSem, 0, &err);
    if ((A[1] == 1 && A[2] == 1 && A[3] == 1)||(A[4] == 1 && A[5] == 1 && A[6] == 1) || (A[7] == 1 && A[8] == 1 && A[9] == 1) 
        || (A[1] == 1 && A[5] == 1 && A[9] == 1) || (A[3] == 1 && A[5] == 1 && A[7] == 1) || (A[1] == 1 && A[1+3] == 1 && A[1+6] == 1) 
        || (A[2] == 1 && A[2+3] == 1 && A[2+6] == 1) || (A[3] == 1 && A[3+3] == 1 && A[3+6] == 1)) {
        printf("X WINS");
    }
    if ((A[1] == 2 && A[2] == 2 && A[3] == 2) || (A[4] == 2 && A[5] == 2 && A[6] == 2) || (A[7] == 2 && A[8] == 2 && A[9] == 2)
        || (A[1] == 2 && A[5] == 2 && A[9] == 2) || (A[3] == 2 && A[5] == 2 && A[7] == 2) || (A[1] == 2 && A[1 + 3] == 2 && A[1 + 6] == 2)
        || (A[2] == 2 && A[2 + 3] == 2 && A[2 + 6] == 2) || (A[3] == 2 && A[3 + 3] == 2 && A[3 + 6] == 2)) {
        printf("O WINS");
    }
    else {
        printf("Draw");
    }
    OSSemPost(StatusSem);
}


/*
*********************************************************************************************************
*                                      NON-TASK FUNCTIONS
*********************************************************************************************************
*/


