/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// ROTS Header Files
#include "FreeRTOS_PSoC.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "event_groups.h"
#include "message_buffer.h"

// Your task function
void vUARTTask1(void *pvParaments);
void vAppTask2(void *pvParaments);

void myPSoCSetup();

MessageBufferHandle_t xMessageBuffer = NULL;
#define               MESSAGE_BUFFER_SIZE 100

CY_ISR_PROTO(myISR_UART);

int main(void)
{
    BaseType_t err;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FreeRTOS_Init();
    myPSoCSetup();
    
    // Create Mutex
   xMessageBuffer = xMessageBufferCreate(MESSAGE_BUFFER_SIZE);

    if (xMessageBuffer == NULL){
        while(1);   // Stop system here
    }
    
    // Create Task
    err = xTaskCreate(vUARTTask1,                    // Taskfunction_t pvTaskCode,
                        "Task 1",                   // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    }

    
    // Start the scheduler, so the tasks start executing
    vTaskStartScheduler();
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

void myPSoCSetup(){
    
    
    // Place your component's start code here
    ISR_UART_StartEx(myISR_UART);
    UART_Start();

    
    
}

typedef enum STATES_CMD{
    S_IDLE,
    S_GOT_DATE
}STATES_CMD;

CY_ISR(myISR_UART){
    static char         buf[20];
    static int          idx = 0;
    static STATES_CMD   state = S_IDLE;
    char                ch;
    char                str[20];
    BaseType_t          xHigherPriorityTaskWoken = pdFALSE; /* Initialised to pdFALSE */
    
    
    while (UART_GetRxBufferSize()  > 0){
        ch = UART_GetChar();
        
        switch (state){
            case S_IDLE:
                //UART_WriteTxData('1');
                if (ch == '+'){
                    state = S_GOT_DATE;
                }
                break;
            case S_GOT_DATE:
                //UART_WriteTxData('2'); 
                if (ch == '\r'){
                    ch = '\0';
                    //UART_WriteTxData('3'); 
                
                }
                if (ch == '\n'){
                    //UART_WriteTxData('4'); 
                    state = S_IDLE;
                    xMessageBufferSendFromISR(xMessageBuffer, buf, idx, xHigherPriorityTaskWoken);
                    idx = 0;
                    sprintf(str,"%s",buf);
                    UART_PutString(str); 
                    break;
                }
                buf[idx++] = ch;
                break;
        }
    }
    UART_ReadRxStatus(); // Clear IRQ signal
    
}


char* xMessage[] = {
        "Welcome",
        "To EE",
        "4450",
        "Message Buf"
};
void vUARTTask1(void *pvParaments){
    
    char    buf[20];
    size_t  rxSize;
    char    *delim = ":";
    char    *delim2 = "*";
    char    *pch;
    uint32  cmp;     
    UART_PutString("Task"); 
    while(1){
        if (xMessageBufferIsEmpty( xMessageBuffer ) == pdFALSE){
            rxSize = xMessageBufferReceive(xMessageBuffer,buf,sizeof(buf),100);
            pch = strtok(buf, delim);
            UART_PutString("Inside "); 
            UART_PutString(pch); 
            if (strcmp(pch, "LEDON") == 0){
                LED_Write(1);
            }
            else if (strcmp(pch, "LEDOFF") == 0){
                LED_Write(0);
            }
            else{
                pch = strtok(buf, delim2);
                cmp = atoi(pch);
                if ( cmp < 50){
                    LED_Write(1);
                }else{
                    LED_Write(0);
                }
            }
            /*
            pch = strtok(buf, delim);
            if (pch != NULL) {
                if (strcmp(pch, "PWM") == 0){
                    pch = strtok(buf, delim);
                    cmp = atoi(pch);    // atoi: string to integer
                    if (cmp <= 100)
                        PWM_WriteCompare(cmp);
                }
            }*/

        }
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 50 ms
    }
}


/* [] END OF FILE */
