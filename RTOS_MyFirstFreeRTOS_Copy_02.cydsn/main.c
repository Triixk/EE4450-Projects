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

int main(void)
{
    BaseType_t err;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FreeRTOS_Init();
    myPSoCSetup();
    
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
    
}
void vAppTask1(void *pvParaments){
    while(1){
    LED1_Write(!LED1_Read());       // Toggle LED1
    vTaskDelay(pdMS_TO_TICKS(1000));// Delay for 1 sec
    }
}
void vAppTask2(void *pvParaments){
    while(1){
    LED2_Write(!LED2_Read());       // Toggle LED1
    vTaskDelay(pdMS_TO_TICKS(850)); // Delay for 850 ms
    }
}

/* [] END OF FILE */
