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

#define CMP0    19599
#define CMP180  17599

int main()
{
    CyGlobalIntEnable;
    uint16 counts = 0;
    float  meter  = 0;
    int  centimeter;
    char str[40];

    PWM_Start();
    PWM_WriteCompare(CMP0);
    
    LCD_Init();
    LCD_Start();
    LCD_ClearDisplay();
    
    for(;;)
    {

        //Timer_1_Init();  //Initiate timer
        Trigger_Write(1);
        CyDelayUs(10);
        Trigger_Write(0);
                 
        while(Echo_Read() != 1); //wait until return pulse starts
        Timer_Start();
        while(Echo_Read() != 0); //wait unit return pulse stops 
    
        counts = 0xFFFF-Timer_ReadCounter();        
        meter = counts * 0.0001717; //Convert pulse width to meters.     
        //meter = counts * 0.000001717; //Convert pulse width to centimeters.     
        
        if (meter < 0.5 ){              
            LED_Write(1);
            PWM_WriteCompare(CMP0);
        }          
        else{        
            LED_Write(0);
            PWM_WriteCompare(CMP180);
        }     
        CyDelay(200);
        Timer_Stop();
        centimeter = meter*100;
        
        sprintf(str, "%d cm",centimeter);
        //LCD_Position(0,0);
        LCD_ClearDisplay();
        LCD_PrintString(str);
    }
}
 
/* [] END OF FILE */
