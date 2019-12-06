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
void vReadUARTTask1(void *pvParaments);
void vSendUARTTask1(void *pvParaments);
void vWriteLCDTask2(void *pvParaments);

void myPSoC2Setup();

MessageBufferHandle_t xMessageBuffer = NULL;
#define               MESSAGE_BUFFER_SIZE 100

CY_ISR_PROTO(myISR_UART);

int main(void)
{
    BaseType_t err;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FreeRTOS_Init();
    myPSoC2Setup();
    UART_WriteTxData('a');
    // Create Mutex
   xMessageBuffer = xMessageBufferCreate(MESSAGE_BUFFER_SIZE);

    if (xMessageBuffer == NULL){
        while(1);   // Stop system here
    }
    
    // Create Task
    err = xTaskCreate(vReadUARTTask1,               // Taskfunction_t pvTaskCode,
                        "Read UART DATA",           // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1){
            UART_WriteTxData('c');
        }
    }
    UART_WriteTxData('b');
    // Start the scheduler, so the tasks start executing
    vTaskStartScheduler();
    
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

void myPSoC2Setup(){
    
    
    // Place your component's start code here
    UART_ClearRxBuffer();
    UART_ClearTxBuffer();
    ISR_UART_StartEx(myISR_UART);
    UART_Start();
    
    CyDelay(2000);
    UART_PutString(";L1:");
    
    CyDelay(2000);
    UART_PutString(";L2:");
    
    CyDelay(2000);
    UART_PutString(";S1:");
    
    CyDelay(2000);
    UART_PutString(";S2:");
    
    CyDelay(2000);
    UART_PutString(";S1:");
    
    CyDelay(2000);
    UART_PutString(";S2:");
    
    
}

typedef enum STATES_CMD{
    S_IDLE,
    S_GOT_DATE
}STATES_CMD;



CY_ISR(myISR_UART){
    static char         buf[20];
    static int          idx = 0;
    static int          write = 0;
    static STATES_CMD   state = S_IDLE;
    char                ch;
    BaseType_t          xHigherPriorityTaskWoken = pdFALSE; /* Initialised to pdFALSE */
    
    while (UART_GetRxBufferSize() > 0){
        //UART_WriteTxData('q');
    //while (UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY){    
        ch = UART_GetByte();
        //ch = UART_ReadRxData();
        buf[idx] = ch;
        idx++;
        CyDelay(10);
        write = 1;
        if (idx == 4){
            //UART_WriteTxData('P');
            buf[idx] = '\0';
            state = S_IDLE;
            xMessageBufferSendFromISR(xMessageBuffer, buf, 4, xHigherPriorityTaskWoken);
            idx = 0;
            
        }
    }
    UART_ReadRxStatus(); // Clear IRQ signal
    if (write == 1){
        UART_PutString(buf);
        write = 0;
    }
    /*
    UART_WriteTxData(buf[0]);
    CyDelay(10);
    UART_WriteTxData(buf[1]);
    CyDelay(10);
    UART_WriteTxData(buf[2]);
    CyDelay(10);
    UART_WriteTxData(buf[3]);
    CyDelay(10);
    */
    
}

// Task to read sensor data and write to global variable
void vReadUARTTask1(void *pvParaments){    
    char    buf[20];
    size_t  rxSize;
    char    *delim = ":";
    char    *pch;
    
    while(1){
        if (xMessageBufferIsEmpty( xMessageBuffer ) == pdFALSE){
            //UART_WriteTxData('M');
            rxSize = xMessageBufferReceive(xMessageBuffer,buf,4,100);
            pch = strtok(buf, delim);
            UART_PutString(pch);
            CyDelay(100);
            pch = strtok(buf, delim);
            UART_PutString(pch);
            if (rxSize > 0){
                if (strcmp(pch, "L1") == 0){
                    LED_Write(1);
                }
                else if (strcmp(pch, "L2") == 0){
                    LED_Write(0);
                }
            }
            vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50 ms
        }
    }
}


/* [] END OF FILE */
