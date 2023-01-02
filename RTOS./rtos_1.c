/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*					WIN32 PORT & LINUX PORT
*                          (c) Copyright 2004, Werner.Zimmermann@fht-esslingen.de
*                 (Similar to Example 1 of the 80x86 Real Mode port by Jean J. Labrosse)
*                                           All Rights Reserved
** *****************************************************************************************************
*		Further modified by mikael.jakas@puv.fi, jukka.matila@vamk.fi
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
#define  N_TASKS                        2       /* Number of identical tasks           */


/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/

OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];
OS_EVENT * ReadSem, * IncreaseSem, * MboxSem, * MboxSem2;

INT8U COUNT2 = 0;
INT8U COUNT1 = 0;


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void TaskStart(void* data);        /* Function prototype of Startup task           */
void Function_A(void* data);   /* Function prototypes of Function A Task     */
void Function_B(void* data);   /* Function prototypes of Function A Task     */
void READ_COUNTER(void *data);
void INCREASE_COUNTER(void* data);


/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

int  main(void)
{
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

    OSInit();                                              /* Initialize uC/OS-II       */

        IncreaseSem = OSSemCreate(1);


     ReadSem = OSSemCreate(1);



    OSTaskCreate(TaskStart, (void*)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);

    OSStart();                                             /* Start multitasking                       */





    return 0;
}


/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
void  TaskStart(void* pdata)
{
    INT16U key;
    INT8U symbol;
    INT8U symbol2;


    pdata = pdata;                                         /* Prevent compiler warning                 */
    symbol = 'O';
    symbol2 = 'L';

    OSTaskCreate(Function_A, (void*)&symbol, &TaskStk[1][TASK_STK_SIZE - 1], 2);

    OSTaskCreate(Function_B, (void*)&symbol2, &TaskStk[0][TASK_STK_SIZE - 1], 1);

    

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

void Function_A(INT8U* text_ptr) {

    // INT8U err;

    while (1)
    {
        INCREASE_COUNTER(COUNT1);
        READ_COUNTER(COUNT2);
        OSTimeDlyHMSM(0, 0, 1,0 );

    }





}



void Function_B(INT8U* text_ptr) {

    



    while (1)
    {
        
        INCREASE_COUNTER(COUNT1);
        READ_COUNTER(COUNT2);

       
        OSTimeDlyHMSM(0, 0, 1, 0);
    }




}

void READ_COUNTER(INT8U* text_ptr)
{
    INT8U err;
    
    OSMboxPend(MboxSem, 0, &err); 
    OSSemPend(ReadSem, 0, &err); 
    printf("C2:%d  ", COUNT2);
    printf("C1:%d  ", COUNT1);
    OSSemPost(ReadSem);
    OSMboxPost(MboxSem, (void*)1);

}/*function*/

void INCREASE_COUNTER(INT8U* text_ptr)
{
     INT8U err;

     OSMboxPend(MboxSem2, 0, &err);
    OSSemPend(IncreaseSem, 0, &err); 
    COUNT2++;
    COUNT1++;
    OSSemPost(IncreaseSem);
    OSMboxPost(MboxSem2, (void*)1);

   
}/*function*/





/*
*********************************************************************************************************
*                                      NON-TASK FUNCTIONS
*********************************************************************************************************
*/
