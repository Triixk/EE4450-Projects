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

void myPSoC2Setup(){
    
    
    // Place your component's start code here
    ISR_UART_StartEx(myISR_UART);
    UART_Start();
    LCD_Init();
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("Hello");
    
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

void vUARTTask1(void *pvParaments){
    
    char    buf[20];
    size_t  rxSize;
    char    *delim = ":";
    char    *pch;
    uint32  distance;     
    char    str[20];
    
    char    system_on[] = "SystemON:\r\n";
    char    system_off[] = "SystemOFF:\r\n";
    
    //UART_PutString("Task Started \r\n"); 
    while(1){
        if (xMessageBufferIsEmpty( xMessageBuffer ) == pdFALSE){
            rxSize = xMessageBufferReceive(xMessageBuffer,buf,sizeof(buf),100);
            pch = strtok(buf, delim);
            UART_PutString("Received ");
            UART_PutString(pch);
            UART_PutString("\n");
            
            distance = atoi(pch);
            sprintf(str,"Distance: %d   ",distance);
            LCD_Position(1,0);
            LCD_PrintString(str);
            
            if (distance < 50){
                LED_Write(1);
                UART_PutString(system_on);
                LCD_Position(0,0);
                LCD_PrintString("System ON ");
            
            }
            else {
                LED_Write(0);
                UART_PutString(system_off);
                LCD_Position(0,0);
                LCD_PrintString("System OFF");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 50 ms
    }
}


/* [] END OF FILE */
