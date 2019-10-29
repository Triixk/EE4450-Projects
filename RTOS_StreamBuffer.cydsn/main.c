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

StreamBufferHandle_t    xStreamBuffer = NULL;
#define                 STREAM_BUFFER_SIZE 100
#define                 TRIGGER_LEVEL 10

int main(void)
{
    BaseType_t err;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FreeRTOS_Init();
    myPSoCSetup();
    
    // Create Mutex
   xStreamBuffer = xStreamBufferCreate(STREAM_BUFFER_SIZE, TRIGGER_LEVEL);

    if (xStreamBuffer == NULL){
        LCD_PrintString("Stream Buffer Error!");
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
    
    uint    i = 0;
    size_t  xBytesSent;
    uint8_t ucArrayToSend[] = {1, 2, 3, 4};
    char    *pStrToSend = "String to Send";
    
    
    while( 1){
        i = 0;
        do{
            xBytesSent = xStreamBufferSend(xStreamBuffer, &ucArrayToSend[i], sizeof(ucArrayToSend)-i, pdMS_TO_TICKS(100));
            i += xBytesSent;
        }while(i < sizeof(ucArrayToSend));
        
        i = 0;
        do{
            xBytesSent = xStreamBufferSend(xStreamBuffer, &pStrToSend[i], strlen(&pStrToSend[i]), pdMS_TO_TICKS(100));
            i += xBytesSent;
           
        }while(i < strlen(pStrToSend));
        
        
        
        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 850 ms
    }
}
void vAppTask2(void *pvParaments){
    
    char        rxBuff[50];
    size_t      xBytesReceived;
    int arraySize = sizeof(rxBuff) / sizeof(rxBuff[0]);
    char str[40];
    
    while(1){
        xBytesReceived = xStreamBufferReceive(xStreamBuffer, rxBuff, sizeof(rxBuff), 20);
        
        if (xBytesReceived > 0){
            for (int i = 0; i < xBytesReceived; i++){
                if ( ((rxBuff[i] >= '0') && (rxBuff[i] <= '9')) || 
                        ((rxBuff[i] >= 'a') && (rxBuff[i] <= 'z')) ||
                        ((rxBuff[i] >= 'A') && (rxBuff[i] <= 'Z'))){
                        LCD_PutChar(rxBuff[i]);
                
                }else{
                    sprintf(str,"%d",rxBuff[i]);
                    LCD_PrintString(str);
        
                }
                vTaskDelay(pdMS_TO_TICKS(50));
            }
            
        }
      
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 850 ms
    }
}

/* [] END OF FILE */
