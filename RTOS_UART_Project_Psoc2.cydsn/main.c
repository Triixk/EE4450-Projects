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
void vWriteLCDTask2(void *pvParaments);

void myPSoC2Setup();
void senduart(char *buff, int size);

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
        LCD_PrintString("Message Buffer Error!");
        while(1);   // Stop system here
    }
    
    // Create Task
    err = xTaskCreate(vUARTTask1,               // Taskfunction_t pvTaskCode,
                        "Read UART DATA",           // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    } /*
    err = xTaskCreate(vWriteLCDTask2,               // Taskfunction_t pvTaskCode,
                        "Write LCD",                // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    }*/
    
    // Start the scheduler, so the tasks start executing
    vTaskStartScheduler();
    
    for(;;)
    {
        /* Place your application code here. */
    }
}
char msg[] = "Hello";

void myPSoC2Setup(){
    // Place your component's start code here
    UART_ClearRxBuffer();
    UART_ClearTxBuffer();
    ISR_UART_StartEx(myISR_UART);
    UART_Start();
    UART_USB_Start();
    LCD_Init();
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString(msg);
    UART_USB_PutString("Hello");
}

typedef enum STATES_CMD{
    S_IDLE,
    S_GOT_DATE
}STATES_CMD;


CY_ISR(myISR_UART){
    static char         buf[20];
    static int          idx = 0;
    char                ch;
    BaseType_t          xHigherPriorityTaskWoken = pdFALSE; /* Initialised to pdFALSE */
    /*
    while (UART_GetRxBufferSize() > 0){
        ch = UART_GetByte();
        buf[idx] = ch;
        idx++;
        CyDelay(10);
        UART_USB_PutChar(ch);
        if (idx == 4){
            buf[idx] = '\0';
            xMessageBufferSendFromISR(xMessageBuffer, buf, 4, xHigherPriorityTaskWoken);
            idx = 0;
            UART_USB_PutString(buf);
            LCD_Position(0,0);
            LCD_PrintString(buf);
        }
    }*/
    ch = UART_GetByte();
    UART_USB_PutChar(ch);
    xMessageBufferSendFromISR(xMessageBuffer, ch, 1, xHigherPriorityTaskWoken);
    //LCD_PutChar(ch);
}



// Task to read sensor data and write to global variable
void vUARTTask1(void *pvParaments){
    
    char led_on[4]    = ";L1:";
    char led_off[4]   = ";L2:";
    char servo_on[4]  = ";S1:";
    char servo_off[4] = ";S2:";
    char music_on[4]  = ";M1:";
    char music_off[4] = ";M2:";
    
    char    buf[20];
    char    str[20];
    size_t  rxSize;
    char    *delim1 = ";";
    char    *delim2 = ":";
    char    *pch;
    uint8_t     distance;
  
    
    while(1){
        
        if (xMessageBufferIsEmpty( xMessageBuffer ) == pdFALSE){
            
            /*
            rxSize = xMessageBufferReceive(xMessageBuffer,buf,4,100);
            UART_USB_PutString(pch);
            pch = strtok(buf, delim1);
            UART_USB_PutString(pch);
            CyDelay(100);
            pch = strtok(buf, delim2);
            distance = atoi(pch);
            UART_USB_PutString(pch);
            sprintf(buf,"Distance: %d  ",distance);
            LCD_Position(1,0);
            LCD_PrintString(buf);
            */
            
            rxSize = xMessageBufferReceive(xMessageBuffer,distance,1,100);
            sprintf(str,"Dis: %d  ",distance);
            LCD_Position(1,0);
            LCD_PrintString(str);
            if (distance < 50){
                // Open gate etc
                LED_Write(0);
            } else{
                // Close gate etc
                LED_Write(1);
            }       
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 50 ms
    }
        
}


/*
void vWriteLCDTask2(void *pvParaments){
    
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
}*/

/* [] END OF FILE */
