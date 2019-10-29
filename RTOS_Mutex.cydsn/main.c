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

SemaphoreHandle_t xMutex_LCD;

int main(void)
{
    BaseType_t err;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FreeRTOS_Init();
    myPSoCSetup();
    
    // Create Mutex
    xMutex_LCD = xSemaphoreCreateMutex();
    if (xMutex_LCD == NULL){
        LCD_PrintString("Mutx Error!");
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
    
    int i = 0;
    while( xSemaphoreTake(xMutex_LCD, 100 != pdPASS)){
        LCD_Position(0,0);
        LCD_PrintInt16(i);
        xSemaphoreGive(xMutex_LCD);
        i++;
        if (i > 100) i = 0;
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 850 ms
    }
}
void vAppTask2(void *pvParaments){
    
    char ch='a';
    char str[20];
    while(1){
        sprintf(str, "%c ", ch);
        xSemaphoreTake(xMutex_LCD, portMAX_DELAY);
        LCD_Position(0,10);
        LCD_PrintString(str);
        xSemaphoreGive(xMutex_LCD);
        ch++;
        if (ch > 'z') ch = 'a';
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 850 ms
    }
}

/* [] END OF FILE */
