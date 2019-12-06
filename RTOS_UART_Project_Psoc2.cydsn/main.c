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
                        "Send UART DATA",           // const char * const pcName,
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
    UART_ClearRxBuffer();
    UART_ClearTxBuffer();
    ISR_UART_StartEx(myISR_UART);
    UART_Start();
    LCD_Init();
    LCD_Start();
    LCD_ClearDisplay();
    
    //UART_PutString("Hello");
    
    
}

typedef enum STATES_CMD{
    S_IDLE,
    S_GOT_DATE
}STATES_CMD;

#define RxBufferSize 20
uint8_t RxBuffer[RxBufferSize];
uint8_t *RxReadIndex = RxBuffer;
uint8_t *RxWriteIndex = RxBuffer;

CY_ISR(myISR_UART){
    static char         buf[128];
    static int          idx = 0;
    static STATES_CMD   state = S_IDLE;
    char                ch;
    BaseType_t          xHigherPriorityTaskWoken = pdFALSE; /* Initialised to pdFALSE */
    /*
    while (UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY){
        *RxWriteIndex++ = UART_ReadRxData();
        if (RxWriteIndex >= RxBuffer + RxBufferSize) RxWriteIndex = RxBuffer;
    }
    */
    
    while (UART_GetRxBufferSize() > 0 ){
        buf[idx] = UART_GetChar();
        idx++;
        if ( idx == 128 )
            idx = 0;
    }
    
    UART_ReadRxStatus(); // Clear IRQ signal
    
    //sprintf(buf, "%s", RxBuffer);
    UART_PutString(buf);
    /*
    for(int i = 0; i<20;i++){
        UART_WriteTxData(RxBuffer[i]);
        CyDelay(100);
    }*/
    /*
    //while (UART_GetRxBufferSize()  > 0){
    while (UART_ReadRxStatus() & UART_RX_STS_FIFO_NOTEMPTY){    
        ch = UART_GetChar();
        switch (state){
            case S_IDLE:
                //UART_WriteTxData('1');
                if (ch == '+'){
                    strcpy(buf, "");
                    state = S_GOT_DATE;
                }
                break;
            case S_GOT_DATE:
                //UART_WriteTxData('2');
                if (ch == '\r')
                    ch = '\0';
                else if (ch == '\n'){
                    buf[idx] = '\0';
                    state = S_IDLE;
                    xMessageBufferSendFromISR(xMessageBuffer, buf, idx, xHigherPriorityTaskWoken);
                    idx = 0;
                }
                buf[idx] = ch;
                idx++;
                break;
        }
        CyDelay(100);
    }
    UART_ReadRxStatus(); // Clear IRQ signal
    
    UART_WriteTxData(buf[0]);
    CyDelay(10);
    UART_WriteTxData(buf[1]);
    CyDelay(10);
    UART_WriteTxData(buf[2]);
    CyDelay(10);
    UART_WriteTxData(buf[3]);
    CyDelay(10);
    UART_WriteTxData(buf[4]);
    CyDelay(10);
    UART_WriteTxData(buf[5]);
    CyDelay(10);
    UART_WriteTxData(buf[6]);
    CyDelay(10);
    
    */
}


int distance = 1;
int not_sent = 1;

// Task to send commands to Psoc 1 based on sensor readings
void vSendUARTTask1(void *pvParaments){
    char servo_open[]   = "GATE:OPEN:\r\n";
    char servo_close[]  = "GATE:CLOSE:\r\n";
    char led_on[]       = "LED:ON:\r\n";
    char led_off[]      = "LED:OF:\r\n";
    
    for(int i = 0; i < strlen(servo_open);i++){
            UART_WriteTxData(servo_open[i]);
    } 
    
    while(1){
       if (distance < 0.5 && not_sent == 0){
            
            for(int i = 0; i < strlen(servo_open);i++){
                UART_WriteTxData(servo_open[i]);
            }
            not_sent = 1;          
       }else if (distance > 0.5 && not_sent == 0){
            for(int i = 0; i < strlen(servo_close);i++){
                UART_WriteTxData(servo_close[i]);
            }
            not_sent = 1;
        }
        
    }
}

// Task to read sensor data and write to global variable
void vReadUARTTask1(void *pvParaments){
    
    char    buf[20];
    size_t  rxSize;
    char    *delim = ":";
    char    *pch;
  
    
    while(1){
        rxSize = xMessageBufferReceive(xMessageBuffer,buf,sizeof(buf),100);
        if (rxSize > 0){
            UART_WriteTxData('A');
            pch = strtok(buf, delim);
            if (pch != NULL) {
                UART_WriteTxData('B');
                if (strcmp(pch, "LED") == 0){
                    UART_WriteTxData('C');
                    pch = strtok(buf, delim);
                    if (strcmp(pch, "ON") == 0){
                        UART_WriteTxData('D');
                        LED_Write(1);
                    } else if (strcmp(pch, "OFF") == 0){
                        LED_Write(0);
                    }
                }
                /*
                if (strcmp(pch, "PWM") == 0){
                    pch = strtok(buf, delim);
                    cmp = atoi(pch);    // atoi: string to integer
                    
                }*/
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
