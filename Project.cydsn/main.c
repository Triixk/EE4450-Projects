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
//#include "BlynkBLEPeripheralSerial.h"

char auth[] = "htWD8znEJsrgIpZZI8atoZixwlOv1_Y7";

int main()
{
    CyGlobalIntEnable;
    uint16 counts = 0;
    float  meter   = 0;

 
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
        if (meter < 0.5 ){              
            LED_Write(1);            
        }          
        else{        
            LED_Write(0);
        }     
        CyDelay(100);
        Timer_Stop();
    }
}
 
/* [] END OF FILE */
