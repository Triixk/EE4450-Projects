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
void vAppTask1(void *pvParaments);
void vAppTask2(void *pvParaments);

void myPSoCSetup();

MessageBufferHandle_t xMessageBuffer = NULL;
#define               MESSAGE_BUFFER_SIZE 100
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
        LCD_PrintString("Message Buffer Error!");
        while(1);   // Stop system here
    }
    
    // Create Task
    err = xTaskCreate(vAppTask1,                    // Taskfunction_t pvTaskCode,
                        "Task 1",                   // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    }
    
    err = xTaskCreate(vAppTask2,                    // Taskfunction_t pvTaskCode,
                        "Task 2",                   // const char * const pcName,
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
    LCD_Start();
    LCD_ClearDisplay();
    
}
char* xMessage[] = {
        "Welcome",
        "To EE",
        "4450",
        "Message Buf"
};
void vAppTask1(void *pvParaments){
    
    int i = 0;
    int arraySize = sizeof(xMessage) /sizeof(xMessage[0]);
    size_t xBytesent;
    
    while( 1){
        xBytesent = xMessageBufferSend(xMessageBuffer, xMessage[i], 
                                            strlen(xMessage[i]),100);
        if (xBytesent == strlen(xMessage[i])){
            i++;
            if ( i > arraySize)
                i = 0;
        }
        
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 850 ms
    }
}
void vAppTask2(void *pvParaments){
    
    char        rxBuff[100];
    size_t      xBytesReceived;
    int arraySize = sizeof(rxBuff) / sizeof(rxBuff[0]);
    
    while(1){
        xBytesReceived = xMessageBufferReceive(xMessageBuffer, rxBuff,
                                        arraySize,pdMS_TO_TICKS(10));
        
        if (xBytesReceived > 0){
            rxBuff[xBytesReceived] = '\0';
            LCD_Position(1,0);
            LCD_PrintString(rxBuff);
        }
        
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 850 ms
    }
}

/* [] END OF FILE */
