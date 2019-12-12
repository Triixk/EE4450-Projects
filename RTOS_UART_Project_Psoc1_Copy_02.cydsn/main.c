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
void vReadUltraSonicTask(void *pvParaments);
void vMusicTask(void *pvParaments);
void vTestTask(void *pvParaments);

void beep(int note, int duration);
void firstSection();
void secondSection();
void myPSoCSetup();


#define CMP0    19099
#define CMP180  17599



int main(void)
{
    BaseType_t err;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    FreeRTOS_Init();
    myPSoCSetup();

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
    /*
    err = xTaskCreate(vMusicTask,                   // Taskfunction_t pvTaskCode,
                        "Read Sensor",              // const char * const pcName,
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

void myPSoCSetup(){
    
    
    // Place your component's start code here
    
    PWM_Servo_Start();
    PWM_Servo_WriteCompare(CMP0);
    CyDelay(1000);
    PWM_Music_Start();
    
    LCD_Init();
    LCD_Start();
    LCD_ClearDisplay();
    LCD_PrintString("Hello");
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
        sprintf(str,"Distance %d",centimeter);
        
        LCD_Position(1,0);
        LCD_PrintString(str);
        
        if (centimeter < 50){
            PWM_Servo_WriteCompare(CMP0);
            firstSection();
        }else {
            PWM_Servo_WriteCompare(CMP180);
            PWM_Music_WriteCompare(0);
        }
        

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
