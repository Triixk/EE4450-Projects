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

// Your task function
void vAppTask1(void *pvParaments);
void vAppTask2(void *pvParaments);

void myPSoCSetup();

QueueHandle_t xQueue = NULL;
typedef struct AMESSAGE{
    uint8_t idx;
    char    msg[10];
    
} AMESSAGE;

#define QUEUE_LENGTH 5
#define QUEUE_ITEM_SIZE (sizeof(AMESSAGE))

int main(void)
{
    BaseType_t err;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FreeRTOS_Init();
    myPSoCSetup();
    
    // Create Mutex
    xQueue = xQueueCreate(QUEUE_LENGTH,QUEUE_ITEM_SIZE);
    if (xQueue == NULL){
        LCD_PrintString("Queue Error!");
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
void vAppTask1(void *pvParaments){
    AMESSAGE    xMessage;
    int i = 0;
    
    while( 1){
        xMessage.idx = i;
        xMessage.msg[0] = 'a' + rand()%25;
        xMessage.msg[1] = 'a' + rand()%25;
        xMessage.msg[2] = 'a' + rand()%25;
        xMessage.msg[3] = '\0';
        
        while (xQueueSendToBack(xQueue, &xMessage, 100) != pdPASS);
        
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 850 ms
    }
}
void vAppTask2(void *pvParaments){
    
    AMESSAGE    xMessage;
    char        str[40];
    
    while(1){
        if ( xQueueReceive(xQueue, &xMessage, 100) == pdPASS){
            sprintf(str, "%d: %s", xMessage.idx, xMessage.msg);
            LCD_Position(1,0);
            LCD_PrintString(str);
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 850 ms
    }
}

/* [] END OF FILE */
