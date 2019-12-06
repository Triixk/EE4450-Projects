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
void vUARTTask2(void *pvParaments);
void vUltraSonicTask(void *pvParaments);
void vReadUltraSonicTask(void *pvParaments);
void vMusicTask(void *pvParaments);

void beep(int note, int duration);
void firstSection();
void secondSection();
void myPSoCSetup();

MessageBufferHandle_t xMessageBuffer = NULL;
#define               MESSAGE_BUFFER_SIZE 100

CY_ISR_PROTO(myISR_UART);

#define CMP0    19099
#define CMP180  17599

// Global variables
int  centimeter;

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
        while(1);   // Stop system here
    }
    
    // Create Task
    err = xTaskCreate(vUARTTask1,                   // Taskfunction_t pvTaskCode,
                        "Task 1",                   // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    }/*
    err = xTaskCreate(vUARTTask2,                   // Taskfunction_t pvTaskCode,
                        "Task 1",                   // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    }*/
    // Create a task to read sensor data from the ultra sonic sensor
    err = xTaskCreate(vReadUltraSonicTask,          // Taskfunction_t pvTaskCode,
                        "Read Sensor",              // const char * const pcName,
                        configMINIMAL_STACK_SIZE,   // unsigned short usStackDepth,
                        NULL,                       // void *pvParameters,
                        configMAX_PRIORITIES-1,     // UBaseType_t uxPriority,
                        NULL);                      // TaskHandle_t *pxCreatedTask );
    
    if (err != pdPASS){
        // Cannot create task!
        while(1);
    }
    
    err = xTaskCreate(vMusicTask,                   // Taskfunction_t pvTaskCode,
                        "Read Sensor",              // const char * const pcName,
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
    ISR_UART_StartEx(myISR_UART);
    UART_Start();
    
    PWM_Servo_Start();
    PWM_Servo_WriteCompare(CMP0);
    
    PWM_Music_Start();

    
}

CY_ISR(myISR_UART){ 
    static char         buf[10];
    static int          idx = 0;
    char                ch;
    BaseType_t          xHigherPriorityTaskWoken = pdFALSE; /* Initialised to pdFALSE */
    
    strcpy(buf, "");
    
    while (UART_GetRxBufferSize() > 0){   
        ch = UART_GetByte();
        buf[idx] = ch;
        idx++;
        CyDelay(10);
        if (idx == 4){
            buf[idx] = '\0';
            xMessageBufferSendFromISR(xMessageBuffer, buf, 4, xHigherPriorityTaskWoken);
            idx = 0;
        }
    }
    UART_ReadRxStatus(); // Clear IRQ signal
}

void vUARTTask1(void *pvParaments){
    
    char    buf[10];
    size_t  rxSize;
    char    *delim = ";";
    char    *delim2 = ":";
    char    *pch;
    
    while(1){
        if (xMessageBufferIsEmpty( xMessageBuffer ) == pdFALSE){
            rxSize = xMessageBufferReceive(xMessageBuffer,buf,sizeof(buf),100);
            pch = strtok(buf, delim);
            //UART_PutString(pch);
            CyDelay(100);
            pch = strtok(pch, delim2);
            //UART_PutString(pch);
            if (strcmp(pch, "S1") == 0){
                PWM_Servo_WriteCompare(CMP180);
            }else if (strcmp(pch, "S2") == 0){
                PWM_Servo_WriteCompare(CMP0);
            }else if (strcmp(pch, "L1") == 0){
                LED_Write(1);
            }else if (strcmp(pch, "L2") == 0){
                LED_Write(0);
            }
        
            vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50 ms
        }
    }
}
/*
void vUARTTask2(void *pvParaments){
    
    char    ch;

    while(1){
        ch = UART_GetChar();
        switch(ch){
            case 'A':
                PWM_Servo_WriteCompare(CMP180);
                break;
            case 'B':
                PWM_Servo_WriteCompare(CMP0);
                break;
            case 'C':
                LED_Write(1);
                break;
            case 'D':
                LED_Write(0);
                break;    
        }

        vTaskDelay(pdMS_TO_TICKS(50)); // Delay for 50 ms
    }
}
*/
void vReadUltraSonicTask(void *pvParaments){
    
    uint16 counts = 0;
    float  meter  = 0;

    char str[40];
    
    while(1){
        Trigger_Write(1);
        CyDelayUs(10);
        Trigger_Write(0);
                 
        while(Echo_Read() != 1); //wait until return pulse starts
        Timer_Start();
        while(Echo_Read() != 0); //wait unit return pulse stops 
    
        counts = 0xFFFF-Timer_ReadCounter();        
        centimeter = counts * 0.01717; //Convert pulse width to centimeters.         
           
        vTaskDelay(pdMS_TO_TICKS(200)); // Delay for 200 ms
        Timer_Stop();
    }
}

const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  //tone(buzzerPin, note, duration);
  PWM_Music_WriteCompare(note);
  CyDelay(duration);
  
}
 
void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  CyDelay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  CyDelay(500);
}
 
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  CyDelay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  CyDelay(350);
}
void vMusicTask(void *pvParaments){
    
    //sing();
    
    while(1){
        //Play first section
        //firstSection();
 
        //Play second section
        //secondSection();
    }
}
/* [] END OF FILE */
