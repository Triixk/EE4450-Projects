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
    
    // Create Mutex
   xMessageBuffer = xMessageBufferCreate(MESSAGE_BUFFER_SIZE);

    if (xMessageBuffer == NULL){
        LCD_PrintString("Message Buffer Error!");
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
        while(1);
    }
    err = xTaskCreate(vSendUARTTask1,               // Taskfunction_t pvTaskCode,
                        "Read UART DATA",           // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    }    
    err = xTaskCreate(vWriteLCDTask2,               // Taskfunction_t pvTaskCode,
                        "Write LCD",                // const char * const pcName,
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
    BaseType_t          xHigherPriorityTaskWoken = pdFALSE; /* Initialised to pdFALSE */
    
    
    while (UART_GetRxBufferSize  > 0){
        ch = UART_GetChar();
        
        switch (state){
            case S_IDLE:
                if (ch == '+')
                    state = S_GOT_DATE;
                
                break;
            case S_GOT_DATE:
                if (ch == '\r')
                    ch = '\0';
                if (ch == '\n'){
                    state = S_IDLE;
                    xMessageBufferSendFromISR(xMessageBuffer, buf, idx, xHigherPriorityTaskWoken);
                    idx = 0;
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
int distance;
// Task to send commands to Psoc 1 based on sensor readings
void vSendUARTTask1(void *pvParaments){
    char servo_open[]   = "SERVOOPEN";
    char servo_close[]  = "SERVOCLOSE";
    char led_on[]       = "LEDON";
    char led_off[]      = "LEDOF";
    
    while(1){
       if (distance < 0.5){
          for(int i = 0; i < strlen(servo_open);i++){
            UART_WriteTxData(servo_open[i]);
          }
       }else if (distance > 0.5){
          for(int i = 0; i < strlen(servo_close);i++){
            UART_WriteTxData(servo_close[i]);
          }
        }
       
    }
}

// Task to read sensor data and write to global variable
void vReadUARTTask1(void *pvParaments){
    
    char    buf[20];
    size_t  rxSize;
    char    *delim = ":";
    char    *pch;
    uint32  cmp;     
    
    while(1){
        rxSize = xMessageBufferReceive(xMessageBuffer,buf,sizeof(buf),100);
        if (rxSize > 0){
            pch = strtok(buf, delim);
            if (pch != NULL) {
                if (strcmp(pch, "PWM") == 0){
                    pch = strtok(buf, delim);
                    cmp = atoi(pch);    // atoi: string to integer
                    if (cmp <= 100)
                        PWM_WriteCompare(cmp);
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50 ms
    }
}
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
}

/* [] END OF FILE */
