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

typedef enum STATES{
    S_RED,
    S_GREEN,
    S_YELLOW,
} STATES;

int main(void)
{
    STATES  state = S_RED;
    bool    cmdGo, cmdStop; // Command for 
    int     timeOut = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    // After power on, turn off all lights
    RedLED_Write(0);
    GreenLED_Write(0);
    YellowLED_Write(0);
    
    for(;;)
    {
        /* Place your application code here. */
    
        cmdGo   = !nSW_Go_Read();
        cmdStop = !nSW_STOP_Read();
        
        
        switch(state){
            case S_RED:
                RedLED_Write(1);
                YellowLED_Write(0);
                if (cmdGo)
                    state = S_GREEN;
                break;
            case S_GREEN:
                // Turn off RED, turn on Green
                RedLED_Write(0);
                GreenLED_Write(1);
                
                if (cmdStop){
                    timeOut = 20;
                }
                break;
            case S_YELLOW:
                // Turn on Yellow LED and turn off Green
                YellowLED_Write(1);
                GreenLED_Write(0);
                
                timeOut--;
                if (timeOut < 0){
                    state = S_RED;
                }
                
                break;
        }
        CyDelay(50);
    }
}

/* [] END OF FILE */
