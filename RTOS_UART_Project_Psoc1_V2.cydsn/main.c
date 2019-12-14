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
void vReadUltraSonicTask(void *pvParaments);

void beep(int note, int duration);
void firstSection();
void secondSection();
void myPSoCSetup();

MessageBufferHandle_t xMessageBuffer = NULL;
#define               MESSAGE_BUFFER_SIZE 100

CY_ISR_PROTO(myISR_UART);

#define CMP0    19099
#define CMP180  17599



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
    }
    
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
    PWM_Music_Start();
    UART_USB_Start();
    UART_USB_PutString("Start\r\n");
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
                if (ch == '+'){
                    state = S_GOT_DATE;
                }
                break;
            case S_GOT_DATE:
                if (ch == '\r'){
                    ch = '\0';                
                }
                if (ch == '\n'){
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
    
    while(1){
        if (xMessageBufferIsEmpty( xMessageBuffer ) == pdFALSE){ // Check if there is something in the message buffer
            rxSize = xMessageBufferReceive(xMessageBuffer,buf,sizeof(buf),100);
            pch = strtok(buf, delim);
            if (strcmp(pch, "SystemON") == 0){
                PWM_Servo_WriteCompare(CMP180);
                LED_Write(1);
                firstSection();
            }else if (strcmp(pch, "SystemOFF") == 0){
                PWM_Servo_WriteCompare(CMP0);
                LED_Write(0);
                firstSection();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay for 100 ms
    }
}

void vReadUltraSonicTask(void *pvParaments){
    
    uint16 counts = 0;
    float  meter  = 0;
    int centimeter;
    char str[20];
    
    while(1){
        LED_Write(1);
        Trigger_Write(1);
        vTaskDelay(pdMS_TO_TICKS(10)); // Delay for 200 ms
        //CyDelayUs(10);
        Trigger_Write(0);
              
        while(Echo_Read() != 1); //wait until return pulse starts
        Timer_Start();
        while(Echo_Read() != 0); //wait unit return pulse stops 
        
        counts = 0xFFFF-Timer_ReadCounter();        
        centimeter = counts * 0.01717; //Convert pulse width to centimeters.         
           
        vTaskDelay(pdMS_TO_TICKS(200)); // Delay for 200 ms
        Timer_Stop();
        LED_Write(0);
        
        sprintf(str,"+%d:\r\n",centimeter);
        UART_PutString(str);
        
        UART_USB_PutString("Sending ");
        UART_USB_PutString(str);
        
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
  //CyDelay(duration);
  vTaskDelay(pdMS_TO_TICKS(duration));
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
